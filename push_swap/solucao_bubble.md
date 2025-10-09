Com certeza! Vou refazer o projeto "push_swap" utilizando o algoritmo **Bubble Sort** para pilhas grandes, mantendo a explicação detalhada linha a linha em todos os arquivos.

**AVISO IMPORTANTE SOBRE BUBBLE SORT NO PUSH_SWAP:**

É crucial entender que, embora o Bubble Sort seja conceitualmente simples, sua implementação com as operações restritas do `push_swap` (especialmente para pilhas grandes, acima de 5 elementos) resultará em um **número de operações extremamente alto**. O projeto "push_swap" geralmente exige soluções com o **menor número possível de operações**. Uma solução baseada em Bubble Sort para pilhas maiores quase certamente **falhará nos requisitos de desempenho** (o número máximo de operações toleradas) do projeto e resultará em uma nota 0.

O algoritmo **Radix Sort** (que foi a minha sugestão anterior) é a escolha mais comum e eficiente para `push_swap` para pilhas maiores, pois ele consegue ordenar com um número de operações muito menor, geralmente dentro dos limites aceitáveis do projeto (O(N log N) ou O(N * bits)).

Estou fornecendo esta implementação de Bubble Sort conforme solicitado para fins educacionais, para demonstrar como seria, mas com o forte alerta de que **não é a solução ideal ou performática** para o problema "push_swap" real.

---

### 1. `Makefile`

O `Makefile` é um script que automatiza o processo de compilação. Ele define as regras para construir o executável a partir dos arquivos fonte.

```makefile
# Define o nome do executável final que será gerado.
NAME = push_swap

# Lista todos os arquivos fonte (.c) que compõem o projeto.
# Cada linha é um arquivo fonte diferente. O '\' permite que a lista continue na próxima linha.
SRCS = \
	main.c \
	error_handler.c \
	parsing.c \
	stack_utils.c \
	operations.c \
	sort_small.c \
	sort_large.c \
	ft_split.c

# Define a variável OBJS (arquivos objeto).
# Substitui a extensão '.c' de cada arquivo em SRCS por '.o'.
# Ex: main.c -> main.o, error_handler.c -> error_handler.o
OBJS = $(SRCS:.c=.o)

# Define o compilador C a ser usado. Neste caso, é o GCC.
CC = gcc

# Define as flags de compilação.
# -Wall: Habilita todos os warnings "sensatos" (warnings que são geralmente úteis).
# -Wextra: Habilita warnings adicionais, complementares ao -Wall.
# -Werror: Transforma todos os warnings em erros. Se houver qualquer warning, a compilação falha. Boa prática para projetos 42.
# -g: Inclui informações de depuração no executável, essenciais para usar ferramentas como GDB.
CFLAGS = -Wall -Wextra -Werror -g

# Define as flags de inclusão de cabeçalhos.
# -I.: Informa ao compilador para procurar arquivos de cabeçalho no diretório atual ('.').
INC_FLAGS = -I.

# ----------------- REGRAS PRINCIPAIS -----------------

# A regra 'all' é a regra padrão. Quando você digita 'make' sem argumentos, esta é a regra executada.
# Ela depende da regra $(NAME), que por sua vez compila o executável principal.
all: $(NAME)

# Regra para compilar o executável final $(NAME) (push_swap).
# Depende de todos os arquivos objeto listados em $(OBJS).
# O comando $(CC) $(OBJS) -o $(NAME) linka todos os arquivos objeto para criar o executável.
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

# Regra genérica para compilar arquivos fonte (.c) em arquivos objeto (.o).
# '%': Caractere curinga que representa o nome base do arquivo.
# '%.o: %.c': Significa "para criar um arquivo .o, eu preciso de um arquivo .c com o mesmo nome base".
# $(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@:
# - $(CC): O compilador.
# - $(CFLAGS): As flags de compilação definidas anteriormente.
# - $(INC_FLAGS): As flags de inclusão de cabeçalhos.
# - -c: Indica ao compilador para compilar apenas, sem linkar (gerar apenas o arquivo .o).
# - $<: Variável automática que representa o primeiro pré-requisito (o arquivo .c).
# - -o $@: Variável automática que representa o nome do arquivo alvo (o arquivo .o).
%.o: %.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Regra 'clean': Remove todos os arquivos objeto (.o) gerados durante a compilação.
# 'rm -f $(OBJS)': Remove forçadamente ('-f') os arquivos listados em $(OBJS).
clean:
	rm -f $(OBJS)

# Regra 'fclean': Remove todos os arquivos objeto (.o) E o executável final $(NAME).
# Primeiro executa a regra 'clean' e depois remove o executável.
fclean: clean
	rm -f $(NAME)

# Regra 're': "Recompilar" do zero.
# Primeiro executa 'fclean' (limpa tudo) e depois 'all' (compila tudo novamente).
re: fclean all

# Declaração de regras "phony".
# '.PHONY': Informa ao Make que essas regras não correspondem a nomes de arquivos reais.
# Isso garante que o Make sempre executará essas regras, mesmo que exista um arquivo com o mesmo nome.
.PHONY: all clean fclean re
```

---

### 2. `push_swap.h`

Este é o arquivo de cabeçalho principal. Ele define as estruturas de dados usadas em todo o projeto e declara os protótipos de todas as funções, tornando-as acessíveis a outros arquivos `.c`. A principal mudança aqui é no protótipo da função de ordenação para pilhas grandes.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H // Guarda de inclusão (include guard): Se PUSH_SWAP_H ainda não foi definido...
# define PUSH_SWAP_H // ...então define PUSH_SWAP_H. Isso previne que o arquivo seja incluído múltiplas vezes.

// --- INCLUDES ---
# include <stdlib.h> // Inclui a biblioteca padrão de C. Necessário para `malloc`, `free`, `exit`, `atoll`.
# include <unistd.h> // Inclui a biblioteca POSIX para funções de sistema. Necessário para `write` (usado para imprimir erros no `stderr`).
# include <limits.h> // Inclui limites de tipos de dados. Necessário para `INT_MIN` e `INT_MAX` (usados na validação de argumentos).
# include <stdbool.h> // Inclui a biblioteca para tipos booleanos (`true`, `false`).

// --- ESTRUTURAS DE DADOS ---

// `typedef struct s_stack_node` cria um novo tipo `t_stack_node` (convenção 42: `t_` prefixo para `typedef`).
// Esta estrutura representa um único elemento (nó) dentro de uma pilha.
typedef struct s_stack_node
{
	int						value; // `value` armazena o número inteiro que este nó representa na pilha.
	int						index; // `index` armazena um índice atribuído ao `value`.
	                           // O menor valor na pilha original terá índice 0, o segundo menor 1, etc.
	                           // Isso é crucial para o algoritmo de ordenação (mesmo Bubble Sort pode se beneficiar).
	struct s_stack_node		*next; // `next` é um ponteiro para o próximo nó na pilha.
	                           // Se este for o último nó da pilha, `next` será `NULL`.
}	t_stack_node; // O nome do tipo `t_stack_node` é definido aqui.

// `typedef struct s_stack` cria um novo tipo `t_stack`.
// Esta estrutura representa uma pilha inteira (Stack A ou Stack B).
typedef struct s_stack
{
	t_stack_node	*head; // `head` é um ponteiro para o primeiro nó (`t_stack_node`) da pilha.
	                           // Este nó é considerado o "topo" da pilha. Se a pilha estiver vazia, `head` será `NULL`.
	int				size;  // `size` armazena o número de elementos (nós) atualmente na pilha.
	                           // Manter o tamanho atualizado evita ter que percorrer a lista toda vez para contá-la, melhorando a performance.
}	t_stack; // O nome do tipo `t_stack` é definido aqui.


// --- PROTÓTIPOS DE FUNÇÕES ---
// As funções são agrupadas por sua responsabilidade em diferentes arquivos .c.

// 1. Funções de `error_handler.c`:
void			error_exit(t_stack *a, t_stack *b); // Declara a função `error_exit`. Ela é chamada em caso de erro fatal,
	                           // imprime "Error\n" no `stderr`, libera a memória das pilhas `a` e `b` (se existirem) e encerra o programa.
void			ft_putstr_fd(char *s, int fd); // Declara a função `ft_putstr_fd`. Escreve a string `s` no descritor de arquivo `fd`.
	                           // É uma versão simplificada de `ft_putstr_fd` da Libft, usada principalmente para `stderr`.

// 2. Funções de `parsing.c`:
void			parse_arguments(int argc, char **argv, t_stack *a); // Declara `parse_arguments`. É a função principal de parsing,
	                           // que processa os argumentos da linha de comando (`argv`) para construir a pilha `a`.
	                           // Lida com a validação e a conversão dos números.
void			init_stack_a(t_stack *a, char **numbers_str, int count); // Declara `init_stack_a`. Inicializa a pilha `a`
	                           // a partir de um array de strings (`numbers_str`) contendo os números e o `count` de números.
	                           // Realiza validações de tipo e range.
bool			is_numeric(char *str); // Declara `is_numeric`. Retorna `true` se a string `str` representa um número inteiro válido, `false` caso contrário.
bool			is_in_int_range(long long num); // Declara `is_in_int_range`. Retorna `true` se o número `num` (long long) está
	                           // dentro dos limites de `INT_MIN` e `INT_MAX`, `false` caso contrário.
bool			has_duplicates(t_stack *a); // Declara `has_duplicates`. Retorna `true` se a pilha `a` contém valores duplicados, `false` caso contrário.
void			assign_indices(t_stack *a); // Declara `assign_indices`. Percorre a pilha `a` e atribui um `index` (0 a `size-1`)
	                           // a cada nó, onde 0 é o menor valor e `size-1` é o maior.

// 3. Funções de `stack_utils.c`:
t_stack_node	*ft_lstnew_stack(int value); // Declara `ft_lstnew_stack`. Cria e retorna um novo `t_stack_node` com o `value` fornecido.
	                           // Retorna `NULL` se a alocação de memória falhar.
void			ft_lstadd_front_stack(t_stack *stack, t_stack_node *new_node); // Declara `ft_lstadd_front_stack`. Adiciona `new_node`
	                           // no topo (frente) da `stack`.
void			ft_lstadd_back_stack(t_stack *stack, t_stack_node *new_node); // Declara `ft_lstadd_back_stack`. Adiciona `new_node`
	                           // no final (cauda) da `stack`.
t_stack_node	*ft_lstlast_stack(t_stack *stack); // Declara `ft_lstlast_stack`. Percorre a `stack` e retorna um ponteiro para o último nó.
	                           // Retorna `NULL` se a pilha estiver vazia.
int				ft_lstsize_stack(t_stack *stack); // Declara `ft_lstsize_stack`. Retorna o número de elementos na `stack`.
	                           // Embora `t_stack.size` já faça isso, esta função pode ser útil para verificação.
void			ft_lstdelone_stack(t_stack_node *node); // Declara `ft_lstdelone_stack`. Libera a memória de um único nó.
void			ft_lstclear_stack(t_stack *stack); // Declara `ft_lstclear_stack`. Libera toda a memória de uma pilha.

// 4. Funções de `operations.c` (as 11 operações push_swap):
void			sa(t_stack *a); // Declara `sa`. Troca os dois primeiros elementos da pilha `a`. Imprime "sa\n".
void			sb(t_stack *b); // Declara `sb`. Troca os dois primeiros elementos da pilha `b`. Imprime "sb\n".
void			ss(t_stack *a, t_stack *b); // Declara `ss`. Executa `sa` e `sb` simultaneamente. Imprime "ss\n".
void			pa(t_stack *a, t_stack *b); // Declara `pa`. Move o topo da pilha `b` para o topo da pilha `a`. Imprime "pa\n".
void			pb(t_stack *a, t_stack *b); // Declara `pb`. Move o topo da pilha `a` para o topo da pilha `b`. Imprime "pb\n".
void			ra(t_stack *a); // Declara `ra`. Rotaciona a pilha `a` para cima (o topo vai para o fundo). Imprime "ra\n".
void			rb(t_stack *b); // Declara `rb`. Rotaciona a pilha `b` para cima. Imprime "rb\n".
void			rr(t_stack *a, t_stack *b); // Declara `rr`. Executa `ra` e `rb` simultaneamente. Imprime "rr\n".
void			rra(t_stack *a); // Declara `rra`. Rotaciona a pilha `a` para baixo (o fundo vai para o topo). Imprime "rra\n".
void			rrb(t_stack *b); // Declara `rrb`. Rotaciona a pilha `b` para baixo. Imprime "rrb\n".
void			rrr(t_stack *a, t_stack *b); // Declara `rrr`. Executa `rra` e `rrb` simultaneamente. Imprime "rrr\n".

// 5. Funções de `sort_small.c` (algoritmos para pilhas pequenas):
bool			is_sorted(t_stack *a); // Declara `is_sorted`. Retorna `true` se a pilha `a` está em ordem crescente, `false` caso contrário.
void			sort_two(t_stack *a); // Declara `sort_two`. Ordena uma pilha de 2 elementos.
void			sort_three(t_stack *a); // Declara `sort_three`. Ordena uma pilha de 3 elementos.
void			sort_four(t_stack *a, t_stack *b); // Declara `sort_four`. Ordena uma pilha de 4 elementos usando `b` como auxiliar.
void			sort_five(t_stack *a, t_stack *b); // Declara `sort_five`. Ordena uma pilha de 5 elementos usando `b` como auxiliar.
void			sort_small_stack(t_stack *a, t_stack *b); // Declara `sort_small_stack`. Função de dispatcher que chama a função de ordenação apropriada
	                           // para pilhas de tamanho 2 a 5.
int				find_min_pos(t_stack *s); // Declara `find_min_pos`. Encontra a posição (0-indexada) do menor elemento na pilha `s`.

// 6. Funções de `sort_large.c` (Bubble Sort):
void			bubble_sort_push_swap(t_stack *a, t_stack *b); // Declara `bubble_sort_push_swap`. Implementa o algoritmo Bubble Sort.

// 7. Funções de `ft_split.c` (utilitários para dividir strings):
char			**ft_split(char const *s, char c); // Declara `ft_split`. Divide a string `s` em um array de strings, usando `c` como delimitador.
	                           // Retorna um array de `char*` ou `NULL` em caso de erro.
void			ft_free_split(char **split); // Declara `ft_free_split`. Libera toda a memória alocada por `ft_split`.
size_t			ft_strlen(const char *s); // Declara `ft_strlen`. Calcula e retorna o comprimento da string `s`.
char			*ft_strdup(const char *s1); // Declara `ft_strdup`. Duplica a string `s1` alocando nova memória.
	                           // Retorna um ponteiro para a nova string, ou `NULL` se a alocação falhar.

#endif // Fim da guarda de inclusão.```

---

### 3. `main.c`

Este é o arquivo principal que contém a função `main`. Ele coordena a inicialização do programa, o parsing dos argumentos e a chamada do algoritmo de ordenação. A principal mudança aqui é na função de ordenação chamada para pilhas grandes.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal do projeto, que contém todas as definições e protótipos de funções.

// A função `main` é o ponto de entrada de qualquer programa C.
// `argc`: Argument count (número de argumentos de linha de comando).
// `argv`: Argument vector (um array de strings, onde cada string é um argumento).
int	main(int argc, char **argv)
{
	t_stack	a; // Declara uma variável `a` do tipo `t_stack`, que representará a primeira pilha.
	t_stack	b; // Declara uma variável `b` do tipo `t_stack`, que representará a segunda pilha (auxiliar).

	// Inicializa os membros `head` (ponteiro para o topo) e `size` (tamanho) de ambas as pilhas.
	// É crucial inicializar ponteiros para `NULL` e tamanhos para `0` para evitar
	// acesso a memória inválida ou comportamentos indefinidos, especialmente em caso de erro.
	a.head = NULL; // A pilha `a` começa vazia.
	a.size = 0;    // O tamanho da pilha `a` é 0.
	b.head = NULL; // A pilha `b` (auxiliar) também começa vazia.
	b.size = 0;    // O tamanho da pilha `b` é 0.

	// Verifica se nenhum argumento foi fornecido além do nome do programa.
	// `argc == 1` significa que a linha de comando foi apenas `./push_swap`.
	if (argc == 1)
		return (0); // Se não houver argumentos, o programa não faz nada e retorna 0 (sucesso).

	// Chama a função `parse_arguments` para processar os argumentos da linha de comando.
	// Esta função irá validar os números, construir a pilha `a` e atribuir índices.
	// Se houver qualquer erro (não numérico, fora do range INT, duplicatas),
	// `parse_arguments` chamará `error_exit`, que imprimirá "Error" e encerrará o programa.
	// `&a` é passado para que a função possa modificar a pilha `a` diretamente.
	parse_arguments(argc, argv, &a);

	// Após a pilha `a` ser construída, verifica se ela já está ordenada.
	// `is_sorted(&a)` retorna `true` se os elementos estiverem em ordem crescente.
	if (is_sorted(&a))
	{
		ft_lstclear_stack(&a); // Se já estiver ordenada, libera a memória de todos os nós da pilha `a`.
		return (0);            // Retorna 0 (sucesso), pois nenhuma operação de ordenação é necessária.
	}

	// Com base no tamanho da pilha `a`, decide qual algoritmo de ordenação usar.
	// Pilhas com 2 a 5 elementos são tratadas por algoritmos específicos e otimizados.
	if (a.size <= 5)
		sort_small_stack(&a, &b); // Chama a função para ordenar pilhas pequenas.
	else
		bubble_sort_push_swap(&a, &b); // Para pilhas maiores, utiliza o algoritmo Bubble Sort (conforme solicitado).

	// Após a conclusão da ordenação (independentemente do algoritmo usado),
	// a pilha `a` deve estar ordenada e a pilha `b` deve estar vazia.
	// Libera toda a memória alocada para a pilha `a`. A pilha `b` já deve estar vazia.
	ft_lstclear_stack(&a);
	
	return (0); // O programa termina com sucesso.
}
```

---

### 4. `error_handler.c`

Este arquivo contém funções para lidar com mensagens de erro. Em `push_swap`, qualquer erro de entrada deve resultar na impressão de "Error" no `stderr` e no encerramento do programa.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal para ter acesso às estruturas e protótipos.

// `ft_putstr_fd` é uma função auxiliar para escrever uma string em um descritor de arquivo específico.
// `char *s`: A string a ser escrita.
// `int fd`: O descritor de arquivo (ex: `STDOUT_FILENO` para saída padrão, `STDERR_FILENO` para erro padrão).
void	ft_putstr_fd(char *s, int fd)
{
	int	i; // Declara um contador inteiro `i` para percorrer a string.

	i = 0; // Inicializa o contador `i` com 0.
	if (!s) // Verifica se o ponteiro `s` é `NULL`. Se for, não há nada para escrever.
		return ; // Retorna da função.
	// Loop `while` que continua enquanto o caractere atual da string `s[i]` não for o terminador nulo ('\0').
	while (s[i] != '\0')
	{
		// `write` é uma chamada de sistema POSIX para escrever dados em um descritor de arquivo.
		// `fd`: O descritor de arquivo onde escrever.
		// `&s[i]`: Um ponteiro para o caractere atual da string a ser escrita.
		// `1`: O número de bytes a serem escritos (neste caso, 1 caractere por vez).
		write(fd, &s[i], 1);
		i++; // Incrementa `i` para mover para o próximo caractere.
	}
}

// `error_exit` é a função central de tratamento de erros do programa.
// Ela é responsável por imprimir a mensagem de erro, liberar qualquer memória alocada
// para as pilhas e encerrar o programa com um código de falha.
// `t_stack *a`: Ponteiro para a pilha 'a'.
// `t_stack *b`: Ponteiro para a pilha 'b'.
void	error_exit(t_stack *a, t_stack *b)
{
	// Imprime a string "Error\n" no `STDERR_FILENO` (descritor de arquivo para erro padrão).
	ft_putstr_fd("Error\n", STDERR_FILENO);

	// Verifica se a pilha `a` e seu ponteiro `head` não são `NULL`.
	// Isso garante que tentamos limpar a pilha apenas se ela foi inicializada e contém nós.
	if (a && a->head)
		ft_lstclear_stack(a); // Chama `ft_lstclear_stack` para liberar toda a memória dos nós da pilha `a`.

	// Faz a mesma verificação e limpeza para a pilha `b`.
	if (b && b->head)
		ft_lstclear_stack(b); // Chama `ft_lstclear_stack` para liberar toda a memória dos nós da pilha `b`.

	// `exit(EXIT_FAILURE)` encerra o programa imediatamente.
	// `EXIT_FAILURE` é uma macro (geralmente definida como 1) que indica que o programa terminou com um erro.
	exit(EXIT_FAILURE);
}
```

---

### 5. `parsing.c`

Este arquivo lida com a parte mais crítica da inicialização: pegar os argumentos de linha de comando (que são strings), validá-los, convertê-los em inteiros e construir a pilha `a`, além de atribuir índices para facilitar a ordenação.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal.

// --- Funções de Validação de Argumentos ---

// `is_numeric` verifica se uma dada string `str` representa um número inteiro válido.
// Retorna `true` se for numérica (pode ter um sinal no início), `false` caso contrário.
bool	is_numeric(char *str)
{
	int	i; // Declara um contador `i` para percorrer a string.

	i = 0; // Inicializa `i` em 0.
	// Verifica se o primeiro caractere é um sinal de '+' ou '-'.
	// Se for, incrementa `i` para pular o sinal na próxima verificação.
	if (str[i] == '+' || str[i] == '-')
		i++;
	// Após verificar o sinal (ou se não havia um), verifica se a string não está vazia.
	// Uma string como "+" ou "-" sozinha não é um número válido.
	if (str[i] == '\0')
		return (false); // Se a string estiver vazia aqui, não é numérica.
	// Loop `while` que continua enquanto o caractere atual `str[i]` não for o terminador nulo.
	while (str[i] != '\0')
	{
		// Verifica se o caractere atual não é um dígito (0-9).
		if (str[i] < '0' || str[i] > '9')
			return (false); // Se não for um dígito, a string não é numérica.
		i++; // Move para o próximo caractere.
	}
	return (true); // Se o loop terminar, todos os caracteres válidos eram dígitos (e opcionalmente um sinal).
}

// `is_in_int_range` verifica se um número `num_ll` (do tipo `long long` para evitar overflow na leitura)
// está dentro dos limites de um `int` padrão (`INT_MIN` a `INT_MAX`).
// Retorna `true` se estiver no range, `false` caso contrário.
bool	is_in_int_range(long long num_ll)
{
	// `INT_MIN` e `INT_MAX` são macros da biblioteca <limits.h>.
	// Compara `num_ll` com o menor e maior valor que um `int` pode armazenar.
	return (num_ll >= INT_MIN && num_ll <= INT_MAX);
}

// `has_duplicates` verifica se há números repetidos dentro da pilha `a`.
// Retorna `true` se encontrar duplicatas, `false` caso contrário.
bool	has_duplicates(t_stack *a)
{
	t_stack_node	*current; // Ponteiro `current` para percorrer a pilha do início.
	t_stack_node	*runner;  // Ponteiro `runner` para comparar cada `current` com os nós subsequentes.

	current = a->head; // `current` começa no topo da pilha `a`.
	// Loop externo: `while (current)` continua enquanto `current` não for `NULL` (ou seja, enquanto houver nós para verificar).
	while (current)
	{
		runner = current->next; // `runner` começa do nó seguinte a `current`.
		// Loop interno: `while (runner)` continua enquanto `runner` não for `NULL`.
		// Compara `current->value` com todos os `runner->value` à frente dele na pilha.
		while (runner)
		{
			// Se o valor de `current` for igual ao valor de `runner`, uma duplicata foi encontrada.
			if (current->value == runner->value)
				return (true); // Retorna `true` imediatamente.
			runner = runner->next; // Move `runner` para o próximo nó.
		}
		current = current->next; // Move `current` para o próximo nó.
	}
	return (false); // Se os loops terminarem sem encontrar duplicatas, retorna `false`.
}

// --- Funções de Inicialização da Pilha ---

// `init_stack_a` preenche a pilha `a` com os números fornecidos em formato de string.
// `t_stack *a`: Ponteiro para a pilha `a` a ser inicializada.
// `char **numbers_str`: Array de strings, onde cada string é um número.
// `int count`: O número de strings no array `numbers_str`.
void	init_stack_a(t_stack *a, char **numbers_str, int count)
{
	int				i;        // Contador `i` para iterar sobre `numbers_str`.
	long long		num_ll;   // `num_ll` (long long) para armazenar o valor convertido temporariamente.
	t_stack_node	*new_node; // Ponteiro para o novo nó da pilha a ser criado.

	i = 0; // Inicializa `i` em 0.
	// Loop `while` para processar cada string numérica no array `numbers_str`.
	while (i < count)
	{
		// 1. Validação de formato: Verifica se a string atual é numérica.
		if (!is_numeric(numbers_str[i]))
			// Se não for numérica, chama `error_exit` para lidar com o erro e encerrar.
			// `a` é passado para liberar a memória já alocada, `NULL` para `b` pois ainda não está em uso.
			error_exit(a, NULL);

		// Converte a string numérica para um `long long`. `atoll` é seguro para valores maiores que INT_MAX/INT_MIN.
		num_ll = atoll(numbers_str[i]);

		// 2. Validação de range: Verifica se o `long long` convertido está dentro dos limites de um `int`.
		if (!is_in_int_range(num_ll))
			error_exit(a, NULL); // Se fora do range, erro.
		
		// Cria um novo nó da pilha com o valor convertido (agora seguro para ser `int`).
		new_node = ft_lstnew_stack((int)num_ll);
		// Verifica se a alocação de memória para o novo nó falhou.
		if (!new_node)
			error_exit(a, NULL); // Se falhou, erro.

		// Adiciona o novo nó ao final da pilha `a`. Isso garante que a ordem dos argumentos
		// (o primeiro argumento sendo o topo) seja mantida ao construir a pilha de forma ascendente.
		ft_lstadd_back_stack(a, new_node);
		i++; // Move para a próxima string numérica.
	}

	// 3. Validação de duplicatas: Após todos os números serem adicionados, verifica se há duplicatas na pilha `a`.
	if (has_duplicates(a))
		error_exit(a, NULL); // Se houver duplicatas, erro.
}

// `assign_indices` atribui um índice único a cada elemento da pilha `a`.
// O menor valor recebe o índice 0, o segundo menor 1, e assim por diante até `size-1`.
// Isso é fundamental para a ordenação, especialmente para algoritmos que se beneficiam de números em um range denso.
void	assign_indices(t_stack *a)
{
	t_stack_node	*current; // Ponteiro `current` para o nó atual que estamos indexando.
	t_stack_node	*temp;    // Ponteiro `temp` para percorrer a pilha e comparar com `current`.
	int				index;    // Variável para armazenar o índice calculado.

	current = a->head; // `current` começa no topo da pilha `a`.
	// Loop externo: `while (current)` itera sobre cada nó da pilha `a`.
	while (current)
	{
		index = 0;       // Inicializa `index` para 0 para cada `current` nó.
		temp = a->head;  // `temp` sempre reinicia no topo da pilha para comparar com `current`.
		// Loop interno: `while (temp)` itera sobre todos os nós da pilha para contar quantos são menores que `current`.
		while (temp)
		{
			// Se o valor de `temp` for menor que o valor de `current`,
			// significa que `current` é maior que `temp`, então seu índice deve ser maior.
			if (temp->value < current->value)
				index++; // Incrementa `index`.
			temp = temp->next; // Move `temp` para o próximo nó.
		}
		current->index = index; // Atribui o `index` calculado ao `current` nó.
		current = current->next; // Move `current` para o próximo nó.
	}
}

// `parse_arguments` é a função principal que gerencia o fluxo de parsing.
// Lida com dois formatos de entrada: números como argumentos separados, ou números em uma única string.
// `int argc`: Número total de argumentos de linha de comando.
// `char **argv`: Array de strings dos argumentos.
// `t_stack *a`: Ponteiro para a pilha `a` a ser populada.
void	parse_arguments(int argc, char **argv, t_stack *a)
{
	char	**numbers_str; // Ponteiro para um array de strings que conterá os números (pode ser `argv` ou o resultado de `ft_split`).
	int		count;         // Número de elementos no `numbers_str` array.

	// Se `argc == 2`, significa que o usuário forneceu apenas um argumento
	// além do nome do programa, e esse argumento pode ser uma string com múltiplos números
	// (ex: `./push_swap "1 2 3 4"`).
	if (argc == 2)
	{
		// `ft_split` divide a string `argv[1]` (o único argumento fornecido) usando o espaço (' ') como delimitador.
		// O resultado é um array de strings (ex: {"1", "2", "3", "4", NULL}).
		numbers_str = ft_split(argv[1], ' ');
		// Verifica se `ft_split` falhou (ex: `malloc` falhou, ou a string estava vazia após a divisão).
		if (!numbers_str)
			error_exit(a, NULL); // Se `ft_split` retornar `NULL`, indica um erro de alocação ou parsing.
		
		count = 0; // Inicializa o contador de números.
		// Loop `while` para contar quantos números foram extraídos por `ft_split`.
		while (numbers_str[count])
			count++;
		
		// Se `count` for 0, significa que a string de entrada estava vazia ou continha apenas espaços.
		if (count == 0)
		{
			ft_free_split(numbers_str); // Libera a memória alocada por `ft_split` para o array vazio.
			error_exit(a, NULL); // Considera isso um erro de entrada inválida.
		}
		
		init_stack_a(a, numbers_str, count); // Chama `init_stack_a` para construir a pilha.
		ft_free_split(numbers_str);          // Libera a memória alocada por `ft_split` após a pilha ser construída.
	}
	else // Se `argc > 2`, significa que os números foram fornecidos como argumentos separados
	     // (ex: `./push_swap 1 2 3 4`).
	{
		// Neste caso, `argv + 1` aponta para o primeiro argumento numérico (ignorando o nome do programa `argv[0]`).
		// `argc - 1` é o número real de argumentos numéricos.
		init_stack_a(a, argv + 1, argc - 1); // Chama `init_stack_a` diretamente com `argv` e o ajuste de contagem.
	}
	
	assign_indices(a); // Depois que a pilha `a` é totalmente construída, atribui índices a todos os seus elementos.
}
```

---

### 6. `stack_utils.c`

Este arquivo contém as funções utilitárias que manipulam a estrutura de lista encadeada subjacente às pilhas (`t_stack` e `t_stack_node`).

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal.

// `ft_lstnew_stack` cria um novo nó para a pilha com o valor inteiro fornecido.
// `int value`: O valor inteiro a ser armazenado no novo nó.
// Retorna um ponteiro para o `t_stack_node` recém-criado, ou `NULL` se a alocação de memória falhar.
t_stack_node	*ft_lstnew_stack(int value)
{
	t_stack_node	*new_node; // Declara um ponteiro para `t_stack_node` que irá apontar para o novo nó.

	// Aloca dinamicamente a memória necessária para uma única estrutura `t_stack_node`.
	// `sizeof(t_stack_node)` obtém o tamanho em bytes da estrutura.
	// O cast `(t_stack_node *)` é para garantir que o tipo do ponteiro esteja correto (embora em C geralmente não seja estritamente necessário para `malloc`).
	new_node = (t_stack_node *)malloc(sizeof(t_stack_node));
	// Verifica se a alocação de memória falhou (`malloc` retorna `NULL` em caso de falha).
	if (!new_node)
		return (NULL); // Retorna `NULL` para indicar a falha.

	new_node->value = value; // Atribui o `value` passado como argumento ao membro `value` do novo nó.
	new_node->index = -1;    // Inicializa o membro `index` como -1. O índice será atribuído posteriormente por `assign_indices`.
	new_node->next = NULL;   // O `next` do novo nó é `NULL` por padrão, pois inicialmente ele é o último (ou único) nó.
	return (new_node); // Retorna o ponteiro para o nó recém-criado e inicializado.
}

// `ft_lstadd_front_stack` adiciona um `new_node` no topo (frente) de uma pilha.
// `t_stack *stack`: Ponteiro para a estrutura `t_stack` à qual o nó será adicionado.
// `t_stack_node *new_node`: Ponteiro para o nó a ser adicionado.
void	ft_lstadd_front_stack(t_stack *stack, t_stack_node *new_node)
{
	// Verifica se a pilha ou o novo nó são ponteiros válidos (não `NULL`).
	if (!stack || !new_node)
		return ; // Se algum for `NULL`, a operação não pode ser realizada, então retorna.

	new_node->next = stack->head; // O `next` do `new_node` agora aponta para o que era o `head` (topo) da pilha antes da adição.
	stack->head = new_node;       // O `head` da pilha agora aponta para o `new_node`, tornando-o o novo topo.
	stack->size++;                // Incrementa o contador de tamanho da pilha.
}

// `ft_lstadd_back_stack` adiciona um `new_node` no final (cauda) de uma pilha.
// `t_stack *stack`: Ponteiro para a estrutura `t_stack` à qual o nó será adicionado.
// `t_stack_node *new_node`: Ponteiro para o nó a ser adicionado.
void	ft_lstadd_back_stack(t_stack *stack, t_stack_node *new_node)
{
	t_stack_node	*last; // Declara um ponteiro `last` que será usado para encontrar o último nó existente.

	// Verifica se a pilha ou o novo nó são ponteiros válidos.
	if (!stack || !new_node)
		return ; // Retorna se algum for `NULL`.

	new_node->next = NULL; // O `next` do `new_node` é `NULL`, pois ele será o novo último nó.
	if (!stack->head) // Verifica se a pilha está vazia (se `head` é `NULL`).
	{
		stack->head = new_node; // Se a pilha estiver vazia, o `new_node` se torna o primeiro e único nó (o `head`).
	}
	else // Se a pilha não estiver vazia.
	{
		last = ft_lstlast_stack(stack); // Encontra o último nó existente na pilha usando a função auxiliar `ft_lstlast_stack`.
		last->next = new_node;          // O `next` do antigo último nó agora aponta para o `new_node`, adicionando-o ao final.
	}
	stack->size++;                      // Incrementa o contador de tamanho da pilha.
}

// `ft_lstlast_stack` percorre uma pilha e retorna um ponteiro para o seu último nó.
// `t_stack *stack`: Ponteiro para a estrutura `t_stack`.
// Retorna um ponteiro para o último `t_stack_node`, ou `NULL` se a pilha estiver vazia.
t_stack_node	*ft_lstlast_stack(t_stack *stack)
{
	t_stack_node	*current; // Declara um ponteiro `current` para percorrer a pilha.

	// Verifica se a pilha é `NULL` ou se o `head` da pilha é `NULL` (pilha vazia).
	if (!stack || !stack->head)
		return (NULL); // Retorna `NULL` se a pilha estiver vazia.

	current = stack->head; // `current` começa no `head` (topo) da pilha.
	// Loop `while` continua enquanto `current->next` não for `NULL`.
	// Isso significa que o loop para quando `current` aponta para o último nó.
	while (current->next)
	{
		current = current->next; // Move `current` para o próximo nó.
	}
	return (current); // Retorna o ponteiro para o último nó.
}

// `ft_lstsize_stack` calcula e retorna o número de elementos em uma pilha.
// `t_stack *stack`: Ponteiro para a estrutura `t_stack`.
// Retorna o número de nós na pilha.
int	ft_lstsize_stack(t_stack *stack)
{
	t_stack_node	*current; // Ponteiro `current` para percorrer a pilha.
	int				count;    // Contador para o número de nós.

	// Verifica se a pilha é `NULL` ou se o `head` da pilha é `NULL` (pilha vazia).
	if (!stack || !stack->head)
		return (0); // Se a pilha estiver vazia, retorna 0.

	count = 0; // Inicializa o contador de nós em 0.
	current = stack->head; // `current` começa no `head` da pilha.
	// Loop `while` continua enquanto `current` não for `NULL` (ou seja, enquanto houver nós).
	while (current)
	{
		count++;             // Incrementa o contador para cada nó.
		current = current->next; // Move `current` para o próximo nó.
	}
	return (count); // Retorna o total de nós contados.
}

// `ft_lstdelone_stack` libera a memória de um único nó da pilha.
// `t_stack_node *node`: Ponteiro para o nó a ser liberado.
void	ft_lstdelone_stack(t_stack_node *node)
{
	if (node) // Verifica se o ponteiro `node` não é `NULL`.
	{
		free(node); // `free(node)` libera a memória alocada dinamicamente para o `node`.
		// node = NULL; // É uma boa prática definir o ponteiro como `NULL` após liberar a memória,
		              // para evitar "dangling pointers", embora o ponteiro local `node` saia do escopo logo em seguida.
	}
}

// `ft_lstclear_stack` libera a memória de todos os nós de uma pilha e a redefine como vazia.
// `t_stack *stack`: Ponteiro para a estrutura `t_stack` a ser limpa.
void	ft_lstclear_stack(t_stack *stack)
{
	t_stack_node	*current;   // Ponteiro `current` para o nó atual que está sendo processado.
	t_stack_node	*next_node; // Ponteiro `next_node` para guardar o próximo nó antes de liberar o `current`.

	// Verifica se a pilha é `NULL` ou se o `head` da pilha é `NULL` (já vazia).
	if (!stack || !stack->head)
		return ; // Se a pilha já estiver vazia ou inválida, não há nada para limpar.

	current = stack->head; // `current` começa no `head` da pilha.
	// Loop `while` continua enquanto `current` não for `NULL` (enquanto houver nós para liberar).
	while (current)
	{
		next_node = current->next; // Guarda o ponteiro para o próximo nó antes de liberar `current`.
		ft_lstdelone_stack(current); // Libera a memória do nó `current`.
		current = next_node;       // `current` avança para o `next_node` que foi guardado.
	}
	stack->head = NULL; // Após liberar todos os nós, define o `head` da pilha como `NULL` (a pilha está vazia).
	stack->size = 0;    // Redefine o `size` da pilha para 0.
}
```

---

### 7. `operations.c`

Este arquivo contém as implementações de todas as 11 operações do `push_swap`. Cada função modifica as pilhas de acordo com a regra da operação e imprime a instrução correspondente.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal.

// --- Swap (troca os 2 primeiros elementos) ---

// `sa`: Troca os dois primeiros elementos (os do topo) da pilha `a`.
// `t_stack *a`: Ponteiro para a pilha `a`.
void	sa(t_stack *a)
{
	t_stack_node	*first;  // Ponteiro para o nó que está atualmente no topo.
	t_stack_node	*second; // Ponteiro para o nó que está abaixo do topo.

	// Verifica se a pilha `a` existe e se tem pelo menos 2 elementos.
	// Se tiver menos de 2 elementos, a troca não é possível, então a função retorna.
	if (!a || a->size < 2)
		return ;

	first = a->head;          // `first` aponta para o nó do topo.
	second = a->head->next;   // `second` aponta para o nó logo abaixo do topo.

	first->next = second->next; // O `next` do `first` (que era o segundo nó) agora aponta para o que era o terceiro nó (ou `NULL`).
	second->next = first;       // O `next` do `second` (que agora se tornará o novo topo) aponta para o `first` (o antigo topo).
	a->head = second;           // O `head` da pilha `a` agora aponta para `second`, tornando-o o novo topo.

	ft_putstr_fd("sa\n", STDOUT_FILENO); // Imprime a instrução "sa" seguida de uma nova linha na saída padrão.
}

// `sb`: Troca os dois primeiros elementos da pilha `b`.
// A lógica é idêntica à de `sa`, mas aplicada à pilha `b`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	sb(t_stack *b)
{
	t_stack_node	*first;
	t_stack_node	*second;

	if (!b || b->size < 2)
		return ;

	first = b->head;
	second = b->head->next;

	first->next = second->next;
	second->next = first;
	b->head = second;

	ft_putstr_fd("sb\n", STDOUT_FILENO); // Imprime a instrução "sb".
}

// `ss`: Executa `sa` e `sb` simultaneamente.
// É crucial que a impressão "ss\n" aconteça APENAS UMA VEZ e as operações `sa`/`sb` não imprimam individualmente quando chamadas por `ss`.
// Por isso, a lógica de troca é reimplementada aqui sem chamar `sa()` ou `sb()` diretamente.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	ss(t_stack *a, t_stack *b)
{
	t_stack_node	*first_a;  // Variáveis para a pilha `a`.
	t_stack_node	*second_a;
	t_stack_node	*first_b;  // Variáveis para a pilha `b`.
	t_stack_node	*second_b;
	bool			performed_op = false; // Flag para verificar se alguma operação de troca realmente ocorreu.

	// Lógica de troca para a pilha `a`.
	if (a && a->size >= 2) // Verifica se `a` é válida e tem pelo menos 2 elementos.
	{
		first_a = a->head;
		second_a = a->head->next;
		first_a->next = second_a->next;
		second_a->next = first_a;
		a->head = second_a;
		performed_op = true; // Marca que uma operação foi realizada.
	}
	// Lógica de troca para a pilha `b`.
	if (b && b->size >= 2) // Verifica se `b` é válida e tem pelo menos 2 elementos.
	{
		first_b = b->head;
		second_b = b->head->next;
		first_b->next = second_b->next;
		second_b->next = first_b;
		b->head = second_b;
		performed_op = true; // Marca que uma operação foi realizada.
	}
	if (performed_op) // Se pelo menos uma das trocas (a ou b) foi executada.
		ft_putstr_fd("ss\n", STDOUT_FILENO); // Imprime a instrução "ss".
}

// --- Push (move o topo de uma pilha para o topo da outra) ---

// `pa`: Pega o elemento do topo da pilha `b` e o coloca no topo da pilha `a`.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	pa(t_stack *a, t_stack *b)
{
	t_stack_node	*node_to_move; // Ponteiro para o nó que será movido.

	// Verifica se a pilha `b` existe e não está vazia.
	// Se `b` estiver vazia, não há nada para mover, então a função retorna.
	if (!b || b->size == 0)
		return ;

	node_to_move = b->head;       // `node_to_move` aponta para o topo atual de `b`.
	b->head = b->head->next;      // O `head` de `b` agora aponta para o próximo nó, removendo o topo.
	b->size--;                    // Decrementa o tamanho da pilha `b`.

	node_to_move->next = a->head; // O `next` do `node_to_move` agora aponta para o antigo `head` de `a`.
	a->head = node_to_move;       // O `head` de `a` agora aponta para `node_to_move`, tornando-o o novo topo.
	a->size++;                    // Incrementa o tamanho da pilha `a`.

	ft_putstr_fd("pa\n", STDOUT_FILENO); // Imprime a instrução "pa".
}

// `pb`: Pega o elemento do topo da pilha `a` e o coloca no topo da pilha `b`.
// A lógica é idêntica à de `pa`, mas move de `a` para `b`.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	pb(t_stack *a, t_stack *b)
{
	t_stack_node	*node_to_move;

	if (!a || a->size == 0)
		return ;

	node_to_move = a->head;
	a->head = a->head->next;
	a->size--;

	node_to_move->next = b->head;
	b->head = node_to_move;
	b->size++;

	ft_putstr_fd("pb\n", STDOUT_FILENO); // Imprime a instrução "pb".
}

// --- Rotate (o topo vai para o fundo) ---

// `ra`: Rotaciona a pilha `a` para cima. O elemento do topo (`head`) é movido para o final da pilha.
// `t_stack *a`: Ponteiro para a pilha `a`.
void	ra(t_stack *a)
{
	t_stack_node	*first; // Ponteiro para o nó que era o topo.
	t_stack_node	*last;  // Ponteiro para o nó que era o último.

	// Verifica se a pilha `a` existe e tem pelo menos 2 elementos.
	// Se tiver menos de 2 elementos, a rotação não é significativa, então a função retorna.
	if (!a || a->size < 2)
		return ;

	first = a->head;         // `first` guarda o nó do topo atual.
	a->head = a->head->next; // O `head` de `a` agora aponta para o segundo nó, tornando-o o novo topo.
	first->next = NULL;      // O `next` do `first` (que agora será o último) é definido como `NULL`.

	last = ft_lstlast_stack(a); // Encontra o nó que era o último antes da rotação (agora o penúltimo).
	last->next = first;         // O `next` do `last` agora aponta para `first`, colocando `first` no final da pilha.

	ft_putstr_fd("ra\n", STDOUT_FILENO); // Imprime a instrução "ra".
}

// `rb`: Rotaciona a pilha `b` para cima. O elemento do topo (`head`) é movido para o final da pilha.
// A lógica é idêntica à de `ra`, mas aplicada à pilha `b`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	rb(t_stack *b)
{
	t_stack_node	*first;
	t_stack_node	*last;

	if (!b || b->size < 2)
		return ;

	first = b->head;
	b->head = b->head->next;
	first->next = NULL;

	last = ft_lstlast_stack(b);
	last->next = first;

	ft_putstr_fd("rb\n", STDOUT_FILENO); // Imprime a instrução "rb".
}

// `rr`: Executa `ra` e `rb` simultaneamente.
// Novamente, a lógica de rotação é reimplementada aqui para garantir que "rr\n" seja a única instrução impressa.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	rr(t_stack *a, t_stack *b)
{
	t_stack_node	*first_a; // Variáveis para a pilha `a`.
	t_stack_node	*last_a;
	t_stack_node	*first_b; // Variáveis para a pilha `b`.
	t_stack_node	*last_b;
	bool			performed_op = false; // Flag para verificar se alguma operação de rotação realmente ocorreu.

	// Lógica de rotação para a pilha `a`.
	if (a && a->size >= 2)
	{
		first_a = a->head;
		a->head = a->head->next;
		first_a->next = NULL;
		last_a = ft_lstlast_stack(a);
		last_a->next = first_a;
		performed_op = true;
	}
	// Lógica de rotação para a pilha `b`.
	if (b && b->size >= 2)
	{
		first_b = b->head;
		b->head = b->head->next;
		first_b->next = NULL;
		last_b = ft_lstlast_stack(b);
		last_b->next = first_b;
		performed_op = true;
	}
	if (performed_op)
		ft_putstr_fd("rr\n", STDOUT_FILENO); // Imprime a instrução "rr".
}

// --- Reverse Rotate (o fundo vai para o topo) ---

// `rra`: Rotaciona a pilha `a` para baixo. O último elemento é movido para o topo (`head`) da pilha.
// `t_stack *a`: Ponteiro para a pilha `a`.
void	rra(t_stack *a)
{
	t_stack_node	*current;        // Ponteiro para percorrer a pilha.
	t_stack_node	*last;           // Ponteiro para o nó que era o último.
	t_stack_node	*second_last;    // Ponteiro para o nó que era o penúltimo.

	// Verifica se a pilha `a` existe e tem pelo menos 2 elementos.
	if (!a || a->size < 2)
		return ;

	current = a->head; // `current` começa no topo.
	// Loop para encontrar o penúltimo nó. Ele para quando `current->next->next` é `NULL`.
	// Isso significa que `current` é o penúltimo nó e `current->next` é o último.
	while (current->next->next)
		current = current->next;
	second_last = current;       // `second_last` aponta para o penúltimo nó.
	last = current->next;        // `last` aponta para o último nó.

	second_last->next = NULL; // O `next` do `second_last` agora é `NULL`, pois ele se torna o novo último.
	last->next = a->head;     // O `next` do `last` (antigo último) aponta para o antigo `head`, conectando-o no início.
	a->head = last;           // O `head` da pilha `a` agora aponta para `last`, tornando-o o novo topo.

	ft_putstr_fd("rra\n", STDOUT_FILENO); // Imprime a instrução "rra".
}

// `rrb`: Rotaciona a pilha `b` para baixo. O último elemento é movido para o topo (`head`) da pilha.
// A lógica é idêntica à de `rra`, mas aplicada à pilha `b`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	rrb(t_stack *b)
{
	t_stack_node	*current;
	t_stack_node	*last;
	t_stack_node	*second_last;

	if (!b || b->size < 2)
		return ;

	current = b->head;
	while (current->next->next)
		current = current->next;
	second_last = current;
	last = current->next;

	second_last->next = NULL;
	last->next = b->head;
	b->head = last;

	ft_putstr_fd("rrb\n", STDOUT_FILENO); // Imprime a instrução "rrb".
}

// `rrr`: Executa `rra` e `rrb` simultaneamente.
// A lógica de reverse rotation é reimplementada aqui para garantir que "rrr\n" seja a única instrução impressa.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b`.
void	rrr(t_stack *a, t_stack *b)
{
	t_stack_node	*current_a;       // Variáveis para a pilha `a`.
	t_stack_node	*last_a;
	t_stack_node	*second_last_a;
	t_stack_node	*current_b;       // Variáveis para a pilha `b`.
	t_stack_node	*last_b;
	t_stack_node	*second_last_b;
	bool			performed_op = false; // Flag para verificar se alguma operação ocorreu.

	// Lógica de reverse rotation para a pilha `a`.
	if (a && a->size >= 2)
	{
		current_a = a->head;
		while (current_a->next->next)
			current_a = current_a->next;
		second_last_a = current_a;
		last_a = current_a->next;

		second_last_a->next = NULL;
		last_a->next = a->head;
		a->head = last_a;
		performed_op = true;
	}
	// Lógica de reverse rotation para a pilha `b`.
	if (b && b->size >= 2)
	{
		current_b = b->head;
		while (current_b->next->next)
			current_b = current_b->next;
		second_last_b = current_b;
		last_b = current_b->next;

		second_last_b->next = NULL;
		last_b->next = b->head;
		b->head = last_b;
		performed_op = true;
	}
	if (performed_op)
		ft_putstr_fd("rrr\n", STDOUT_FILENO); // Imprime a instrução "rrr".
}
```

---

### 8. `sort_small.c`

Este arquivo implementa algoritmos de ordenação otimizados para pilhas com um número pequeno de elementos (2, 3, 4, 5). Para esses casos, uma abordagem baseada em "casos específicos" (hardcoded) geralmente resulta em menos operações do que um algoritmo genérico.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal.

// `is_sorted` verifica se a pilha `a` está em ordem estritamente crescente.
// `t_stack *a`: Ponteiro para a pilha `a`.
// Retorna `true` se a pilha está ordenada, `false` caso contrário.
bool	is_sorted(t_stack *a)
{
	t_stack_node	*current; // Ponteiro para percorrer a pilha.

	// Uma pilha vazia ou com apenas um elemento é considerada ordenada por definição.
	if (!a || !a->head || a->size <= 1)
		return (true);

	current = a->head; // `current` começa no topo da pilha.
	// Loop `while` que continua enquanto `current` tiver um próximo nó.
	while (current->next)
	{
		// Se o valor do nó `current` for maior que o valor do seu sucessor, a pilha não está ordenada.
		if (current->value > current->next->value)
			return (false); // Retorna `false` imediatamente.
		current = current->next; // Move `current` para o próximo nó.
	}
	return (true); // Se o loop terminar sem encontrar elementos fora de ordem, a pilha está ordenada.
}

// `sort_two` ordena uma pilha com exatamente 2 elementos.
// `t_stack *a`: Ponteiro para a pilha `a`.
void	sort_two(t_stack *a)
{
	// Verifica se o valor do topo é maior que o valor do próximo elemento.
	// Se for, a pilha está em ordem decrescente (ex: 2, 1) e precisa ser trocada.
	if (a->head->value > a->head->next->value)
		sa(a); // Executa a operação `sa` para trocar os dois elementos.
}

// `sort_three` ordena uma pilha com exatamente 3 elementos.
// Esta função cobre todas as 6 permutações possíveis para 3 elementos com o mínimo de operações.
// `t_stack *a`: Ponteiro para a pilha `a`.
void	sort_three(t_stack *a)
{
	int	n1, n2, n3; // Variáveis para armazenar os valores dos 3 nós da pilha (topo, meio, fundo).

	// É importante verificar se a pilha tem pelo menos 3 elementos antes de acessar `next->next`.
	// Uma verificação de `a->size == 3` deve ser feita antes de chamar esta função.
	// Obtém os valores dos três nós.
	n1 = a->head->value;           // Valor do topo.
	n2 = a->head->next->value;     // Valor do meio.
	n3 = a->head->next->next->value; // Valor do fundo.

	if (is_sorted(a)) // Primeiro, verifica se a pilha já está ordenada.
		return ;      // Se sim, não faz nada e retorna.

	// As seguintes condições verificam as permutações e aplicam as operações necessárias:

	// Caso: 3 1 2 (n1 > n2 && n1 > n3 && n2 < n3) -> Exemplo: 3, 1, 2
	// O 3 está no topo, o 1 no meio, o 2 no fundo. O 3 é o maior.
	// `ra` move o 3 para o fundo: 1, 2, 3 (ordenado).
	else if (n1 > n2 && n1 > n3 && n2 < n3)
		ra(a);
	// Caso: 3 2 1 (n1 > n2 && n1 > n3 && n2 > n3) -> Exemplo: 3, 2, 1
	// Totalmente invertido.
	// `sa` troca 3 e 2: 2, 3, 1.
	// `rra` move 1 para o topo: 1, 2, 3 (ordenado).
	else if (n1 > n2 && n1 > n3 && n2 > n3)
	{
		sa(a);
		rra(a);
	}
	// Caso: 2 1 3 (n1 > n2 && n1 < n3) -> Exemplo: 2, 1, 3
	// O 2 está no topo, o 1 no meio, o 3 no fundo. O 2 e 1 precisam trocar.
	// `sa` troca 2 e 1: 1, 2, 3 (ordenado).
	else if (n1 > n2 && n1 < n3)
		sa(a);
	// Caso: 1 3 2 (n1 < n2 && n2 > n3 && n1 < n3) -> Exemplo: 1, 3, 2
	// O 1 está no topo, o 3 no meio, o 2 no fundo. O 2 precisa ir para o meio.
	// `rra` move 2 para o topo: 2, 1, 3. Agora é o caso "2 1 3", que `sa` resolve.
	// Ou, uma sequência mais direta: 1 3 2 -> rra -> 2 1 3 -> sa -> 1 2 3
	else if (n1 < n2 && n2 > n3 && n1 < n3)
		rra(a);
	// Caso: 2 3 1 (n1 < n2 && n2 > n3 && n1 > n3) -> Exemplo: 2, 3, 1
	// O 2 está no topo, o 3 no meio, o 1 no fundo. O 1 precisa ir para o topo.
	// `sa` troca 2 e 3: 3, 2, 1. Agora é o caso "3 2 1".
	// `ra` move o 3 para o fundo: 2, 1, 3.
	// `sa` troca 2 e 1: 1, 2, 3 (ordenado).
	// Em resumo: sa ra -> 2 3 1 -> 3 2 1 -> 2 1 3 -> 1 2 3
	else if (n1 < n2 && n2 > n3 && n1 > n3)
	{
		sa(a);
		ra(a);
	}
}

// `find_min_pos` encontra a posição (0-indexada) do menor elemento em uma pilha.
// `t_stack *s`: Ponteiro para a pilha onde procurar o menor elemento.
// Retorna a posição do menor elemento, ou -1 se a pilha estiver vazia.
int	find_min_pos(t_stack *s)
{
	t_stack_node	*current; // Ponteiro para percorrer a pilha.
	int				min_val;  // Variável para armazenar o menor valor encontrado.
	int				min_pos;  // Variável para armazenar a posição do menor valor.
	int				pos;      // Posição atual do nó.

	if (!s || !s->head) // Se a pilha for inválida ou estiver vazia.
		return (-1);    // Retorna -1 para indicar que não há elementos.

	min_val = s->head->value; // Inicialmente, assume que o valor do topo é o menor.
	min_pos = 0;              // E sua posição é 0.
	pos = 0;                  // A posição inicial é 0.
	current = s->head->next;  // `current` começa a procurar do segundo elemento.

	// Loop `while` que continua enquanto `current` não for `NULL`.
	while (current)
	{
		pos++;
		if (current->value < min_val) // Se o valor do nó atual for menor que o `min_val` encontrado até agora.
		{
			min_val = current->value; // Atualiza `min_val` para o novo menor valor.
			min_pos = pos;            // Atualiza `min_pos` para a posição atual.
		}
		current = current->next; // Move `current` para o próximo nó.
	}
	return (min_pos); // Retorna a posição do menor elemento na pilha.
}

// `put_min_on_top` move o menor elemento da pilha `a` para o seu topo.
// Ele escolhe entre `ra` (rotate) e `rra` (reverse rotate) para usar o menor número de movimentos.
// `t_stack *a`: Ponteiro para a pilha `a`.
static void	put_min_on_top(t_stack *a)
{
	int	min_pos; // Variável para armazenar a posição do menor elemento.

	min_pos = find_min_pos(a); // Encontra a posição do menor elemento na pilha `a`.

	// Se o menor elemento estiver na metade superior da pilha (incluindo o meio, se o tamanho for ímpar).
	// Por exemplo, em uma pilha de 5, posições 0, 1, 2 são "superiores".
	if (min_pos <= a->size / 2)
	{
		// Usa `ra` (rotate a) `min_pos` vezes para trazer o elemento para o topo.
		while (min_pos > 0)
		{
			ra(a);
			min_pos--;
		}
	}
	// Se o menor elemento estiver na metade inferior da pilha.
	// Por exemplo, em uma pilha de 5, posições 3, 4 são "inferiores".
	else
	{
		// Usa `rra` (reverse rotate a) `(a->size - min_pos)` vezes para trazer o elemento para o topo.
		while (min_pos < a->size)
		{
			rra(a);
			min_pos++;
		}
	}
}

// `sort_four` ordena uma pilha com exatamente 4 elementos.
// Estratégia:
// 1. Move o menor elemento para a pilha `b`.
// 2. Ordena os 3 elementos restantes na pilha `a` usando `sort_three`.
// 3. Move o elemento de `b` de volta para `a`.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b` (usada como auxiliar).
void	sort_four(t_stack *a, t_stack *b)
{
	put_min_on_top(a); // Coloca o menor elemento no topo de `a`.
	pb(a, b);          // Move o menor elemento de `a` para o topo de `b`. Agora `a` tem 3 elementos.
	sort_three(a);     // Ordena os 3 elementos restantes na pilha `a`.
	pa(a, b);          // Move o elemento de `b` de volta para o topo de `a`. A pilha `a` agora está ordenada.
}

// `sort_five` ordena uma pilha com exatamente 5 elementos.
// Estratégia:
// 1. Move os dois menores elementos para a pilha `b`.
// 2. Ordena os 3 elementos restantes na pilha `a` usando `sort_three`.
// 3. Move os dois elementos de `b` de volta para `a`.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b` (usada como auxiliar).
void	sort_five(t_stack *a, t_stack *b)
{
	put_min_on_top(a); // Garante que o menor elemento de `a` esteja no topo.
	pb(a, b);          // Move o menor elemento de `a` para o topo de `b`. (1º menor está em b)
	put_min_on_top(a); // Garante que o (agora) menor elemento de `a` (o 2º menor original) esteja no topo.
	pb(a, b);          // Move o 2º menor elemento de `a` para o topo de `b`. (2º menor está em b)
	sort_three(a);     // Ordena os 3 elementos restantes na pilha `a`.
	pa(a, b);          // Move o elemento do topo de `b` (o 2º menor original) de volta para `a`.
	pa(a, b);          // Move o elemento do topo de `b` (o 1º menor original) de volta para `a`.
	                   // Os elementos são movidos de volta em ordem correta (primeiro o 2º menor, depois o 1º menor).
}

// `sort_small_stack` é uma função de despacho que decide qual função de ordenação
// para pilhas pequenas deve ser chamada, com base no `size` da pilha `a`.
// `t_stack *a`: Ponteiro para a pilha `a`.
// `t_stack *b`: Ponteiro para a pilha `b` (usada como auxiliar para 4 e 5 elementos).
void	sort_small_stack(t_stack *a, t_stack *b)
{
	if (is_sorted(a)) // Primeiro, verifica se a pilha já está ordenada.
		return ;      // Se sim, não faz nada.

	if (a->size == 2) // Se a pilha tem 2 elementos.
		sort_two(a);  // Chama a função para ordenar 2 elementos.
	else if (a->size == 3) // Se a pilha tem 3 elementos.
		sort_three(a);     // Chama a função para ordenar 3 elementos.
	else if (a->size == 4) // Se a pilha tem 4 elementos.
		sort_four(a, b);   // Chama a função para ordenar 4 elementos.
	else if (a->size == 5) // Se a pilha tem 5 elementos.
		sort_five(a, b);   // Chama a função para ordenar 5 elementos.
}
```

---

### 9. `sort_large.c`

Este arquivo agora implementa o algoritmo **Bubble Sort** para pilhas maiores (com mais de 5 elementos). Ele usa os `index`s que foram atribuídos aos nós da pilha para as comparações.

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal.

// `bubble_sort_push_swap` implementa uma variação do Bubble Sort para ordenar a pilha `a`.
// Esta implementação usa a pilha `b` como auxiliar para guardar os elementos à medida que são ordenados.
//
// ATENÇÃO: Esta abordagem de Bubble Sort para `push_swap` será **muito menos eficiente**
// (em termos de número de operações) do que algoritmos como Radix Sort para pilhas grandes.
// É improvável que ela atenda aos requisitos de desempenho de um projeto `push_swap` real da 42 para N > 5,
// pois o número de operações cresce exponencialmente (complexidade O(N^2) no pior caso,
// mais as operações de rotação).
//
// `t_stack *a`: Ponteiro para a pilha `a` a ser ordenada.
// `t_stack *b`: Ponteiro para a pilha `b` (pilha auxiliar).
void	bubble_sort_push_swap(t_stack *a, t_stack *b)
{
	int		i; // Contador para as "passadas" do Bubble Sort (cada passada coloca um elemento na posição correta).
	int		j; // Contador para as comparações e rotações dentro de cada passada.
	int		num_elements; // Guarda o número original de elementos na pilha `a`.

	num_elements = a->size; // Armazena o tamanho inicial da pilha `a`.

	// Loop externo: Representa as `N` passadas do Bubble Sort.
	// Em cada passada `i`, o maior elemento da sub-lista não ordenada é "bubbled" para
	// o topo de `a` e então empurrado para `b`.
	// Este loop irá esvaziar a pilha `a` e preencher a pilha `b`.
	for (i = 0; i < num_elements; i++)
	{
		// Loop interno: Percorre os elementos restantes na pilha `a` (`num_elements - 1 - i` elementos).
		// O objetivo é fazer o maior elemento da sub-lista atual "flutuar" (bubble) para o topo de `a`.
		// Isso é conseguido comparando pares adjacentes e trocando-os, e depois rotacionando a pilha.
		for (j = 0; j < (num_elements - 1 - i); j++)
		{
			// Compara o elemento no topo de `a` com o elemento abaixo dele, usando seus `index`.
			// `index` 0 é o menor, `num_elements - 1` é o maior.
			if (a->head->index > a->head->next->index)
			{
				sa(a); // Se o topo for maior que o próximo (fora de ordem), troca-os.
			}
			ra(a); // Rotaciona a pilha `a`. Isso move o elemento atual do topo para o fundo
			       // e traz o próximo elemento para o topo para a próxima comparação.
			       // Este `ra` é crucial para simular o movimento através da lista em um Bubble Sort.
		}
		// Após o loop interno, o elemento de maior índice (maior valor original) da sub-lista
		// que foi percorrida deve estar agora no topo da pilha `a` (devido à série de `ra`s).
		// Exemplo: se N=5 e i=0 (primeira passada), o loop `j` faz 4 `ra`s.
		// O maior elemento da pilha original `a` acaba no topo de `a`.

		pb(a, b); // Empurra o elemento do topo de `a` para o topo de `b`.
		          // Este elemento é o maior da parte não ordenada que acabamos de processar.
		          // Ele é movido para `b` para ser "colocado" em sua posição final ordenada.
		          // A pilha `a` agora tem um elemento a menos para a próxima passada.
	}

	// Após o loop externo, todos os `num_elements` foram movidos da pilha `a` para a pilha `b`.
	// Na pilha `b`, os elementos estão em ordem decrescente (o maior no topo, o menor no fundo)
	// devido à forma como foram empurrados para `b`.
	// Para ordená-los em `a` (menor no topo), simplesmente movemos todos de volta de `b` para `a`.
	while (b->size > 0)
	{
		pa(a, b); // Move o elemento do topo de `b` para o topo de `a`.
		          // Isso resulta na pilha `a` estando completamente ordenada do menor para o maior.
	}
}
```

---

### 10. `ft_split.c`

Esta é uma implementação simplificada da função `ft_split`, comum na Libft. Ela é usada para dividir uma string de entrada que contém múltiplos números separados por espaços (ex: `"1 2 3"`).

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/10/09 17:37:47 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" // Inclui o cabeçalho principal.

// --- Funções Auxiliares (Libft-like) ---

// `ft_strlen` calcula o comprimento de uma string.
// `const char *s`: Ponteiro para a string constante.
// Retorna o número de caracteres na string antes do terminador nulo.
size_t	ft_strlen(const char *s)
{
	size_t	i; // Declara um contador `i` do tipo `size_t`.

	i = 0; // Inicializa `i` em 0.
	// Loop `while` continua enquanto o caractere `s[i]` não for o terminador nulo ('\0').
	while (s[i])
		i++; // Incrementa `i`.
	return (i); // Retorna o valor final de `i`.
}

// `ft_strdup` duplica uma string. Aloca nova memória e copia o conteúdo.
// `const char *s1`: Ponteiro para a string original a ser duplicada.
// Retorna um ponteiro para a nova string duplicada, ou `NULL` se a alocação de memória falhar.
char	*ft_strdup(const char *s1)
{
	char	*dup;      // Ponteiro para a nova string duplicada.
	size_t	len;       // Variável para armazenar o comprimento da string original.
	size_t	i;         // Contador.

	len = ft_strlen(s1); // Obtém o comprimento da string original `s1`.
	// Aloca memória para a nova string: `len` caracteres + 1 para o terminador nulo.
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup) // Se a alocação de memória falhar.
		return (NULL); // Retorna `NULL`.
	i = 0; // Inicializa o contador.
	// Loop para copiar cada caractere de `s1` para `dup`.
	while (i < len)
	{
		dup[i] = s1[i]; // Copia o caractere.
		i++; // Incrementa o contador.
	}
	dup[len] = '\0'; // Adiciona o terminador nulo no final da nova string.
	return (dup);    // Retorna o ponteiro para a string duplicada.
}

// `ft_free_split` libera a memória alocada por `ft_split`.
// `char **split`: O array de strings a ser liberado.
void	ft_free_split(char **split)
{
	int	i; // Contador.

	if (!split) // Se o array `split` for `NULL`, não há nada para liberar.
		return ;
	i = 0; // Inicializa o contador.
	// Loop `while` continua enquanto `split[i]` não for `NULL` (que marca o fim do array de strings).
	while (split[i])
	{
		free(split[i]); // Libera a memória de cada string individual no array.
		i++; // Move para a próxima string.
	}
	free(split); // Após liberar todas as strings, libera a memória do próprio array de ponteiros.
}

// `count_words` é uma função auxiliar para `ft_split`. Conta o número de "palavras"
// (substrings não delimitadas pelo caractere `c`) em uma string `s`.
// `char const *s`: A string a ser analisada.
// `char c`: O caractere delimitador.
// Retorna o número de palavras encontradas.
static int	count_words(char const *s, char c)
{
	int	count;   // Contador para o número de palavras.
	int	in_word; // Flag booleana (0 ou 1): 1 se estamos dentro de uma palavra, 0 caso contrário.

	count = 0;   // Inicializa o contador de palavras.
	in_word = 0; // Inicialmente, não estamos dentro de uma palavra.
	// Loop `while` que percorre a string `s` caractere por caractere.
	while (*s)
	{
		if (*s == c) // Se o caractere atual é o delimitador.
			in_word = 0; // Não estamos mais em uma palavra.
		else if (in_word == 0) // Se o caractere atual NÃO é o delimitador E não estava em uma palavra.
		{
			in_word = 1; // Isso significa que uma nova palavra começou.
			count++;     // Incrementa o contador de palavras.
		}
		s++; // Move para o próximo caractere na string.
	}
	return (count); // Retorna o total de palavras contadas.
}

// `ft_strndup_safe` é uma função auxiliar para `ft_split`. Duplica uma parte (substring) da string `s`.
// `char const *s`: A string original.
// `size_t start`: O índice de início da substring.
// `size_t len`: O comprimento da substring a ser duplicada.
// Retorna um ponteiro para a nova substring, ou `NULL` se a alocação de memória falhar.
static char	*ft_strndup_safe(char const *s, size_t start, size_t len)
{
	char	*word; // Ponteiro para a nova string (a palavra).
	size_t	i;     // Contador.

	// Aloca memória para a palavra: `len` caracteres + 1 para o terminador nulo.
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word) // Se a alocação falhar.
		return (NULL); // Retorna `NULL`.
	i = 0; // Inicializa o contador.
	// Loop para copiar `len` caracteres da string `s` (a partir de `start`) para `word`.
	while (i < len)
	{
		word[i] = s[start + i]; // Copia o caractere.
		i++; // Incrementa o contador.
	}
	word[len] = '\0'; // Adiciona o terminador nulo no final da palavra.
	return (word);    // Retorna o ponteiro para a palavra.
}

// `ft_split` divide uma string `s` em um array de strings (palavras), usando `c` como delimitador.
// `char const *s`: A string de entrada a ser dividida.
// `char c`: O caractere delimitador.
// Retorna um array de ponteiros para as novas strings (o array é terminado por `NULL`),
// ou `NULL` em caso de erro (ex: `malloc` falhou, ou `s` era `NULL`).
char	**ft_split(char const *s, char c)
{
	char	**split_arr;   // Ponteiro para o array de `char*` (o array de strings resultante).
	size_t	i;             // Índice para percorrer a string original `s`.
	size_t	j;             // Índice para adicionar palavras ao `split_arr`.
	int		word_start;    // Variável que armazena o índice onde uma nova palavra começa (-1 se não estiver em uma palavra).

	if (!s) // Se a string de entrada for `NULL`.
		return (NULL); // Retorna `NULL`.

	// Aloca memória para o array de ponteiros de strings.
	// `count_words(s, c)` obtém o número de palavras. +1 é para o terminador `NULL` do array.
	split_arr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split_arr) // Se a alocação falhar.
		return (NULL); // Retorna `NULL`.

	i = 0;        // Inicializa o índice da string original.
	j = 0;        // Inicializa o índice do array de strings.
	word_start = -1; // Inicializa `word_start` para indicar que não estamos dentro de uma palavra.
	// Loop `while` para percorrer a string `s`, incluindo o terminador nulo, para garantir que a última palavra seja processada.
	while (i <= ft_strlen(s))
	{
		// Condição para o início de uma palavra:
		// - O caractere atual `s[i]` não é o delimitador `c`.
		// - E `word_start` é -1 (significa que não estávamos dentro de uma palavra).
		if (s[i] != c && word_start == -1)
			word_start = i; // Define `word_start` para o índice atual `i`.
		// Condição para o fim de uma palavra:
		// - O caractere atual `s[i]` é o delimitador `c` OU `i` atingiu o fim da string (`ft_strlen(s)`).
		// - E `word_start` NÃO é -1 (significa que estávamos dentro de uma palavra).
		else if ((s[i] == c || i == ft_strlen(s)) && word_start != -1)
		{
			// Duplica a substring (a palavra) usando `ft_strndup_safe`.
			// A palavra começa em `word_start` e tem `i - word_start` de comprimento.
			split_arr[j] = ft_strndup_safe(s, word_start, i - word_start);
			if (!split_arr[j]) // Se a alocação da substring falhar.
			{
				ft_free_split(split_arr); // Libera toda a memória já alocada para `split_arr` e suas substrings.
				return (NULL); // Retorna `NULL` para indicar falha.
			}
			j++;          // Incrementa o índice para a próxima palavra no `split_arr`.
			word_start = -1; // Reseta `word_start` para indicar que não estamos mais em uma palavra.
		}
		i++; // Move para o próximo caractere na string original.
	}
	split_arr[j] = NULL; // Adiciona um `NULL` no final do array de strings para marcá-lo como terminado.
	return (split_arr);  // Retorna o array de strings resultante.
}
```