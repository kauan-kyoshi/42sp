#!/bin/bash

# Script de teste para push_swap usando o checker da 42
# Uso: ./test_checker.sh

CHECKER="./checker_linux(1)"
PUSH_SWAP="./push_swap"

# Cores para output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}=== Testes Push Swap com Checker da 42 ===${NC}\n"

# Função para testar
test_case() {
    local ARG="$1"
    local OP_COUNT=$(./push_swap $ARG 2>/dev/null | wc -l)
    local RESULT=$(./push_swap $ARG 2>/dev/null | $CHECKER $ARG 2>/dev/null)
    
    if [ "$RESULT" = "OK" ]; then
        echo -e "${GREEN}✓ OK${NC}: $ARG (${OP_COUNT} operações)"
        return 0
    else
        echo -e "${RED}✗ KO${NC}: $ARG"
        return 1
    fi
}

# Testes básicos
echo "Testes básicos:"
test_case "2 1"
test_case "1 2 3"
test_case "3 2 1"
test_case "1 3 2"
test_case "2 1 3"
test_case "2 3 1"
test_case "3 1 2"

echo -e "\nTestes com mais números:"
test_case "5 4 3 2 1"
test_case "1 5 2 4 3"
test_case "4 67 3 87 23"
test_case "10 9 8 7 6 5 4 3 2 1"

echo -e "\nTestes com número único:"
test_case "42"
test_case "0"
test_case "-5"

echo -e "\nTestes de validação (devem mostrar Error):"
echo -e "${YELLOW}Testando duplicatas...${NC}"
./push_swap 1 1 2 2>&1 | grep -q "Error" && echo -e "${GREEN}✓ OK${NC}: Duplicata detectada" || echo -e "${RED}✗ FALHOU${NC}: Duplicata não detectada"

echo -e "${YELLOW}Testando número inválido...${NC}"
./push_swap abc 2>&1 | grep -q "Error" && echo -e "${GREEN}✓ OK${NC}: Número inválido detectado" || echo -e "${RED}✗ FALHOU${NC}: Número inválido não detectado"

echo -e "${YELLOW}Testando sem argumentos...${NC}"
./push_swap 2>&1 | grep -q "Error" || [ $? -eq 0 ] && echo -e "${GREEN}✓ OK${NC}: Sem argumentos (sem output)" || echo -e "${RED}✗ FALHOU${NC}"

echo -e "\n${YELLOW}Testes completos!${NC}"

