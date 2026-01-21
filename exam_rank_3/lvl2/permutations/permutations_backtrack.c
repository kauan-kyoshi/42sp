/* permutations_backtrack.c
 * Versão por backtracking (recursiva) das permutações em ordem lexicográfica.
 * Recebe uma única string como argumento e imprime cada permutação
 * única em ordem lexicográfica, uma por linha.
 */

#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* puts */

/* ------------------------------------------------------------
 * Função: my_strlen
 * Objetivo: calcular o comprimento de uma string C-terminada por '\0'.
 * Entrada: ponteiro `s` para a string.
 * Saída : comprimento (size_t). Se `s` for NULL, retorna 0.
 * ------------------------------------------------------------ */
static size_t my_strlen(const char *s)
{
    size_t i = 0;            /* contador de caracteres */
    if (!s) return 0;       /* segurança: ponteiro nulo */
    while (s[i]) i++;       /* avança até encontrar o terminador '\0' */
    return i;               /* retorna o comprimento contado */
}

/* ------------------------------------------------------------
 * Função: sort_string
 * Objetivo: ordenar a string `s` de tamanho `n` em ordem crescente
 *            usando insertion sort (algoritmo simples e seguro).
 * Por que: para que a geração por backtracking produza permutações
 *          em ordem lexicográfica quando iteramos índices em ordem.
 * ------------------------------------------------------------ */
static void sort_string(char *s, size_t n)
{
    for (size_t i = 1; i < n; ++i) {
        char key = s[i];           /* elemento a inserir na parte ordenada */
        long j = (long)i - 1;      /* índice para percorrer a parte ordenada */
        while (j >= 0 && s[j] > key) {
            s[j+1] = s[j];         /* desloca elementos maiores para a direita */
            j--;                   /* continua procurando o local correto */
        }
        s[j+1] = key;              /* insere o elemento na posição correta */
    }
}

/* ------------------------------------------------------------
 * Função: backtrack_select
 * Objetivo: gerar permutações recursivamente por seleção.
 * Parâmetros:
 *  - src: string fonte (ordenada) contendo os caracteres disponíveis
 *  - n: comprimento da string fonte
 *  - perm: buffer onde construímos a permutação atual
 *  - pos: posição atual em `perm` que estamos preenchendo
 *  - used: vetor de inteiros (0/1) que marca quais índices de `src`
 *          já foram usados na permutação corrente
 *
 * Lógica:
 *  - Se pos == n, construímos uma permutação completa em `perm` e
 *    a imprimimos com `puts`.
 *  - Caso contrário, iteramos i de 0 a n-1 e escolhemos `src[i]`
 *    se ainda não foi usado. Para evitar permutações duplicadas quando
 *    há caracteres repetidos, aplicamos a checagem:
 *      se i>0 e src[i]==src[i-1] e used[i-1]==0 então pular i
 *    (isso garante que entre caracteres iguais escolhemos apenas a
 *     primeira disponível naquele nível de recursão).
 * ------------------------------------------------------------ */
static void backtrack_select(const char *src, size_t n, char *perm, size_t pos, int *used)
{
    if (pos == n) {
        perm[n] = '\0';    /* termina a string de permutação */
        puts(perm);         /* imprime a permutação seguida de '\n' */
        return;             /* volta para explorar outras escolhas */
    }

    /* percorre todos os índices da fonte em ordem crescente */
    for (size_t i = 0; i < n; ++i) {
        if (used[i]) continue; /* pula se este caractere já foi usado */

        /* evita gerar duplicatas: quando há caracteres iguais em src,
         * só devemos escolher o segundo (ou posteriores) se o anterior
         * já foi usado nesta permutação (significando que estamos em
         * uma ordem diferente). Caso contrário, pular evita repetições.
         */
        if (i > 0 && src[i] == src[i - 1] && !used[i - 1]) continue;

        used[i] = 1;           /* marca src[i] como usado */
        perm[pos] = src[i];    /* coloca o caractere na posição atual */
        backtrack_select(src, n, perm, pos + 1, used); /* recusa para pos+1 */
        used[i] = 0;           /* desfaz a marcação (backtrack) */
    }
}

/* ------------------------------------------------------------
 * Função: main
 * Objetivo: verificar argumentos, preparar buffers e iniciar o
 *           processo de geração de permutações por backtracking.
 * Regras de saída: retorna 1 em erro (argumentos, malloc falhou,
 *                  string vazia), 0 em sucesso.
 * ------------------------------------------------------------ */
int main(int argc, char **argv)
{
    if (argc != 2) return 1;         /* requer exatamente um argumento */
    const char *in = argv[1];        /* string de entrada (não modificamos) */
    size_t n = my_strlen(in);        /* comprimento da entrada */
    if (n == 0) return 1;            /* trata string vazia como erro */

    /* copia a string de entrada para um buffer mutável `src` */
    char *src = (char *)malloc(n + 1);
    if (!src) return 1;              /* falha de alocação */
    for (size_t i = 0; i < n; ++i) src[i] = in[i];
    src[n] = '\0';                  /* termina a cópia */

    /* ordena os caracteres para garantir ordem lexicográfica nas permutações */
    sort_string(src, n);

    /* prepara o buffer `perm` que recebe cada permutação e o vetor `used` */
    char *perm = (char *)malloc(n + 1);
    if (!perm) { free(src); return 1; }
    int *used = (int *)malloc(sizeof(int) * n);
    if (!used) { free(perm); free(src); return 1; }
    for (size_t i = 0; i < n; ++i) used[i] = 0; /* inicializa marcações */

    /* inicia o backtracking a partir da posição 0 */
    backtrack_select(src, n, perm, 0, used);

    /* libera recursos e encerra com sucesso */
    free(used);
    free(perm);
    free(src);
    return 0;
}
