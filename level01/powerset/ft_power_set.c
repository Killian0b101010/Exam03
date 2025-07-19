/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 04:40:22 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/19 05:10:35 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	print(int buf_index, int *buffer, int *flag)
{
	int	i;

	*flag = 1;
	i = 0;
	while (i < buf_index)
	{
		printf("%d", buffer[i]);
		if (buf_index - 1 != i)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_power(int target, int max_ac, int *tab, int *buffer, int i_tab,
		int i_buffer, int *flag)
{
	int	i;

	i = 0;
	if (i_tab == max_ac)
	{
		if (target == 0 && i_buffer > 0)
			print(i_buffer, buffer, flag);
		return ;
	}
	ft_power(target, max_ac, tab, buffer, i_tab + 1, i_buffer, flag);
	buffer[i_buffer] = tab[i_tab];
	ft_power(target - tab[i_tab], max_ac, tab, buffer, i_tab + 1, i_buffer + 1,
		flag);
}

int	main(int ac, char **argv)
{
	int	*buffer;
	int	*tab;
	int	target;
	int	max_ac;
	int	i;
	int	flag;

	flag = 0;
	if (ac < 2)
		return (0);
	buffer = 0;
	tab = 0;
	target = 0;
	max_ac = (ac - 2);
	target = atoi(argv[1]);
	i = 0;
	buffer = malloc(sizeof(int) * max_ac);
	tab = malloc(sizeof(int) * max_ac);
	if (!buffer || !tab)
		return (1);
	while (i < max_ac)
	{
		tab[i] = atoi(argv[i + 2]);
		i++;
	}
	ft_power(target, max_ac, tab, buffer, 0, 0, &flag);
	if (flag == 0)
		printf("\n");
	free(buffer);
	free(tab);
	return (0);
}
