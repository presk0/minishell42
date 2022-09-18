#include "minishell.h"

char	*heredoc_loop(int *first_loop, char **line, char **tmp, char **text)
{
	if (!*first_loop)
	{
		*tmp = *line;
		*line = ft_strjoin(*line, "\n");
		free(*tmp);
		*tmp = *text;
		if (*text)
		{
			*text = ft_strjoin(*text, *line);
			free(*tmp);
		}
		else
			*text = *line;
	}
	*line = readline("> ");
	if (!*line)
		write(2, "\nwarning: here-document delimited by end-of-file\n", 50);
	*first_loop = 0;
	return (*line);
}

int	heredoc_fd(char **text, char **line)
{
	int	fd;

	fd = open("heredoc", O_WRONLY | O_CREAT, 0666);
	if (text)
		write(fd, *text, ft_strlen(*text));
	close(fd);
	free(*text);
	free(*line);
	fd = open("heredoc", O_RDONLY);
	return (fd);
}

int	heredoc(t_data *param, char *stop_str)
{
	int				first_loop;
	char			*line;
	char			*text;
	char			*tmp;
	struct termios	term;

	first_loop = 1;
	text = NULL;
	line = NULL;
	while (first_loop || !line || \
		ft_strncmp(line, stop_str, ft_strlen(stop_str)))
	{
		init_sig(&term, param);
		if (heredoc_loop(&first_loop, &line, &tmp, &text) == NULL)
			break ;
	}
	init_sig(&term, param);
	return (heredoc_fd(&text, &line));
}

