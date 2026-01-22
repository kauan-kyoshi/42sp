# Enunciado: ft_scanf

Assignment name  : ft_scanf
Expected files   : ft_scanf.c
Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Escreva uma função chamada `ft_scanf` que irá imitar o `scanf` real com as seguintes restrições:

- Ela deverá tratar apenas as conversões: `s`, `d` e `c`.
- Não é necessário tratar as opções `*`, `m` e `'`.
- Não é necessário tratar a largura máxima de campo (maximum field width).
- Não é necessário tratar os modificadores de tipo (`h`, `hh`, `l`, etc.).
- Não é necessário tratar conversões que começam com `%n$`.

Sua função deve ser declarada da seguinte forma:

```
int ft_scanf(const char *, ... );
```

No diretório fornecido você encontrará um ficheiro contendo parte do código de que precisará — você só terá que completá-lo.

Para testar o seu programa, compare os resultados com os do `scanf` real.

Dica: pode ser útil consultar o manual (`man`) do `scanf`.

```c
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
        // You may insert code here
    return (0);
}

int match_char(FILE *f, char c)
{
        // You may insert code here
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_int(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}

int scan_string(FILE *f, va_list ap)
{
        // You may insert code here
    return (0);
}


int     match_conv(FILE *f, const char **format, va_list ap)
{
        switch (**format)
        {
                case 'c':
                        return scan_char(f, ap);
                case 'd':
                        match_space(f);
                        return scan_int(f, ap);
                case 's':
                        match_space(f);
                        return scan_string(f, ap);
                case EOF:
                        return -1;
                default:
                        return -1;
        }
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
        int nconv = 0;

        int c = fgetc(f);
        if (c == EOF)
                return EOF;
        ungetc(c, f);

        while (*format)
        {
                if (*format == '%')
                {
                        format++;
                        if (match_conv(f, &format, ap) != 1)
                                break;
                        else
                                nconv++;
                }
                else if (isspace(*format))
                {
                        if (match_space(f) == -1)
                                break;
                }
                else if (match_char(f, *format) != 1)
                        break;
                format++;
        }

        if (ferror(f))
                return EOF;
        return nconv;
}


int ft_scanf(const char *format, ...)
{
        // ...
        int ret = ft_vfscanf(stdin, format, ap);
        // ...
        return ret;
}

```

Boa sorte — complete as funções indicadas e verifique o comportamento comparando com `scanf`.
