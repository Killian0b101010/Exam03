

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 1024

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
		i++;
	return (s1[i] - s2[i]);
}
int	main(int ac, char **av)
{
	char	buffer[BUF_SIZE];

	int word_len, n, i;
	if (ac != 2 || !*av[1])
		return (1);
	word_len = strlen(av[1]);
	while ((n = read(0, buffer, BUF_SIZE)) > 0)
	{
		i = 0;
		while (i < n)
		{
			if (i <= n - word_len && strncmp(&buffer[i], av[1], word_len) == 0)
			{
				for (int j = 0; j < word_len; j++)
					write(1, "*", 1);
				i += word_len;
			}
			else
				write(1, &buffer[i++], 1);
		}
	}
	if (n < 0)
	{
		fprintf(stderr, "Error: ");
		perror("");
		return (1);
	}
	return (0);
}
