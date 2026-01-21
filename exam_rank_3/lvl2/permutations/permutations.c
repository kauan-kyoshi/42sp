/* inclui definições para alocação e conversão de I/O */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* puts */

/* Implementa as permutações em ordem lexicográfica.
 * O arquivo adiciona comentários linha a linha explicando a lógica.
 */

/* Computa o comprimento de uma string C-terminada por '\0'.
 * Recebe `s` e retorna o número de caracteres antes do terminador.
 */
static size_t my_strlen(const char *s)
{
    size_t i = 0;           /* índice de iteração começando em 0 */
    if (!s) return 0;      /* se ponteiro nulo, comprimento 0 */
    while (s[i]) i++;      /* avança até encontrar '\0' */
    return i;              /* retorna comprimento contado */
}

/* Troca os conteúdos de dois caracteres apontados por `a` e `b`. */
static void swap_char(char *a, char *b)
{
    char t = *a;           /* guarda temporariamente o valor em *a */
    *a = *b;               /* copia o valor de *b para *a */
    *b = t;                /* restaura o antigo *a em *b */
}

/* Inverte (reverse) a substring de `s` entre os índices `l` e `r` (inclusivo).
 * Usa `swap_char` para trocar pares de caracteres até o meio.
 */
static void reverse_range(char *s, size_t l, size_t r)
{
    while (l < r) {        /* enquanto não cruzaram os índices */
        swap_char(&s[l], &s[r]); /* troca s[l] e s[r] */
        l++;                /* aproxima a borda esquerda do centro */
        r--;                /* aproxima a borda direita do centro */
    }
}

/* Gera a próxima permutação lexicográfica de `s` com comprimento `n`.
 * Retorna 1 se conseguiu gerar a próxima permutação, 0 se `s` já era
 * a última (maior) permutação.
 *
 * Algoritmo (padrão next_permutation):
 * 1) encontra o maior índice i tal que s[i] < s[i+1]; se não existir,
 *    a sequência está em ordem decrescente (última permutação).
 * 2) encontra o maior índice j > i tal que s[j] > s[i].
 * 3) troca s[i] e s[j].
 * 4) inverte a subsequência s[i+1 .. n-1] para obter a menor ordem
 *    possível da sufíxio após a posição i.
 */
static int next_permutation(char *s, size_t n)
{
    if (n < 2) return 0;   /* sequências de comprimento <2 não têm permutações */
    /* procura o maior i tal que s[i] < s[i+1] */
    long i = (long)n - 2;  /* começa em n-2 (penúltimo índice válido) */
    while (i >= 0 && !(s[i] < s[i+1])) i--; /* move para a esquerda até achar */
    if (i < 0) return 0;   /* não encontrou: já estamos na última permutação */
    /* procura o maior j > i tal que s[j] > s[i] */
    long j = (long)n - 1;  /* começa no último índice */
    while (j > i && !(s[j] > s[i])) j--; /* move para a esquerda até achar */
    /* troca os valores em i e j */
    swap_char(&s[i], &s[j]);
    /* reverte o sufixo que fica após i para obter a menor ordem possível */
    reverse_range(s, (size_t)i + 1, n - 1);
    return 1;              /* houve próxima permutação */
}

/* Ordenação simples por inserção (insertion sort) para ordenar a string
 * inicialmente em ordem crescente. Isso garante que a primeira permutação
 * impressa seja a lexicograficamente menor.
 */
static void sort_string(char *s, size_t n)
{
    for (size_t i = 1; i < n; ++i) { /* começa em 1, o subarray [0..i-1] está ordenado */
        char key = s[i];     /* elemento a ser inserido na posição correta */
        long j = (long)i - 1;/* j percorre a parte ordenada para encontrar o local */
        while (j >= 0 && s[j] > key) {
            s[j+1] = s[j];  /* desloca elemento maior para a direita */
            j--;            /* move para a esquerda */
        }
        s[j+1] = key;       /* insere a chave na posição correta */
    }
}

/* Função principal: espera um único argumento (a string de entrada) e imprime
 * todas as permutações distintas em ordem lexicográfica, uma por linha.
 */
int main(int argc, char **argv)
{
    if (argc != 2) return 1; /* requer exatamente um argumento */
    const char *in = argv[1]; /* ponteiro para a string de entrada */
    size_t n = my_strlen(in); /* comprimento da string de entrada */
    if (n == 0) return 1;    /* se string vazia, sai com erro */

    char *s = (char *)malloc(n + 1); /* aloca espaço para copiar a string (+1 para \0) */
    if (!s) return 1;        /* falha de alocação: sai com erro */
    for (size_t i = 0; i < n; ++i) s[i] = in[i]; /* copia caracter a caracter */
    s[n] = '\0';           /* termina a string copiada */

    /* ordena a string copiada para iniciar na menor permutação lexicográfica */
    sort_string(s, n);

    /* imprime a permutação atual e itera chamando next_permutation
     * até que não haja mais permutações.
     */
    do {
        puts(s);            /* imprime a string seguida de '\n' */
    } while (next_permutation(s, n)); /* gera a próxima enquanto existir */

    free(s);                /* libera a memória alocada */
    return 0;               /* encerra com código de sucesso */
}
