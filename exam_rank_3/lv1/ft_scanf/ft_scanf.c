#include <stdarg.h> /* macros para argumentos variádicos: va_start, va_arg, va_end */
#include <stdio.h>  /* FILE, fgetc, ungetc, ferror, stdin */
#include <ctype.h>  /* isspace, isdigit */

/* match_space: consome espaços do arquivo `f` */
int match_space(FILE *f) /* função recebe FILE* e retorna int */
{
    int c; /* variável para armazenar cada caractere lido */
    int seen = 0; /* flag para indicar se vimos pelo menos um espaço */
    while ((c = fgetc(f)) != EOF) /* lê caracteres até EOF */
    {
        if (!isspace(c)) /* se o caractere lido não for espaço */
        {
            ungetc(c, f); /* devolve-o ao fluxo */
            return 1; /* sucesso: há um caractere não-espacial */
        }
        seen = 1; /* marcamos que vimos espaço(s) */
    }
    /* se chegamos aqui, EOF foi alcançado */
    if (seen)
        return 1; /* se vimos espaços antes do EOF, consideramos casamento bem-sucedido */
    return -1; /* EOF sem ver nada -> sinaliza término */
}

/* match_char: tenta casar um caractere literal do formato com o próximo caractere do fluxo */
int match_char(FILE *f, char c)
{
    int r = fgetc(f); /* lê próximo caractere */
    if (r == EOF)
        return -1; /* EOF -> falha */
    if (r == (unsigned char)c) /* se bate com o literal */
        return 1; /* sucesso */
    ungetc(r, f); /* não bateu: devolve o caractere lido */
    return 0; /* não casou */
}

/* scan_char: lê um caractere e grava no ponteiro fornecido por va_list */
int scan_char(FILE *f, va_list ap)
{
    int r = fgetc(f); /* lê um byte do fluxo */
    if (r == EOF)
        return -1; /* EOF -> falha */
    char *p = va_arg(ap, char *); /* obtém argumento: espera um char* */
    *p = (char)r; /* escreve o caractere lido no destino */
    return 1; /* uma conversão bem-sucedida */
}

/* scan_int: lê um inteiro decimal (com sinal) e grava no int* passado */
int scan_int(FILE *f, va_list ap)
{
    int c; /* leitura temporária */
    long sign = 1; /* sinal do número */
    long val = 0; /* valor acumulado */
    int any = 0; /* se ao menos um dígito foi lido */

    while ((c = fgetc(f)) != EOF && isspace(c)) /* pula espaços iniciais */
        ;
    if (c == EOF)
        return -1; /* EOF prematuro */

    if (c == '+' || c == '-') /* trata sinal */
    {
        if (c == '-')
            sign = -1; /* ajusta sinal */
        c = fgetc(f); /* lê próximo após sinal */
    }

    while (c != EOF && isdigit(c)) /* enquanto for dígito */
    {
        any = 1; /* marcamos que lemos dígito */
        val = val * 10 + (c - '0'); /* acumula valor */
        c = fgetc(f); /* lê próximo */
    }

    if (c != EOF)
        ungetc(c, f); /* devolve primeiro não-dígito */

    if (!any)
        return 0; /* nenhuma conversão: não havia dígitos */

    int *p = va_arg(ap, int *); /* obtém destino (int*) */
    *p = (int)(val * sign); /* escreve valor convertido */
    return 1; /* sucesso */
}

/* scan_string: lê uma palavra (sequência sem espaços) e grava no buffer passado */
int scan_string(FILE *f, va_list ap)
{
    int c; /* leitura temporária */
    char *buf = va_arg(ap, char *); /* destino (char*) */
    int any = 0; /* se lemos ao menos um caractere */

    while ((c = fgetc(f)) != EOF && isspace(c)) /* pula espaços iniciais */
        ;
    if (c == EOF)
        return -1; /* EOF sem dados */

    while (c != EOF && !isspace(c)) /* enquanto não encontrar espaço */
    {
        *buf++ = (char)c; /* copia caractere para o buffer */
        any = 1; /* registramos que copiamos algo */
        c = fgetc(f); /* lê próximo */
    }

    if (c != EOF)
        ungetc(c, f); /* devolve separador lido */

    if (!any)
        return 0; /* não leu caracteres válidos */

    *buf = '\0'; /* termina string */
    return 1; /* sucesso */
}

/* match_conv: identifica a conversão no formato e chama a função correspondente */
int match_conv(FILE *f, const char **format, va_list ap)
{
    switch (**format) /* olha o caractere do formato apontado por *format */
    {
    case 'c':
        return scan_char(f, ap); /* %c */
    case 'd':
        match_space(f); /* %d: pula espaços antes de ler inteiro */
        return scan_int(f, ap);
    case 's':
        match_space(f); /* %s: pula espaços antes de ler string */
        return scan_string(f, ap);
    case EOF:
        return -1; /* formato inválido */
    default:
        return -1; /* conversão não suportada */
    }
}

/* ft_vfscanf: loop principal que interpreta a string de formato e consome a entrada */
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    int nconv = 0; /* contador de conversões bem-sucedidas */

    int c = fgetc(f); /* verifica se arquivo está em EOF */
    if (c == EOF)
        return EOF; /* EOF no início -> retorna EOF */
    ungetc(c, f); /* devolve caractere lido */

    while (*format) /* percorre cada caractere do formato */
    {
        if (*format == '%') /* especificador de conversão */
        {
            format++; /* avança para o código da conversão */
            if (match_conv(f, &format, ap) != 1) /* tenta fazer a conversão */
                break; /* falhou -> interrompe */
            else
                nconv++; /* conta conversão bem-sucedida */
        }
        else if (isspace((unsigned char)*format)) /* espaço no formato: casa espaços na entrada */
        {
            if (match_space(f) == -1)
                break; /* se não há input -> interrompe */
        }
        else if (match_char(f, *format) != 1) /* caractere literal no formato */
            break; /* não bateu -> interrompe */
        format++; /* avança no formato */
    }

    if (ferror(f))
        return EOF; /* erro de I/O -> retorna EOF */
    return nconv; /* retorna número de conversões realizadas */
}

/* ft_scanf: função pública que usa stdin */
int ft_scanf(const char *format, ...)
{
    va_list ap; /* lista de argumentos */
    int ret; /* resultado */

    va_start(ap, format); /* inicia va_list */
    ret = ft_vfscanf(stdin, format, ap); /* delega em stdin */
    va_end(ap); /* finaliza va_list */
    return ret; /* retorna resultado */
}