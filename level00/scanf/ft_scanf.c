/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scanf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiteixei <kiteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 00:07:20 by kiteixei          #+#    #+#             */
/*   Updated: 2025/07/19 21:16:33 by kiteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int	match_space(FILE *f)
{
	int	i;

	i = fgetc(f);
	while (i != EOF)
	{
		if (!isspace(i))
		{
			ungetc(i, f);
			break ;
		}
		i = fgetc(f);
	}
	return (0);
}

int	match_char(FILE *f, char c)
{
	int	match;

	match = fgetc(f);
	if (match == EOF)
		return (-1);
	if (match == c)
		return (1);
	ungetc(match, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*ptr;
	int		i;

	i = fgetc(f);
	ptr = va_arg(ap, char *);
	if (i == EOF)
		return (-1);
	*ptr = (char)i;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int	i;
	int	num;
	int	sign;
	int	is_number;
	int	*ptr;

	i = fgetc(f);
	num = 0;
	sign = 1;
	is_number = 0;
	ptr = va_arg(ap, int *);
	if (i == '-' || i == '+')
	{
		if (i == '-')
			sign = -1;
		i = fgetc(f);
	}
	while (i != EOF && isdigit(i))
	{
		num = num * 10 + (i - '0');
		is_number = 1;
		i = fgetc(f);
	}
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
	int		count;
	char	*ptr;

	count = 0;
	ptr = va_arg(ap, char *);
	get = fgetc(f);
	while (get != EOF && !isspace(get))
	{
		ptr[count++] = (char)get;
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

#include <stdio.h>

int	ft_scanf(const char *format, ...);

int	main(void)
{
	int		nb;
	char	c;
	char	str[100];

	ft_scanf("%d %c %s", &nb, &c, str);
	// printf("%d\n%c\n%s\n", nb, c, str);
	return (0);
}
