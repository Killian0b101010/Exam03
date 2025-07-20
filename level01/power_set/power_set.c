#include <stdio.h>
#include <stdlib.h>

void	print(int *nums, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d", nums[i]);
		if (i < n - 1)
			printf(" ");
	}
	printf("\n");
}

int	seen_before(int *nums, int start, int current)
{
	for (int i = start; i < current; i++)
		if (nums[i] == nums[current])
			return (1);
	return (0);
}

void	solve(int *nums, int size, int target, int *subset, int subsize,
		int index)
{
	if (target == 0 && subsize > 0)
	{
		print(subset, subsize);
		return ;
	}
	if (target < 0)
		return ;
	for (int i = index; i < size; i++)
	{
		if (seen_before(nums, index, i))
			continue ;
		subset[subsize] = nums[i];
		solve(nums, size, target - nums[i], subset, subsize + 1, i + 1);
	}
}

int	main(int ac, char **av)
{
	int	target;
	int	size;
	int	*nums;
	int	*subset;

	if (ac < 3)
		return (0);
	target = atoi(av[1]);
	size = ac - 2;
	nums = malloc(sizeof(int) * size);
	subset = malloc(sizeof(int) * size);
	if (!nums || !subset)
		return (1);
	for (int i = 0; i < size; i++)
		nums[i] = atoi(av[i + 2]);
	solve(nums, size, target, subset, 0, 0);
	free(nums);
	free(subset);
	return (0);
}
