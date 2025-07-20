#include <unistd.h>

void	ft_putstr(char *s, int len)
{
	write(1, s, len);
	write(1, "\n", 1);
}

void	count_to_remove(char *s, int *open_rem, int *close_rem)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	*open_rem = 0;
	*close_rem = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open == 0)
				(*close_rem)++;
			else
				open--;
		}
		i++;
	}
	*open_rem = open;
}

void	recurse(char *s, int i, int open_rem, int close_rem, int bal, char *out,
		int o)
{
	if (!s[i])
	{
		if (open_rem == 0 && close_rem == 0 && bal == 0)
			ft_putstr(out, o);
		return ;
	}
	if (s[i] == '(')
	{
		if (open_rem > 0)
			recurse(s, i + 1, open_rem - 1, close_rem, bal, out, o);
		out[o] = '(';
		recurse(s, i + 1, open_rem, close_rem, bal + 1, out, o + 1);
	}
	else if (s[i] == ')')
	{
		if (close_rem > 0)
			recurse(s, i + 1, open_rem, close_rem - 1, bal, out, o);
		if (bal > 0)
		{
			out[o] = ')';
			recurse(s, i + 1, open_rem, close_rem, bal - 1, out, o + 1);
		}
	}
	else
	{
		out[o] = s[i];
		recurse(s, i + 1, open_rem, close_rem, bal, out, o + 1);
	}
}

int	main(int ac, char **av)
{
	char	out[1000];

	if (ac == 2)
	{
		int open_rem, close_rem;
		count_to_remove(av[1], &open_rem, &close_rem);
		recurse(av[1], 0, open_rem, close_rem, 0, out, 0);
	}
	else
		write(1, "\n", 1);
	return (0);
}
