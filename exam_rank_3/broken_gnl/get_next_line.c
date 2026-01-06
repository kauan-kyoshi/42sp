/*
 * EXERCISE: BROKEN_GNL (Get Next Line)
 *
 * DESCRIPTION:
 * Implement get_next_line that reads line by line from a file descriptor.
 * This version may contain special cases or intentional "bugs".
*/

#include "get_next_line.h"

/*
 * Corrigido `ft_strchr`:
 * - Trata quando `s` é NULL para evitar dereferência.
 * - Percorre até o terminador '\0' em vez de assumir que o caractere
 *   estará presente (anteriormente causava leitura além do buffer).
 * - Retorna position quando encontra `c` e aceita `c == '\0'`.
 */

 /*
 Verifica se o *s existe, caso nao, NULL.
 Retira o iterador e incrementa direto no
 ponteiro.
 Se o c for \0, retorna s
 */
 char *ft_strchr(char *s, int c)
{
  if (!s)
    return NULL;
  while (*s)
  {
    if (*s == (char)c)
      return s;
    s++;
  }
  if (c == '\0')
    return s;
  return NULL;
}

/*
 * Corrigido `ft_memcpy`:
 * - Garante cópia de exatamente `n` bytes em ordem crescente.
 * - Retorna NULL se ambos ponteiros forem NULL (comportamento defensivo).
 * - Evita os loops com índices incorretos que pulavam o primeiro byte.
 */

 /*
 Apaga tudo.
 Verifica de existe dest e src, caso nao, NULL.
 dentro do while copia de src para dest e retorna dest.
 */
void *ft_memcpy(void *dest, const void *src, size_t n)
{
  if (!dest && !src)
    return NULL;
  char *d = dest;
  const char *s = src;
  size_t i = 0;
  while (i < n)
  {
    d[i] = s[i];
    i++;
  }
  return dest;
}

/*
 * `ft_strlen` com checagem NULL para evitar segfaults se chamado
 * com ponteiro nulo (algumas rotinas usam essa verificação).
 */

 /*
 Verificar se s existe, caso nao, NULL.
 */
size_t ft_strlen(char *s)
{
  size_t res = 0;
  if (!s)
    return 0;
  while (*s)
  {
    s++;
    res++;
  }
  return res;
}

/*
 * `str_append_mem` e `str_append_str`:
 * - Tratam o caso em que `*s1` é NULL (concatenação inicial).
 * - Alocam exatamente size1+size2+1 e copiam apenas quando necessário.
 * - Liberam o buffer antigo e atualizam `*s1`.
 * - `str_append_str` aceita `s2 == NULL` como operação nula (retorna 1).
 */


 /*
 verifica se s1 existe, caso sim, size1 = tamanho de s1. se nao, size1 = 0.
 Malloca tmp com size2 + size1 + 1(\0).
 Verifica novamente se s1 existe, caso sim, chama ft_memcpy(size2 + size1 + 1).
 Verifica se s2 existe E se size2 > 0, caso sim,ft_memcpy(tmp + size1, s2, size2)
 Coloca o terminator \0.
 Da free em s1.
 *s1 = tmp
 */
int str_append_mem(char **s1, char *s2, size_t size2)
{
  size_t size1;
  if (*s1)
    size1 = ft_strlen(*s1);
  else
    size1 = 0;
  char *tmp = malloc(size2 + size1 + 1);
  if (!tmp)
    return 0;
  if (*s1)
    ft_memcpy(tmp, *s1, size1);
  if (s2 && size2 > 0)
    ft_memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = '\0';
  free(*s1);
  *s1 = tmp;
  return 1;
}
/*
Apenas verifique se s2 existe, caso nao, retorna (1)

*/
int str_append_str(char **s1, char *s2)
{
  if (!s2)
    return 1;
  return str_append_mem(s1, s2, ft_strlen(s2));
}

/*
 * `ft_memmove` implementado para suportar sobreposição de origem/destino.
 * - Copia para frente quando `dest < src`.
 * - Copia para trás (do fim para o início) quando `dest > src`.
 * - Evita recursão incorreta e índices sem sinal mal manipulados.
 */


/*
Apaga tudo
Verifica se dest E src existem, caso nao, NULL.
*d recebe dest.
*s recebe src.

verifica de d < s, caso sim,
declara um iterador como size_t = 0 e ENQUANTO o iterador i < n, o d[i] = s[i] e incrementa o i++

ou entao se d > s,
declara um iterador como size_t = n e ENQUANTO o iterador i > 0 decrementa o i-- e d[i] = s[i]

por fim retorna dest
*/

void *ft_memmove(void *dest, const void *src, size_t n)
{
  if (!dest && !src)
    return NULL;
  char *d = dest;
  const char *s = src;
  if (d < s)
  {
    size_t i = 0;
    while (i < n)
    {
      d[i] = s[i];
      i++;
    }
  }
  else if (d > s)
  {
    size_t i = n;
    while (i > 0)
    {
      i--;
      d[i] = s[i];
    }
  }
  return dest;
}

/*
 * `get_next_line`:
 * - Usa um buffer estático `b` para armazenar dados lidos entre chamadas.
 * - Valida `fd` e `BUFFER_SIZE` no início para comportamento definido.
 * - Procura por '\n' no buffer atual; enquanto não achar, anexa o conteúdo
 *   do buffer ao `ret` acumulador e lê mais do descritor.
 * - Trata erros de `read` (retorna NULL e libera memória parcial).
 * - No EOF (r == 0): se houver dados acumulados, retorna-os; caso
 *   contrário libera e retorna NULL.
 * - Ao encontrar '\n', anexa até e incluindo '\n', desloca o restante do
 *   buffer para o início com `ft_memmove` e retorna a linha.
 * - Garantia: quando retorna uma string não-NULL, ela é alocada e pode ser
 *   liberada pelo chamador.
 */


/*
Aproveita as 2 primeiras linhas, o resto apaga
Declara um char *nl (newline)
Verifica se fd < 0 OU se o buffer_size <=0, caso sim, NULL.

nl = ft_strchr(b, '\n');

ENQUANTO nl nao existir faça :
	size_t len recebe o tamanho de b
	verifica se len é maior do que 0, caso sim, verifica se !str_append_mem(&ret, b, len), se a alocação falhar:
		dar free no ret e retorna NULL

	ssize_t r recebe read(fd, b, BUFFER_SIZE)
	se r < 0 :
		da free em ret e retorna NULL
	se r == 0:
		verifica se (ret && *ret):
			b[0] = '\0'
			return NULL
		free(ret);
      	b[0] = '\0';
      	return NULL;
	b[r] = '\0';
    nl = ft_strchr(b, '\n');
	
size_t take = nl - b + 1;
  if (!str_append_mem(&ret, b, take))
  {
    free(ret);
    return NULL;
  }
  size_t rem = ft_strlen(b + take);
  ft_memmove(b, b + take, rem + 1);
  return ret;
*/
char *get_next_line(int fd)
{
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;
  char *nl;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return NULL;

  nl = ft_strchr(b, '\n');
  while (!nl)
  {
    size_t len = ft_strlen(b);
    if (len > 0)
    {
      if (!str_append_mem(&ret, b, len))
      {
        free(ret);
        return NULL;
      }
    }
    ssize_t r = read(fd, b, BUFFER_SIZE);
    if (r < 0)
    {
      free(ret);
      return NULL;
    }
    if (r == 0)
    {
      if (ret && *ret)
      {
        b[0] = '\0';
        return ret;
      }
      free(ret);
      b[0] = '\0';
      return NULL;
    }
    b[r] = '\0';
    nl = ft_strchr(b, '\n');
  }

  size_t take = nl - b + 1;
  if (!str_append_mem(&ret, b, take))
  {
    free(ret);
    return NULL;
  }
  size_t rem = ft_strlen(b + take);
  ft_memmove(b, b + take, rem + 1);
  return ret;
}