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

static void	refresh_fd(int *last_fd, int *fd)
{
	if (*last_fd > 1)
		close(*last_fd);
	*last_fd = *fd;
}

int	redir_out(char **f_matrix)
{
	int	fd;
	int	last_fd;
	int	i;

	i = 0;
	fd = 1;
	last_fd = 0;
	while (i < ft_matrixlen(f_matrix))
	{
		if (!ft_memcmp(f_matrix[i], ">", 2))
		{
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			refresh_fd(&last_fd, &fd);
		}
		else if (!ft_memcmp(f_matrix[i], ">>", 3))
		{
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			refresh_fd(&last_fd, &fd);
		}
		i++;
	}
	return (fd);
}

int	redir_in(t_data	*param, char **f_matrix)
{
	int	fd;
	int	i;
	int	last_fd;

	i = 0;
	last_fd = 0;
	fd = 0;
	while (i < ft_matrixlen(f_matrix) && f_matrix[i + 1] && f_matrix[i])
	{
		if (!ft_memcmp(f_matrix[i], "<", 2))
		{
			fd = open(f_matrix[i + 1], O_RDONLY, 0666);
			refresh_fd(&last_fd, &fd);
		}
		else if (!ft_memcmp(f_matrix[i], "<<", 3))
		{
			fd = heredoc(param, f_matrix[i + 1]);
			refresh_fd(&last_fd, &fd);
		}
		i++;
	}
	return (fd);
}

void	redir_bultin(t_data *param)
{
	int	fd_in;
	int	fd_out;

	fd_in = redir_in(param, param->f_matrix);
	fd_out = redir_out(param->f_matrix);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	init_fd_child(t_data *param, int (*fds)[2], int fd)
{
	(*fds)[1] = redir_out(param->f_matrix);
	(*fds)[0] = redir_in(param, param->f_matrix);
	if ((*fds)[0] == 0)
		(*fds)[0] = fd;
}

void	redir_fd_child(int fds[2], int end[2], int i, int j)
{
	dup2(fds[0], STDIN_FILENO);
	if (fds[1] != 1)
		dup2(fds[1], STDOUT_FILENO);
	else if (i < j - 1)
        dup2(end[1], STDOUT_FILENO);
}
