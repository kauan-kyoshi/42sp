/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_verifications.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 10:56:36 by nde-sant          #+#    #+#             */
/*   Updated: 2025/06/08 18:42:02 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	fill_row(int reverse, int reference, char **dest_matrix)
{
	int	i;

	if (reverse > 0)
	{
		i = 3;
		while (i >= 0)
		{
			dest_matrix[reference][i] = '4' - i;
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < 4)
		{
			dest_matrix[reference][i] = '1' + i;
			i++;
		}
	}
}

void	fill_col(int reverse, int reference, char **dest_matrix)
{
	int	i;

	if (reverse > 0)
	{
		i = 3;
		while (i >= 0)
		{
			dest_matrix[i][reference] = '4' - i;
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < 4)
		{
			dest_matrix[i][reference] = '1' + i;
			i++;
		}
	}
}

void	fill_fours(char **origin_matrix, char **dest_matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{	
			if (origin_matrix[i][j] == '4')
			{
				if (i == 0)
					fill_col(0, j, dest_matrix);
				else if (i == 1)
					fill_col(1, j, dest_matrix);
				else if (i == 2)
					fill_row(0, j, dest_matrix);
				else
					fill_row(1, j, dest_matrix);
			}
			j++;
		}
		i++;
	}
}

void	fill_ones(char **origin_matrix, char **dest_matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (origin_matrix[i][j] == '1')
			{
				if (i == 0)
					dest_matrix[0][j] = '4';
				else if (i == 1)
					dest_matrix[3][j] = '4';
				else if (i == 2)
					dest_matrix[j][0] = '4';
				else
					dest_matrix[j][3] = '4';
			}
			j++;
		}
		i++;
	}
}
