/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/19 14:30:54 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	heredoc_write(char **text, char **line)
{
	int	fd;

	fd = open("heredoc", O_WRONLY | O_CREAT, 0666);
	if (*text)
		write(fd, *text, ft_strlen(*text));
	close(fd);
	free(*text);
	if (*line)
		free(*line);
	close(fd);
}

void	heredoc_func(t_data *param, char *stop_str)
{
	int				first_loop;
	char			*line;
	char			*text;
	char			*tmp;

	(void)param;
	first_loop = 1;
	text = NULL;
	line = NULL;
	while (first_loop || !line || \
		ft_strncmp(line, stop_str, ft_strlen(stop_str) + 1))
	{
		if (heredoc_loop(&first_loop, &line, &tmp, &text) == NULL)
			break ;
	}
	heredoc_write(&text, &line);
}

int	heredoc(t_data *param, char *stop_str)
{
	int				pid;
	static int		child_pid;
	int				main_pid;
	int				fd;
	struct termios	tmp;

	main_pid = g_pid;
	fd = -1;
	pid = fork();
	if (pid)
		child_pid = pid;
	if (!pid)
	{
		g_pid = child_pid;
		signal(SIGINT, &handler_heredoc);
		heredoc_func(param, stop_str);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		g_pid = main_pid;
		init_sig(&tmp, param);
	}
	fd = open("heredoc", O_RDONLY);
	return (fd);
}
