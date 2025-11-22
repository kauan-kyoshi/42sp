/*
 * n_queens.c
 * Implementação do problema das N rainhas usando backtracking.
 * Comentários linha-a-linha explicam a lógica e as decisões.
 */

#include <stdlib.h> /* atoi, malloc, free */
#include <unistd.h> /* write */

/*
 * is_safe:
 *  - `cols` é um vetor onde cols[j] = linha onde a rainha foi colocada
 *    na coluna j (0..col-1 já preenchidas).
 *  - `col` é a coluna atual onde queremos testar a `row`.
 *  - Retorna 1 se é seguro colocar a rainha em (col,row), 0 caso contrário.
 */
static int is_safe(int *cols, int col, int row)
{
    /* percorre todas as colunas já preenchidas */
    for (int j = 0; j < col; ++j) {
        int r = cols[j];           /* linha da rainha na coluna j */
        if (r == row) return 0;    /* mesma linha -> conflito */
        int diff = r - row;        /* diferença de linhas */
        if (diff < 0) diff = -diff;/* valor absoluto da diferença */
        if (diff == col - j) return 0; /* mesma diagonal -> conflito */
    }
    return 1; /* sem conflitos detectados */
}


/*
 * int_to_str:
 *  - Converte `value` (>=0) em caracteres decimais escritos em `buf`.
 *  - Retorna o número de bytes escritos.
 *  - Implementado manualmente para evitar uso de funções proibidas (sprintf).
 */
static int int_to_str(int value, char *buf)
{
    if (value == 0) {          /* caso zero é especial */
        buf[0] = '0';
        return 1;
    }
    int i = 0;
    int v = value;
    char tmp[20];              /* temporário para dígitos invertidos */
    while (v > 0) {            /* extrai dígitos em ordem reversa */
        tmp[i++] = (char)('0' + (v % 10));
        v /= 10;
    }
    /* copia os dígitos na ordem correta para buf */
    int k = 0;
    while (i > 0) {
        buf[k++] = tmp[--i];
    }
    return k;                  /* tamanho escrito em buf */
}


/*
 * print_solution:
 *  - Recebe `cols` com uma solução completa (cols[0..n-1]) e imprime
 *    no formato exigido: "p0 p1 p2 ... pn-1\n" usando `write`.
 */
static void print_solution(int *cols, int n)
{
    char numbuf[32];           /* buffer temporário para representação decimal */
    for (int i = 0; i < n; ++i) {
        int len = int_to_str(cols[i], numbuf); /* converte cols[i] */
        /* escreve os dígitos; checamos retorno para satisfazer -Werror */
        if (write(1, numbuf, len) < 0) { /* ignoramos erro de escrita */ }
        /* escreve espaço entre números ou nova linha ao final */
        if (i + 1 < n) {
            if (write(1, " ", 1) < 0) { }
        } else {
            if (write(1, "\n", 1) < 0) { }
        }
    }
}


/*
 * solve_rec:
 *  - Função recursiva que tenta colocar uma rainha na coluna `col`.
 *  - `cols` guarda as posições já escolhidas para colunas anteriores.
 *  - Se `col == n`, uma solução completa foi encontrada e é impressa.
 */
static void solve_rec(int *cols, int col, int n)
{
    if (col == n) {
        /* todas as colunas preenchidas -> solução completa */
        print_solution(cols, n);
        return;
    }
    /* tenta todas as linhas possíveis para a coluna atual */
    for (int row = 0; row < n; ++row) {
        if (is_safe(cols, col, row)) { /* se não houver conflito */
            cols[col] = row;           /* coloca rainha em (col,row) */
            solve_rec(cols, col + 1, n); /* recusa para próxima coluna */
            /* ao retornar, desfazemos implicitamente a escolha (sobrescrevemos depois) */
        }
    }
}


/*
 * main:
 *  - Valida argumentos, aloca vetor `cols` e inicia o backtracking.
 *  - Respeita as regras do enunciado quanto às funções permitidas.
 */
int main(int argc, char **argv)
{
    if (argc != 2) return 1;    /* requer exatamente um argumento */
    int n = atoi(argv[1]);      /* converte para inteiro */
    if (n <= 0) return 1;       /* tratamos n<=0 como erro de entrada */

    /* aloca vetor para guardar a linha de cada coluna */
    int *cols = (int *)malloc(sizeof(int) * n);
    if (!cols) return 1;        /* falha de alocação -> sai com erro */

    solve_rec(cols, 0, n);      /* inicia o backtracking a partir da coluna 0 */

    free(cols);                 /* libera memória antes de sair */
    return 0;                   /* sucesso */
}
