#include "minishell.h"

static char	*ft_realloc_cat(char *line, char c, int *len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *) malloc(*len + 2);
	if (!ret)
		return (NULL);
	while (i < *len && line)
	{
		ret[i] = line[i];
		i++;
	}
	ret[*len] = c;
	ret[++(*len)] = '\0';
	if (line)
		free(line);
	return (ret);
}

char	*get_next_line(int fd)
{
	char	c;
	char	*line;
	int		len;

	len = 0;
	line = NULL;
	while (1)
	{
		if (read(fd, &c, 1) > 0)
			line = ft_realloc_cat(line, c, &len);
		else
			(c = '\0');
		if (c == '\n' || !c)
			return (line);
	}
	return (NULL);
}
