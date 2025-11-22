/*
 * filter.c
 * Implementação que substitui todas as ocorrências do padrão fornecido
 * pelo mesmo número de '*' lidos de stdin para stdout.
 * Abaixo cada linha/chunk principal recebe comentários explicativos.
 */

#define _GNU_SOURCE /* ativa extensões GNU para memmem() */

#include <unistd.h> /* read, write, STDIN_FILENO, STDOUT_FILENO */
#include <stdlib.h> /* malloc, free, realloc */
#include <stdio.h>  /* perror */
#include <string.h> /* strlen, memcmp, memmove, memmem */
#include <errno.h>  /* errno (não usado diretamente, mas perror usa) */

#define BUFSIZE 4096 /* tamanho de bloco para leituras temporárias */

/*
 * write_all: escreve `count` bytes de `buf` em `fd`, repetindo write
 * até que todo o conteúdo seja escrito ou ocorra erro.
 * Retorna 0 em sucesso, -1 em erro.
 */
static int write_all(int fd, const void *buf, size_t count)
{
    const char *p = buf;       /* ponteiro para percorrer o buffer */
    size_t left = count;       /* quantos bytes faltam escrever */
    while (left > 0) {
        ssize_t w = write(fd, p, left); /* tentativa de escrita */
        if (w < 0) return -1;           /* erro de escrita */
        p += w;                         /* avança o ponteiro */
        left -= (size_t)w;              /* decrementa o restante */
    }
    return 0; /* tudo escrito */
}

int main(int argc, char **argv)
{
    /* validação simples dos argumentos: aceita exatamente 1 argumento */
    if (argc != 2) return 1;
    char *pat = argv[1];          /* padrão passado na linha de comando */
    size_t plen = strlen(pat);    /* comprimento do padrão */
    if (plen == 0) return 1;      /* argumento vazio -> erro */

    /*
     * Estratégia: ler todo o stdin em memória (buffer dinâmico `data`),
     * em seguida fazer um único passe substituindo ocorrências.
     * Isso simplifica o tratamento de ocorrências que cruzam limites
     * de leitura e é aceitável para entradas de tamanho razoável.
     */
    size_t cap = BUFSIZE;              /* capacidade atual do buffer `data` */
    char *data = malloc(cap);          /* buffer dinâmico para armazenar stdin */
    if (!data) { perror("Error"); return 1; } /* erro de alloc */
    size_t len = 0;                    /* quantidade atual de bytes em `data` */

    /* tmpbuf é usado para leituras parciais; depois copiamos para `data` */
    char *tmpbuf = malloc(BUFSIZE);
    if (!tmpbuf) { perror("Error"); free(data); return 1; }

    /* lê repetidamente de stdin até EOF, redimensionando `data` conforme necessário */
    ssize_t rr;
    while ((rr = read(STDIN_FILENO, tmpbuf, BUFSIZE)) > 0) {
        /* se não há espaço suficiente, dobra a capacidade até caber */
        if (len + (size_t)rr > cap) {
            size_t newcap = cap * 2;
            while (newcap < len + (size_t)rr) newcap *= 2;
            char *tmp = realloc(data, newcap); /* aumenta o buffer */
            if (!tmp) { perror("Error"); free(data); free(tmpbuf); return 1; }
            data = tmp; cap = newcap; /* atualiza ponteiro e capacidade */
        }
        /* copia os bytes lidos temporariamente para o buffer final */
        memmove(data + len, tmpbuf, (size_t)rr);
        len += (size_t)rr; /* atualiza tamanho usado */
    }
    if (rr < 0) { /* se read retornou erro */
        perror("Error"); free(data); free(tmpbuf); return 1;
    }
    free(tmpbuf); /* tmpbuf não é mais necessário */

    /* preenche um buffer 'stars' com '*' do mesmo comprimento do padrão */
    char *stars = malloc(plen);
    if (!stars) { perror("Error"); free(data); return 1; }
    for (size_t i = 0; i < plen; ++i) stars[i] = '*';

    /*
     * Varremos o buffer `data` byte a byte. Quando encontramos a sequência
     * que coincide com `pat` (memcmp == 0) escrevemos `plen` asteriscos
     * e avançamos `i` em `plen`. Caso contrário escrevemos apenas o byte
     * atual e avançamos `i` em 1.
     */
    size_t i = 0;
    while (i < len) {
        /* se ainda há espaço suficiente para comparar o padrão inteiro */
        if (i + plen <= len && memcmp(data + i, pat, plen) == 0) {
            /* encontramos uma ocorrência: escrever os '*' equivalentes */
            if (write_all(STDOUT_FILENO, stars, plen) < 0) {
                perror("Error"); free(data); free(stars); return 1; }
            i += plen; /* pula o padrão lido */
        } else {
            /* não há ocorrência aqui: escreve apenas o próximo byte */
            if (write_all(STDOUT_FILENO, data + i, 1) < 0) {
                perror("Error"); free(data); free(stars); return 1; }
            i++; /* avança um byte */
        }
    }

    /* libera recursos e sai com sucesso */
    free(data);
    free(stars);
    return 0;
}
