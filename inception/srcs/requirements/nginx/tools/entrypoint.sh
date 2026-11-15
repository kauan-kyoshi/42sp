#!/bin/bash

# Gera o certificado SSL autoassinado se ele ainda não existir
if [ ! -f /etc/ssl/certs/kakubo-l.42.fr.crt ]; then
    echo "Gerando certificado SSL autoassinado para o domínio ${DOMAIN_NAME}..."
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/ssl/private/kakubo-l.42.fr.key \
        -out /etc/ssl/certs/kakubo-l.42.fr.crt \
        -subj "/C=BR/ST=SP/L=Sao Paulo/O=42Sp/CN=${DOMAIN_NAME}"
fi

echo "Iniciando o NGINX em foreground (PID 1)..."
exec nginx -g "daemon off;"