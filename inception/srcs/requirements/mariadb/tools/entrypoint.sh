#!/bin/bash

set -e

DB_PASSWORD=$(cat /run/secrets/db_password 2>/dev/null || echo "$MYSQL_PASSWORD")
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password 2>/dev/null || echo "$MYSQL_ROOT_PASSWORD")

mysql_exec() {
    mysql -u root -p"${DB_ROOT_PASSWORD}" "$@" 2>/dev/null || mysql -u root "$@"
}

# Verifica se o diretório de dados do MySQL já foi inicializado no volume persistente
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Inicializando o diretório de dados do MariaDB..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null
fi

mkdir -p /var/run/mysqld
chown -R mysql:mysql /var/run/mysqld /var/lib/mysql

# Inicia temporariamente o serviço em background para garantir a configuração do banco/usuário
mysqld --user=mysql &
pid="$!"

# Aguarda o MariaDB subir completamente
until mysqladmin ping --silent; do
    sleep 1
done

echo "Configurando banco de dados e usuários..."

mysql_exec <<-EOSQL
    CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
    CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
    ALTER USER '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
    GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
    ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWORD}';
    FLUSH PRIVILEGES;
EOSQL

mysqladmin -u root -p"${DB_ROOT_PASSWORD}" shutdown 2>/dev/null || mysqladmin -u root shutdown
wait "$pid"

echo "Iniciando o MariaDB em foreground (PID 1)..."
exec mysqld_safe