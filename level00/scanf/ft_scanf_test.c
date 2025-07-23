#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

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
	int	i;

	i = fgetc(f);
	if (i == EOF)
		return (-1);
	if (i == c)
		return (1);
	ungetc(i, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	int		i;
	char	*ptr;

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
	int	*ptr;
	int	sign;
	int	is_number;
	int	number;

	i = fgetc(f);
	number = 0;
	sign = 1;
	is_number = 0;
	ptr = va_arg(ap, int *);
	if (i == '+' || i == '-')
	{
		if (i == '-')
			sign = -1;
		i = fgetc(f);
	}
	while (i != EOF && isdigit(i))
	{
		number = number * 10 + (i - '0');
		is_number = 1;
		i = fgetc(f);
	}
	if (!is_number)
		return (-1);
	if (i != EOF)
		ungetc(i, f);
	*ptr = number * sign;
	return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	int		count;
	char	*ptr;
	int		i;

	count = 0;
	ptr = va_arg(ap, char *);
	i = fgetc(f);
	while (i != EOF && !isspace(i))
	{
		ptr[count++] = (char)i;
		i = fgetc(f);
	}
	if (i != EOF)
		ungetc(i, f);
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

int	main(void)
{
	int i;
	char ptr[100];
	char c;

	ft_scanf("%d %s %c", &i, ptr, &c);
	printf("%d\n%s\n%c\n", i, ptr, c);
}