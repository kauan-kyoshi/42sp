/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 *
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
*/

#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
  if (!s) return NULL; /* alterado: trata entrada NULL */
  while (*s)
  {
    if (*s == (char)c)
      return s; /* alterado: retorna quando encontra */
    s++;
  }
  if (c == 0)
    return s; /* alterado: permite buscar '\0' */
  return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
  size_t i;
  for (i = 0; i < n; i++)
    ((char *)dest)[i] = ((char *)src)[i]; /* alterado: cópia direta correta */
  return dest;
}

size_t ft_strlen(char *s)
{
  size_t res = 0;
  while (*s)
  {
    s++;
    res++;
  }
  return res;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
  size_t size1 = 0;
  if (*s1)
    size1 = ft_strlen(*s1); /* alterado: trata *s1 == NULL */
  char *tmp = malloc(size2 + size1 + 1); /* alterado: aloca mesmo com size1==0 */
  if (!tmp)
    return 0;
  if (size1 > 0)
    ft_memcpy(tmp, *s1, size1); /* alterado: copia só se fonte existir */
  ft_memcpy(tmp + size1, s2, size2); /* alterado: copia os novos dados */
  tmp[size1 + size2] = '\0';
  if (*s1)
    free(*s1); /* alterado: libera apenas se alocado */
  *s1 = tmp;
  return 1;
}

int str_append_str(char **s1, char *s2)
{
  return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
  size_t i;
  if (dest == src || n == 0)
    return dest; /* alterado: nada a fazer */
  if (dest < src)
  {
    for (i = 0; i < n; i++)
      ((char *)dest)[i] = ((char *)src)[i]; /* alterado: cópia para frente */
  }
  else
  {
    for (i = n; i > 0; i--)
      ((char *)dest)[i - 1] = ((char *)src)[i - 1]; /* alterado: cópia reversa para sobreposição */
  }
  return dest;
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;
  char *tmp = ft_strchr(b, '\n');
  while (!tmp)
  {
    if (b[0] != '\0')
    {
      if (!str_append_str(&ret, b))
      {
        free(ret);
        return NULL;
      }
    }
    int read_ret = read(fd, b, BUFFER_SIZE); /* alterado: lê mais para o buffer */
    if (read_ret == -1)
    {
      if (ret)
        free(ret);
      return NULL; /* alterado: libera em caso de erro */
    }
    if (read_ret == 0) /* alterado: tratamento de EOF */
    {
      if (ret && ret[0] != '\0')
        return ret; /* retorna o restante */
      if (ret)
        free(ret);
      return NULL;
    }
    b[read_ret] = '\0';
    tmp = ft_strchr(b, '\n'); /* alterado: atualiza busca após leitura */
  }
  if (!str_append_mem(&ret, b, (size_t)(tmp - b + 1)))
  {
    if (ret) free(ret);
    return NULL;
  }
  /* desloca dados restantes após o newline para o início de b */
  size_t rem = ft_strlen(tmp + 1);
  ft_memmove(b, tmp + 1, rem + 1); /* alterado: move restante */
  return ret;
}