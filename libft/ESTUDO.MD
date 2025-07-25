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

11 - memcmp:
int		ft_memcmp(const void *s1, const void *s2, size_t n);

compara dois blocos de memória "s1 e s2" byte por byte, até um determinado número de bytes "n". Ela retorna um valor inteiro que indica a relação de ordem entre os dois blocos (0 se forem iguais, negativo se o primeiro byte diferente em s1 < s2 e positivo se s1 > s2).

--------------------------------------------------------------------------------------------

12 - memcpy:
void	*ft_memcpy(void *dest, const void *src, size_t n);

copia um bloco de memória de uma localização para outra.

--------------------------------------------------------------------------------------------

13 - memmove:
void	*ft_memmove(void *dest, const void *src, size_t n);

copiar um bloco de memória de uma localização para outra, lidando corretamente com situações onde os blocos de memória de origem e destino se sobrepõem.

--------------------------------------------------------------------------------------------

14 - memset:
void	*ft_memset(void *s, int c, size_t n);

preenche um bloco de memória com um valor específico. Ela pega um determinado número de bytes "n" em um bloco de memória apontado por "s" e define o valor de cada um desses bytes para o valor de "c".

--------------------------------------------------------------------------------------------

15 - putchar_fd:
void	ft_putchar_fd(char c, int fd);

usa o write para exibir o caracter "c" no output determinado por "fd".

--------------------------------------------------------------------------------------------
16 - putendl_fd:
void	ft_putendl_fd(char *s, int fd);

usa o write para exibir a string "s" no output determinado por "fd" com uma quebra de linha.

--------------------------------------------------------------------------------------------

17 - putnbr_fd:
void	ft_putnbr_fd(int n, int fd);

usa o write para exibir o inteiro "n" no output determinado por "fd".

--------------------------------------------------------------------------------------------

18 - putstr_fd:
void	ft_putstr_fd(char *s, int fd);

usa o write para exibir a string "s" no output determinado por "fd".

--------------------------------------------------------------------------------------------

19 - split:
char	**ft_split(char const *s, char c);

recebe uma string "s" e um caractere "c" (delimitador) e retorna um array de strings, onde cada string é uma "palavra" separada pelo delimitador "c".

static int count_words(const char *str, char c): 
para 'contar' as palavras e determinar quantas strings precisarão ser alocadas.

static char *word_dup(const char *str, int start, int finish):
para determinar o tamanho das strings, duplicar e ja alocar memoria suficiente para cada string.

--------------------------------------------------------------------------------------------

20 - strchr:
char	*ft_strchr(const char *s, int c);

localiza a primeira ocorrência de um caractere específico (c) em uma string (s). Se o caractere for encontrado, a função retorna um ponteiro que aponta para a primeira ocorrência.

--------------------------------------------------------------------------------------------

21 - strdup:
char	*ft_strdup(const char *s1);

duplica uma string. Ela aloca uma nova memória para a cópia e então copia o conteúdo da string original para essa nova memória.

--------------------------------------------------------------------------------------------

22 - striteri:
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

itera sobre uma string, aplicando uma função fornecida a cada caractere juntamente com seu índice.

--------------------------------------------------------------------------------------------

23 - strjoin:
char	*ft_strjoin(char const *s1, char const *s2);

concatena duas strings

--------------------------------------------------------------------------------------------

24- strlcat:
size_t	ft_strlcat(char *dst, const char *src, size_t size);

concatena strings de forma segura, evitando estouros de buffer. Ela tenta adicionar a string de origem (src) à string de destino (dst), mas com um limite estrito de tamanho. O retorno da função é o comprimento total da string que teria sido criada se não houvesse limite de tamanho.
Se o valor de retorno for maior ou igual a size, significa que a string original era muito grande para caber no buffer de destino.

--------------------------------------------------------------------------------------------

25 - strlcpy:
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

Ela copia até um determinado número de bytes do início da string de origem (src) para o destino (dest), garantindo que o destino seja terminado em nulo, se houver espaço.

--------------------------------------------------------------------------------------------
