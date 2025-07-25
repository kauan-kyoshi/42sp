1 - Atoi:
int		ft_atoi(const char *str);

Recebe uma string de um número e converte para um inteiro.

--------------------------------------------------------------------------------------------

2 - Bzro:
void	ft_bzero(void *s, size_t n);

Zera os "n" bytes da string passada como parametro.

--------------------------------------------------------------------------------------------

3 - calloc:
void	*ft_calloc(size_t nmemb, size_t size);

Aloca memória para um array de "nmemb" elementos, onde cada elemento tem um tamanho de "size" bytes. Além de alocar a memória, ela inicializa todos os bytes da memória alocada com zero.

--------------------------------------------------------------------------------------------

4 - isalnum:
int		ft_isalnum(int c);

Recebe um int e verifica se a representação desse int na tabela ascii é alfanumerico.

--------------------------------------------------------------------------------------------

5 - isalpha:
int		ft_isalpha(int c);

Recebe um int e verifica se a representação desse int na tabela ascii é alfabetico.

--------------------------------------------------------------------------------------------

6 - isascii:
int		ft_isascii(int c);

Recebe um int e verifica se está dentro da tabela ascii (0~127).

--------------------------------------------------------------------------------------------

7 - isdigit:
int		ft_isdigit(int c);

Recebe um int e verifica se a representação desse int na tabela ascii é um digito.

--------------------------------------------------------------------------------------------

8 - isprint:
int		ft_isprint(int c);

Recebe um int e verifica se a representação desse int na tabela ascii é "printavel".

--------------------------------------------------------------------------------------------

9 - itoa:
char	*ft_itoa(int n);

ao contrario do "atoi", recebe um numero inteiro e retorna esse numero convertido para string.

--------------------------------------------------------------------------------------------

10 - memchr:
void	*ft_memchr(const void *s, int c, size_t n);

Busca a primeira ocorrência de um caractere específico "c" dentro de um bloco de memória apontado por "*s" de tamanho "n".

--------------------------------------------------------------------------------------------
