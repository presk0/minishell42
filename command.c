/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:22:40 by marvin            #+#    #+#             */
/*   Updated: 2022/08/30 18:12:28 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out(char **f_matrix)
{
	int 	len;
	int	fd;
	int	last_fd;
	int	i;

	len = ft_matrixlen(f_matrix);
	i = 0;
	fd = 1;
	last_fd = 0;
	while (i < len)
	{
		if (!ft_memcmp(f_matrix[i], ">", 2))
		{
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (last_fd > 1)
				close(last_fd);
			last_fd = fd;
		}
		else if (!ft_memcmp(f_matrix[i], ">>", 3))
		{
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			if (last_fd > 1)
				close(last_fd);
			last_fd = fd;
		}
		i++;
	}
	return (fd);
}

int	heredoc(t_data *param, char *stop_str)
{
	int		fd;
	int		first_loop;
	char	*line;
	char	*text;
	char	*tmp;
	struct termios	term;

	first_loop = 1;
	text = NULL;
	line = NULL;
	while (first_loop || !line || ft_strncmp(line, stop_str, ft_strlen(stop_str)))
	{
		init_sig(&term, param);
		if (!first_loop)
		{
			tmp = line;
			line = ft_strjoin(line, "\n");
			free(tmp);
			tmp = text;
			if (text)
			{
			//	if (line)
					text = ft_strjoin(text, line);
				free(tmp);
			}
			else
				text = line;
			//if (first_loop == -1)
			//	break ;
		}
		line = readline("> ");
		if (!line)
		{
			write(2, "\nwarning: here-document delimited by end-of-file\n", 50);
			break ;
			//first_loop = -1;
		}
		first_loop = 0;
	}
	init_sig(&term, param);
	fd = open("heredoc", O_WRONLY | O_CREAT, 0666);
	if (text)
		write(fd, text, ft_strlen(text));
	close(fd);
	free(text);
	free(line);
	fd = open("heredoc", O_RDONLY);
	return (fd);
}

int	redir_in(t_data* param, char **f_matrix)
{
	int 	len;
	int 	fd;
	int	i;
	int last_fd;

	len = ft_matrixlen(f_matrix);
	i = 0;
	last_fd = 0;
	fd = 0;
	while (i < len && f_matrix[i + 1] && f_matrix[i])
	{
		if (!ft_memcmp(f_matrix[i], "<", 2))
		{
			fd = open(f_matrix[i + 1], O_RDONLY, 0666);
			if (last_fd)
				close(last_fd);
			last_fd = fd;
		}
		else if (!ft_memcmp(f_matrix[i], "<<", 3))
		{
			fd = heredoc(param, f_matrix[i + 1]);
			if (last_fd)
				close(last_fd);
			last_fd = fd;
		}
		i++;
	}
	return (fd);
}

