#include "minishell.h"

int	rm_heredoc_file(void)
{
	int		fd;
	int		pid;
	char	**rm_cmd;

	rm_cmd = ft_split("/bin/rm heredoc", ' ');
	fd = open(rm_cmd[1], O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		pid = fork();
		if (pid == -1)
			write(2, "rm_heredoc_file error\n", 22);
		else if (pid == 0)
		{
			execve(rm_cmd[0], rm_cmd, NULL);
			exit(1);
		}
		else
			wait(NULL);
	}
	ft_free_split(&rm_cmd);
	return (1);
}

char	*heredoc_loop(int *first_loop, char **line, char **tmp, char **text)
{
	if (!*first_loop)
	{
		*tmp = *line;
		*line = ft_strjoin(*tmp, "\n");
		free(*tmp);
		*tmp = *text;
		if (*text)
		{
			*text = ft_strjoin(*tmp, *line);
			free(*tmp);
			free(*line);
		}
		else
		{
			*text = ft_strdup(*line);
			free(*line);
		}
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
	if (*text)
		write(fd, *text, ft_strlen(*text));
	close(fd);
	free(*text);
	if (*line)
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
	//struct termios	term;

	(void)param;
	first_loop = 1;
	text = NULL;
	line = NULL;
	while (first_loop || !line || \
		ft_strncmp(line, stop_str, ft_strlen(stop_str) + 1))
	{
		//init_sig(&term, param);
		if (heredoc_loop(&first_loop, &line, &tmp, &text) == NULL)
			break ;
	}
	//init_sig(&term, param);
	return (heredoc_fd(&text, &line));
}

