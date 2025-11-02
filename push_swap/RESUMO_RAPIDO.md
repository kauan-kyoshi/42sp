# ⚡ Resumo Rápido - Avaliação Push Swap

## 🚀 Comandos Essenciais

```bash
# Compilar
make re

# Teste básico
ARG="3 2 1"; ./push_swap $ARG | ./checker_linux* $ARG

# Todos os testes
./test_checker.sh
```

## 📋 Checklist Rápido

- [ ] `make re` compila
- [ ] Checker retorna OK em todos os testes
- [ ] Erros são tratados (duplicatas, inválidos)
- [ ] Sem memory leaks

## 🧠 Explicação do Algoritmo (30 segundos)

**Algoritmo em 3 fases:**
1. **Reduzir**: Mover menores elementos de A para B até restarem 3
2. **Ordenar**: Ordenar os 3 restantes em A
3. **Inserir**: Inserir cada elemento de B de volta em A na posição correta

**Por que?** Simples, fácil de entender e explicar, funcional para todos os casos.

## 📁 Estrutura

- `main.c` - Entrada, validação, ordenação
- `parse.c` - Parsing com suporte a strings com espaços
- `operations.c` - 11 operações implementadas
- `sort.c` - Algoritmos (sort_2, sort_3, sort_many)
- `utils.c` - Funções auxiliares
- `stack_utils.c` - Inicialização/limpeza

## ❓ Perguntas Frequentes

**Q: Como funciona?**  
A: Reduz A enviando menores para B, ordena os 3 restantes, insere de volta ordenadamente.

**Q: Por que não Radix?**  
A: Algoritmo simples, fácil de entender e explicar, funcional.

**Q: Memory leaks?**  
A: Cada malloc tem free. `free_stack()` limpa tudo.

**Q: Validação?**  
A: Verifica duplicatas, números inválidos, limites de INT.

## ✅ Métricas

- 2 números: 1 op ✅
- 3 números: 1-2 ops ✅ (máx 3)
- 5 números: 6-8 ops ✅ (máx 12)
- Checker: 100% OK ✅

---

**📖 Para mais detalhes, veja `GUIA_AVALIACAO.md`**

