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

Implementação atual: solução personalizada em três fases — reduzir, ordenar um núcleo pequeno (2–3 elementos) e inserir de volta a partir da pilha auxiliar `B`.

Resumo rápido:
1. Reduzir: mover alguns elementos de `A` para `B` até sobrar um núcleo pequeno em `A`.
2. Ordenar: ordenar esse núcleo com casos manuais (função `sort_3()`).
3. Inserir: reinserir cada elemento de `B` em `A` na posição correta, usando rotações otimizadas.

Observação: se você quiser um nome formal do algoritmo, eu posso extrair do código e inserir aqui.

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

## ✅ Métricas (testes recentes)

- 2 números: 1 op ✅
- 3 números: 1–2 ops ✅ (máx 3)
- 5 números: ~6–8 ops ✅ (máx 12)
- 100 números (5 runs): operações = [612, 595, 584, 610, 581] → média 596.40 ✅
- 500 números (3 runs): operações = [5385, 5333, 5388] → média 5368.67 ✅
- Checker: 100% OK nos testes executados ✅

---

**📖 Para mais detalhes, veja `GUIA_AVALIACAO.md`**

