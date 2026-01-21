#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Estrutura para armazenar soluções únicas
typedef struct s_solution
{
	char *str;
	struct s_solution *next;
} t_solution;

// Lista de soluções encontradas
t_solution *g_solutions = NULL;

// Adiciona solução à lista se não existir duplicata
void add_solution(char *str)
{
	t_solution *node;
	t_solution *current;

	// Verifica se já existe essa solução
	current = g_solutions;
	while (current)
	{
		if (strcmp(current->str, str) == 0)
			return ;  // Já existe
		current = current->next;
	}

	// Aloca novo nó
	node = malloc(sizeof(t_solution));
	if (!node)
		return ;
	node->str = malloc(strlen(str) + 1);
	if (!node->str)
	{
		free(node);
		return ;
	}
	strcpy(node->str, str);
	node->next = g_solutions;
	g_solutions = node;
}

// Imprime todas as soluções armazenadas
void print_solutions(void)
{
	t_solution *current;

	current = g_solutions;
	while (current)
	{
		puts(current->str);
		current = current->next;
	}
}

// Libera memória das soluções
void free_solutions(void)
{
	t_solution *current;
	t_solution *next;

	current = g_solutions;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

// Calcula mínimo de remoções necessárias a partir de uma posição
// Retorna -1 se impossível, ou número de remoções
int min_removals_from(char *str, int pos, int open, int close)
{
	int i;
	int temp_open;
	int temp_close;

	temp_open = open;
	temp_close = close;
	i = pos;
	while (str[i])
	{
		if (str[i] == '(')
			temp_open++;
		else if (str[i] == ')')
		{
			if (temp_open > 0)
				temp_open--;
			else
				temp_close++;
		}
		i++;
	}
	// Se temp_open > 0, temos '(' não fechados no final
	return (temp_close + temp_open);
}

// Função recursiva de backtracking
void solve(char *str, int pos, char *current, int open, int close, int removed, int *min_removed)
{
	int needed;
	int len;

	// Se removed > *min_removed, não vale continuar
	if (removed > *min_removed)
		return ;

	// Se chegou ao final
	if (!str[pos])
	{
		// Se temos uma solução balanceada
		if (open == 0 && close == 0)
		{
			// Se usou exatamente o mínimo de remoções
			if (removed == *min_removed)
				add_solution(current);
		}
		return ;
	}

	// Calcula mínimo necessário daqui em diante
	needed = min_removals_from(str, pos, open, close);
	if (removed + needed > *min_removed)
		return ;

	len = strlen(current);

	// Opção 1: Manter '('
	if (str[pos] == '(')
	{
		current[len] = '(';
		current[len + 1] = '\0';
		solve(str, pos + 1, current, open + 1, close, removed, min_removed);
		current[len] = '\0';
	}
	// Opção 2: Manter ')'
	else if (str[pos] == ')')
	{
		if (open > 0)
		{
			current[len] = ')';
			current[len + 1] = '\0';
			solve(str, pos + 1, current, open - 1, close, removed, min_removed);
			current[len] = '\0';
		}
	}

	// Opção 3: Remover (espaço)
	current[len] = ' ';
	current[len + 1] = '\0';
	solve(str, pos + 1, current, open, close, removed + 1, min_removed);
	current[len] = '\0';
}

// Calcula o número mínimo de remoções necessárias
int calc_min_removals(char *str)
{
	int open;
	int close;
	int i;

	open = 0;
	close = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			open++;
		else if (str[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

int main(int argc, char **argv)
{
	char *str;
	char *current;
	int min_removed;

	if (argc != 2)
		return (1);

	str = argv[1];

	// Aloca buffer para solução
	current = malloc(strlen(str) + 1);
	if (!current)
		return (1);
	current[0] = '\0';

	// Calcula mínimo
	min_removed = calc_min_removals(str);

	// Resolve
	solve(str, 0, current, 0, 0, 0, &min_removed);

	// Imprime soluções
	print_solutions();

	// Libera memória
	free(current);
	free_solutions();
	return (0);
}
