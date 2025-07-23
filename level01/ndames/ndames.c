/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ndames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:39:46 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/23 22:16:22 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Moulinette Certified 21/07/25.
#include <stdio.h>
#include <stdlib.h>

int	is_safe(int *position, int current_row, int current_col)
{
	int	row_prev;

	for (int col_prev = 0; col_prev < current_col; col_prev++)
	{
		row_prev = position[col_prev];
		if (current_row == row_prev || current_row + current_col == row_prev
			+ col_prev || current_row - current_col == row_prev - col_prev)
			return (0);
	}
	return (1);
}
void	solve(int *position, int col, int i)
{
	if (i == col)
	{
		for (int j = 0; j < i; j++)
		{
			if (j > 0)
				fprintf(stdout, " ");
			fprintf(stdout, "%d", position[j]);
		}
		fprintf(stdout, "\n");
		return ;
	}
	for (int row = 0; row < i; row++)
	{
		if (is_safe(position, row, col))
		{
			position[col] = row;
			solve(position, col + 1, i);
		}
	}
}
int	main(int ac, char **argv)
{
	int	num;
	int	*ptr;

	if (ac != 2)
		return (0);
	num = atoi(argv[1]);
	if (num == 0)
		return (0);
	if (num == 2 || num == 3)
		return (1);
	ptr = malloc(sizeof(int) * num);
	if (!ptr)
		return (1);
	solve(ptr, 0, num);
	free(ptr);
	return (0);
}
