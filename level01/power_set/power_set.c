#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *subset, int subsize)
{
	if (subsize == 0)
	{
		printf("\n");
		return ;
	}
	for (int i = 0; i < subsize; i++)
	{
		printf("%d", subset[i]);
		if (i < subsize - 1)
			printf(" ");
	}
	printf("\n");
}

void	generate(int *set, int size, int target, int *subset, int index,
		int subsize, int sum)
{
	if (index == size)
	{
		if (sum == target)
			print_subset(subset, subsize);
		return ;
	}
	// Sans l’élément set[index]
	generate(set, size, target, subset, index + 1, subsize, sum);
	// Avec l’élément set[index]
	subset[subsize] = set[index];
	generate(set, size, target, subset, index + 1, subsize + 1, sum
		+ set[index]);
}

int	main(int ac, char **av)
{
	int	target;
	int	size;
	int	*set;
	int	*subset;

	if (ac < 2)
		return (0);
	target = atoi(av[1]);
	size = ac - 2;
	set = NULL;
	subset = NULL;
	if (size < 0)
		size = 0;
	if (size > 0)
	{
		set = malloc(sizeof(int) * size);
		if (!set)
			return (1);
		subset = malloc(sizeof(int) * size);
		if (!subset)
		{
			free(set);
			return (1);
		}
		for (int i = 0; i < size; i++)
			set[i] = atoi(av[i + 2]);
	}
	else
	{
		// Cas où il n'y a pas d'ensemble, solution vide si target == 0
		if (target == 0)
			printf("\n");
		return (0);
	}
	generate(set, size, target, subset, 0, 0, 0);
	free(set);
	free(subset);
	return (0);
}
