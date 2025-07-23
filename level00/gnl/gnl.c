#include "gnl.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*gnl(int fd)
{
	static int	buffer_read = 0;
	static int	buffer_pos = 0;
	static char	buffer[BUFFER_READ];
	char		line[100000];
	int			i;

	i = 0;
	if (BUFFER_READ <= 0 || fd < 0)
		return (NULL);
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_READ);
			buffer_pos = 0;
			if (buffer_read == 0)
				break ;
		}
		line[i++] = buffer[buffer_pos++];
		if (line[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}

int	main(void)
{
	char *line;
	int fd = open("subject.txt", O_RDONLY);
	line = gnl(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = gnl(fd);
	}
	close(fd);
	return (0);
}