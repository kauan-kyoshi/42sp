#!/bin/bash

GREEN='\033[0;32m'
NO_COLOR='\033[0m' # No Color

cd libft && \
make re
cd ../tests && \
make && \
make leakfull && \
cd ../libft && \
norminette && \
echo ""  && \
echo -e "${GREEN}SUCESSO!${NO_COLOR}" 