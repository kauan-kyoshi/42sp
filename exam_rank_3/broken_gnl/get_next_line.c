#include "get_next_line.h"

/* gnl_strlen: retorna comprimento de string (0 se ponteiro NULL) */
static size_t gnl_strlen(const char *s)
{
    size_t i = 0;
    if (!s) return 0;       /* protege contra ponteiro NULL */
    while (s[i]) i++;      /* itera até o terminador '\0' */
    return i;
}

/* gnl_strchr: procura caractere `c` em `s`; retorna apontador ou NULL */
static char *gnl_strchr(const char *s, int c)
{
    if (!s) return NULL;   /* se s for NULL, não há busca */
    while (*s) {           /* percorre até terminador */
        if (*s == (char)c) return (char *)s; /* encontrou */
        s++;
    }
    return NULL;           /* não encontrou */
}

/*
 * gnl_strjoin: concatena a string existente `s1` (pode ser NULL) com
 * `s2_len` bytes vindos de `s2`. A função aloca uma nova string, copia
 * os conteúdos e libera s1. Retorna a nova string (ou NULL em erro).
 */
static char *gnl_strjoin(char *s1, const char *s2, size_t s2_len)
{
    size_t len1 = gnl_strlen(s1);                  /* comprimento atual */
    char *res = malloc(len1 + s2_len + 1);         /* aloca espaço total */
    if (!res) return NULL;                         /* erro de malloc */
    size_t i = 0;
    for (; i < len1; ++i) res[i] = s1[i];          /* copia s1, se existir */
    for (size_t j = 0; j < s2_len; ++j)            /* copia `s2_len` bytes de s2 */
        res[i + j] = s2[j];
    res[len1 + s2_len] = '\0';                    /* termina string */
    if (s1) free(s1);                              /* libera antigo stash */
    return res;                                    /* retorna nova string */
}

/* gnl_substr_dup: duplica os primeiros n bytes de s em uma nova string terminada em '\0' */
static char *gnl_substr_dup(const char *s, size_t n)
{
    char *res = malloc(n + 1); /* +1 para o terminador */
    if (!res) return NULL;     /* malloc falhou */
    for (size_t i = 0; i < n; ++i) res[i] = s[i];
    res[n] = '\0';
    return res;                /* string alocada do tamanho pedido */
}

/*
 * get_next_line: retorna a próxima linha do descritor `fd`.
 * Comportamento resumido:
 * - Mantém um `stash` estático entre chamadas com bytes lidos mas não ainda
 *   consumidos (restos após a última linha retornada).
 * - Lê de `fd` em blocos de BUFFER_SIZE até encontrar '\n' ou EOF.
 * - Quando encontra '\n', devolve a linha incluindo '\n' e atualiza o stash.
 * - Em EOF devolve o restante acumulado (se houver) ou NULL se não houver dados.
 */
char *get_next_line(int fd)
{
    static char *stash = NULL; /* guarda dados lidos e não consumidos */
    char buf[BUFFER_SIZE];     /* buffer de leitura temporário */
    ssize_t r;

    /* validação simples do descritor e do BUFFER_SIZE */
    if (fd < 0 || BUFFER_SIZE <= 0) return NULL;

    /* Enquanto não houver '\n' no stash, lemos mais do descritor */
    while (!gnl_strchr(stash, '\n')) {
        r = read(fd, buf, BUFFER_SIZE); /* tenta ler até BUFFER_SIZE bytes */
        if (r < 0) {                   /* erro de leitura */
            if (stash) { free(stash); stash = NULL; } /* libera antes de sair */
            return NULL;               /* propagamos o erro retornando NULL */
        }
        if (r == 0) break; /* EOF: sai do loop e processa o que há no stash */
        /* anexa os bytes lidos (r bytes) ao stash */
        stash = gnl_strjoin(stash, buf, (size_t)r);
        if (!stash) return NULL; /* erro de malloc durante concatenação */
    }

    /* Se não houver nada no stash => nada a retornar (EOF sem dados) */
    if (!stash || stash[0] == '\0') {
        if (stash) { free(stash); stash = NULL; } /* garante liberar stash */
        return NULL; /* sem dados => NULL conforme especificação */
    }

    /* Procura por '\n' no stash para determinar se há uma linha completa */
    char *nl = gnl_strchr(stash, '\n');
    if (nl) {
        /* calcula o tamanho da linha a retornar (inclusive '\n') */
        size_t line_len = (size_t)(nl - stash) + 1;
        /* duplica os primeiros line_len bytes para retornar ao chamador */
        char *line = gnl_substr_dup(stash, line_len);
        if (!line) { free(stash); stash = NULL; return NULL; }
        /* atualiza o stash para conter apenas o que ficou após a linha retornada */
        size_t rem = gnl_strlen(stash) - line_len;
        if (rem > 0) {
            /* copia os bytes restantes para nova área alocada */
            char *new_stash = gnl_substr_dup(stash + line_len, rem);
            if (!new_stash) { free(line); free(stash); stash = NULL; return NULL; }
            free(stash);          /* libera o antigo stash */
            stash = new_stash;    /* stash agora contém apenas o remanescente */
        } else {
            /* não sobrou nada: libera stash e zera o ponteiro estático */
            free(stash);
            stash = NULL;
        }
        return line; /* retorna a linha incluindo '\n' */
    }

    /* Se não há '\n' no stash, então estamos em EOF e devolvemos tudo que há */
    char *line = gnl_substr_dup(stash, gnl_strlen(stash));
    free(stash); /* limpa stash */
    stash = NULL;
    return line; /* retorna o conteúdo final (pode ser string vazia se arquivo vazio) */
}
