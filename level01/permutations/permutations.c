#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
int	ft_dup(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] == str[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
void	ft_sort(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (str[i] > str[j])
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
			j++;
		}
		i++;
	}
}
void	generate(char *str, char *result, int *used, int len, int depth)
{
	int	i;

	if (len == depth)
	{
		write(1, result, len);
		write(1, "\n", 1);
		return ;
	}
	i = 0;
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			result[depth] = str[i];
			generate(str, result, used, len, depth + 1);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int ac, char **argv)
{
	if (ac != 2 || ft_dup(argv[1]))
		return (1);

	int *used;
	char *result;

	int len = ft_strlen(argv[1]);
	used = calloc(len,sizeof(int));
	result = malloc(sizeof(char) * len + 1);
	if (!used || !result)
		return (1);
	ft_sort(argv[1]);
	generate(argv[1], result, used, len, 0);
	free(used);
	free(result);
	return (0);
}