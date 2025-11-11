/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:31:30 by kakubo-l          #+#    #+#             */
/*   Updated: 2025/11/11 16:29:20 by kakubo-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* headers padrão necessários para o projeto */
# include <stdlib.h> /* malloc, free */
# include <unistd.h> /* write */
# include <limits.h> /* INT_MAX, INT_MIN */
# include "../libft/libft.h" /* biblioteca auxiliar (dlist, ft_printf, etc) */

/*
** Estrutura principal: representa as duas pilhas do push_swap
** stack->a: pilha A (inicialmente contém os números a ordenar)
** stack->b: pilha B (auxiliar, inicialmente vazia)
*/
typedef struct s_stack
{
	t_dlist	*a; /* ponteiro para a pilha A (dlist duplamente ligada) */
	t_dlist	*b; /* ponteiro para a pilha B (dlist duplamente ligada) */
}	t_stack;

/* ===== PARSING E VALIDAÇÃO ===== */
/* função principal que faz o parsing dos argumentos */
int		parse_arguments(int argc, char **argv, t_stack *stack);
/* verifica se uma string representa um número válido */
int		is_valid_number(char *str);
/* verifica se há duplicatas em um array de inteiros */
int		has_duplicates(int *arr, int size);
/* libera um array de strings (resultado de ft_split) */
void	free_split(char **split);
/* converte string para long (detecta overflow) */
long	ft_atol(const char *str);

/* ===== HELPERS INTERNOS DE PARSING ===== */
/* conta o número de palavras em uma string separadas por um caractere */
int		ps_count_words(char const *s, char c);
/* processa um único argumento (pode conter múltiplos números) */
int		ps_process_single_arg(char *arg, t_stack *stack);
/* verifica duplicatas dentro da pilha A */
int		ps_check_duplicates_in_stack(t_dlist *stack);
/* indexa os valores de A (0..n-1 baseado na ordem) */
void	ps_index_stack(t_stack *stack);

/* ===== INICIALIZAÇÃO E LIMPEZA ===== */
/* aloca e inicializa uma nova estrutura t_stack com duas dlists vazias */
t_stack	*init_stack(void);
/* libera toda a memória associada à stack (pilhas, nós e dados) */
void	free_stack(t_stack *stack);
/* função que libera um dado int (usada em ft_clean_dlist) */
void	free_int(void *data);

/* ===== OPERAÇÕES BÁSICAS DO PUSH_SWAP ===== */
/* sa: swap os dois primeiros da pilha A */
void	sa(t_stack *stack, int print);
/* sb: swap os dois primeiros da pilha B */
void	sb(t_stack *stack, int print);
/* ss: sa + sb em uma operação */
void	ss(t_stack *stack);
/* pa: push (move topo de B para topo de A) */
void	pa(t_stack *stack, int print);
/* pb: push (move topo de A para topo de B) */
void	pb(t_stack *stack, int print);
/* ra: rotate A (move head para tail) */
void	ra(t_stack *stack, int print);
/* rb: rotate B (move head para tail) */
void	rb(t_stack *stack, int print);
/* rr: ra + rb */
void	rr(t_stack *stack);
/* rra: reverse rotate A (move tail para head) */
void	rra(t_stack *stack, int print);
/* rrb: reverse rotate B (move tail para head) */
void	rrb(t_stack *stack, int print);
/* rrr: rra + rrb */
void	rrr(t_stack *stack);

/* ===== HELPERS INTERNOS DE PUSH ===== */
/* copia o valor do topo de `from` para um novo int alocado */
int		copy_top_value(t_dlist *from, int **out);
/* remove o primeiro nó da pilha (libera nó e dado) */
void	detach_head_node(t_dlist *from);
/* insere um valor alocado no topo da pilha destino */
void	push_value_to_dest(t_dlist *to, int *value_copy);

/* ===== FUNÇÕES AUXILIARES / UTILITÁRIOS ===== */
/* verifica se uma dlist está ordenada em ordem crescente */
int		is_sorted(t_dlist *stack);
/* retorna o valor inteiro armazenado em um nó */
int		get_value(t_dnode *node);
/* encontra o valor mínimo em uma dlist */
int		find_min_value(t_dlist *stack);
/* encontra o valor máximo em uma dlist */
int		find_max_value(t_dlist *stack);
/* encontra a posição (índice) de um valor em uma dlist */
int		find_position(t_dlist *stack, int value);
/* calcula a menor distância até o topo usando ra ou rra */
int		distance_to_top(t_dlist *stack, int position);

/* ===== ALGORITMOS DE ORDENAÇÃO ===== */
/* função roteadora que escolhe o algoritmo apropriado baseado no tamanho */
void	sort_stack(t_stack *stack);
/* ordena 2 elementos com até 1 operação */
void	sort_2(t_stack *stack);
/* ordena 3 elementos com até 2-3 operações */
void	sort_3(t_stack *stack);
/* ordena 4+ elementos usando chunking ou estratégias para 4/5 */
void	sort_many(t_stack *stack);

/* ===== CHECKER HELPERS ===== */
/* aplica uma operação (string como "ra\n") na stack e retorna 1 se válida */
int		apply_op(t_stack *stack, const char *op);

/* ===== HELPER FUNCTIONS PARA ORDENAÇÃO (PHASES) ===== */
/* traz um elemento na posição 'position' de B para o topo escolhendo rb ou rrb */
void	move_to_top_b(t_stack *stack, int position);
/* segunda fase: reinsere todos os elementos de B de volta em A (do maior para o menor) */
void	phase_pull_b_to_a(t_stack *stack, int size);
/* traz o menor elemento de A para o topo e o move para B (operação auxiliar para 4/5) */
void	bring_min_to_top_and_pb(t_stack *stack);
/* trata casos especiais de 4 e 5 elementos, retorna 1 se tratou, 0 caso contrário */
int		handle_small_cases(t_stack *stack, int size);

#endif