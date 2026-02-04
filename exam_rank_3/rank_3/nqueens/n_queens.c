#include <stdio.h>
#include <stdlib.h>

int		abs(int n);
void	solution(int *board, int n);
int		safe(int *board, int col, int row);
void	solve(int *board, int col, int n);

int	main(int argc, char **argv)
{
	int	n;
	int	*board;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	board = malloc(sizeof(int) * n);
	if (!board)
		return (1);
	solve(board, 0, n);
	free(board);
	return (0);
}

void	solve(int *board, int col, int n)
{
	int	row;

	row = 0;
	if (col == n)
	{
		solution(board, n);
		return ;
	}
	while (row < n)
	{
		if (safe(board, col, row))
		{
			board[col] = row;
			solve(board, col +1, n);
		}
		row++;
	}
}

int	safe(int *board, int col, int row)
{
	int	prev;

	prev = 0;
	while (prev < col)
	{
		if (board[prev] == row)
			return (0);
		if (abs(board[prev] - row) == col - prev)
			return (0);
		prev++;
	}
	return (1);
}

void	solution(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < n -1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

int	abs(int n)
{
	return (n < 0 ? -n : n);
}
