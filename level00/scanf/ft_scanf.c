/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:07:20 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/19 00:35:12 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int	match_space(FILE *f)
{
	int	i;

	i = getc(f);
	while (i != EOF)
	{
		if (!isspace(i))
		{
			ungetc(i, f);
			break ;
		}
		i = getc(f);
	}
	return (0);
}

int	match_char(FILE *f, char c)
{
	int	match;

	match = getc(f);
	if (match == EOF)
		return (-1);
	if (match == c)
		return (1);
	else
		ungetc(match, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*ptr;
	int		i;

	i = getc(f);
	ptr = va_arg(ap, char *);
	if (i == EOF)
		return (-1);
	*ptr = (char)i;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int	i;
	int	is_number;
	int	*ptr;
	int	sign;
	int	num;

	num = 0;
	sign = 1;
	is_number = 0;
	ptr = va_arg(ap, int *);
	i = getc(f);
	// gestion signe
	if (i == '-' || i == '+')
	{
		if (i == '-')
			sign = -1;
		i = fgetc(f);
	}
	// Affichage des nombres
	while (isdigit(i) && i != EOF)
	{
		num = num * 10 + (i - '0');
		is_number = 1;
		i = fgetc(f);
	}
	// gestion d'erreur
	if (!is_number)
		return (-1);
	if (i != EOF)
		ungetc(i, f);
	*ptr = num * sign;
	return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	int		get;
	char	*ptr;
	int		count;

	get = 0;
	count = 0;
	ptr = va_arg(ap, char *);
	get = fgetc(f);
	while (get != EOF && (!isspace(get)))
	{
		ptr[count] = (char)get;
		count++;
		get = fgetc(f);
	}
	if (get != EOF)
		ungetc(get, f);
	if (count == 0)
		return (-1);
	ptr[count] = '\0';
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
	case 'c':
		return (scan_char(f, ap));
	case 'd':
		match_space(f);
		return (scan_int(f, ap));
	case 's':
		match_space(f);
		return (scan_string(f, ap));
	case EOF:
		return (-1);
	default:
		return (-1);
	}
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	nconv;
	int	c;

	nconv = 0;
	c = fgetc(f);
	if (c == EOF)
		return (EOF);
	ungetc(c, f);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break ;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break ;
		}
		else if (match_char(f, *format) != 1)
			break ;
		format++;
	}
	if (ferror(f))
		return (EOF);
	return (nconv);
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
void	run_test(int use_ft)
{
	int		nb;
	char	str[100];
	char	c;
	int		ret;

	if (use_ft)
	{
		ret = ft_scanf("%d %s %c", &nb, str, &c);
		printf("%d %d %s %c\n", ret, nb, str, c);
	}
	else
	{
		ret = scanf("%d %s %c", &nb, str, &c);
		printf("%d %d %s %c\n", ret, nb, str, c);
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	if (strcmp(av[1], "ft") == 0)
		run_test(1);
	else if (strcmp(av[1], "scanf") == 0)
		run_test(0);
	else
		printf("Usage: ./scanf_test [scanf|ft]\n");
	return (0);
}