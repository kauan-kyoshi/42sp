/* Header para a implementação de get_next_line.
 * Contém a definição de BUFFER_SIZE (se não fornecida) e
 * o protótipo da função pública get_next_line.
 */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* Inclui as funções permitidas: malloc/free via stdlib e read via unistd */
# include <stdlib.h>
# include <unistd.h>

/* Se BUFFER_SIZE não for definida no momento da compilação,
 * definimos um valor padrão razoável. O avaliador normalmente
 * define -D BUFFER_SIZE=xx quando compilar.
 */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* Protótipo público: lê a próxima linha do descritor `fd`.
 * Retorna uma string alocada (deve ser liberada com free),
 * incluindo '\n' quando presente, ou NULL em EOF/erro.
 */
char *get_next_line(int fd);

#endif
