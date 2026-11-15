#!/bin/bash

set -e

# Garante que o diretório web exista e pertença ao usuário do webserver
mkdir -p /var/www/html
mkdir -p /run/php
chown -R www-data:www-data /var/www/html

cd /var/www/html

# Aguarda o MariaDB ficar pronto para aceitar conexões
DB_PASSWORD=$(cat /run/secrets/db_password 2>/dev/null || echo "$MYSQL_PASSWORD")

until mysqladmin -h"${MYSQL_HOST}" -u"${MYSQL_USER}" -p"${DB_PASSWORD}" ping --silent; do
    echo "Aguardando o MariaDB iniciar..."
    sleep 2
done

WP_ADMIN_USER="${WORDPRESS_ADMIN_USER:-${WP_ADMIN_USER}}"
WP_ADMIN_PASSWORD="${WORDPRESS_ADMIN_PASSWORD:-${WP_ADMIN_PASSWORD}}"
WP_ADMIN_EMAIL="${WORDPRESS_ADMIN_EMAIL:-${WP_ADMIN_EMAIL}}"
WP_USER="${WORDPRESS_USER:-${WP_USER}}"
WP_PASSWORD="${WORDPRESS_USER_PASSWORD:-${WP_PASSWORD}}"
WP_EMAIL="${WORDPRESS_USER_EMAIL:-${WP_EMAIL}}"

# Se o WordPress ainda não foi instalado, faz o setup completo
if [ ! -f "wp-config.php" ]; then
    if [ ! -f "wp-includes/version.php" ]; then
        echo "Baixando o core do WordPress..."
        wp core download --allow-root --locale=pt_BR
    fi

    echo "Criando o arquivo wp-config.php..."
    wp config create --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${DB_PASSWORD}" \
        --dbhost="${MYSQL_HOST}"

    echo "Instalando o WordPress..."
    wp core install --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="Inception 42 - ${DOMAIN_NAME}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}"

    echo "Criando usuário secundário..."
    wp user create --allow-root \
        "${WP_USER}" "${WP_EMAIL}" \
        --user_pass="${WP_PASSWORD}" \
        --role=author
fi

echo "Iniciando o PHP-FPM em foreground (PID 1)..."
exec php-fpm7.4 -F