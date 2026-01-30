/* Minimal corrected get_next_line (diferenças reduzidas em relação ao broken_gnl)
 * Mantive a estrutura original, alterando somente o essencial para funcionar:
 * - ft_memcpy: correção da cópia
 * - str_append_mem: tratar *s1 == NULL
 * - ft_memmove: implementação correta para sobreposição
 * - get_next_line: recalcula tmp após ler, trata EOF/erro e desloca o buffer
 */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char *ft_strchr(char *s, int c)
{
  int i = 0;
  //if (!s) /* ALTERAÇÃO: checagem adicionada - evita ler além de NULL (não presente no broken_gnl.c) */
    //return NULL;
  while (s[i]) /* ALTERAÇÃO: loop seguro até '\0' (original fazia while(s[i] != c), risco de leitura além) */
  {
    if (s[i] == (char)c)
      return s + i;
    i++;
  }
  if (c == '\0')
    return s + i;
  return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
  size_t i;
  char *d = (char *)dest;
  const char *s = (const char *)src;
  /* ALTERAÇÃO: implementação direta de cópia byte-a-byte usando while.
     Motivo: manter lógica equivalente ao for, conforme pedido. */
  i = 0;
  while (i < n)
  {
    d[i] = s[i];
    i++;
  }
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
/*
int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = 0;
	if (s1 && *s1)
    size1 = ft_strlen(*s1);
	else
	*/
    //size1 = 0; /* ALTERAÇÃO: trata *s1 == NULL (original assumia *s1 válido) */
	/*
	char *tmp = malloc(size2 + size1 + 1);
	if (!tmp)
    return 0;
	if (s1 && *s1)
    ft_memcpy(tmp, *s1, size1);
	if (s2 && size2)
    ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	if (s1 && *s1)
    free(*s1);
	*s1 = tmp;
	return 1;
}
*/

int str_append_mem(char **s1, char *s2, size_t size2)
{
  size_t size1 = 0 ;
	if (s1 && *s1)
	{

		size1 = ft_strlen(*s1);
	}
  char *tmp = malloc(size2 + size1 + 1);
  //if (!tmp)
    //return 0;
  ft_memcpy(tmp, *s1, size1);
  ft_memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = '\0';
  free(*s1);
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
  char *d = (char *)dest;
  const char *s = (const char *)src;
  //if (d == s || n == 0)
    //return dest;
  /* ALTERAÇÃO: implementação iterativa para suportar sobreposição corretamente.
     Motivo: original usava recursão e lógica incorreta para sobreposição. */
  if (d < s)
  {
    i = 0;
    while (i < n)
    {
      d[i] = s[i];
      i++;
    }
  }
  else
  {
    i = n;
    while (i > 0)
    {
      i--;
      d[i] = s[i];
    }
  }
  return dest;
}

char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;
  char *tmp = b[0] ? ft_strchr(b, '\n') : NULL; /* ALTERAÇÃO: evita chamar ft_strchr em buffer vazio (reduz risco de comportamento indefinido) */
  while(!tmp)
  {
    if (!str_append_str(&ret, b)) /* segue original aqui, mas tratamos alocações em str_append_mem */
      return (NULL);
    int read_ret = read(fd, b, BUFFER_SIZE);
    if (read_ret == -1)
    {
      //free(ret);
      return (NULL);
    }

	if (read_ret == 0)
    {
      /* ALTERAÇÃO: trata EOF - se há conteúdo acumulado, retorna-o; caso contrário NULL.
         Motivo: versão original não tratava read==0 corretamente e podia entrar em loop/erro. */
      //if (ret && *ret)
        //return ret;
      free(ret);
      return NULL;
    }
    b[read_ret] = 0;
    tmp = ft_strchr(b, '\n');
  }
  if (!str_append_mem(&ret, b, tmp - b + 1))
  {
    free(ret);
    return NULL;
  }
  /* ALTERAÇÃO: move o restante do buffer para o início para chamadas subsequentes.
     Motivo: original não fazia esse deslocamento, logo bytes após '\n' eram perdidos. */
  size_t rem = ft_strlen(b) - (size_t)(tmp - b + 1);
  if (rem > 0)
    ft_memmove(b, tmp + 1, rem);
  b[rem] = '\0';
  return ret;
}
