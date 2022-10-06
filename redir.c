/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:22:40 by marvin            #+#    #+#             */
/*   Updated: 2022/10/06 12:03:58 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_bultin(t_data *param)
{
	int	fd_in;
	int	fd_out;

	fd_in = redir_in(param->f_matrix);
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

void	redir_execute_single(t_data *param, int (*fds)[2])
{
	(*fds)[0] = dup(redir_in(param->f_matrix));
	(*fds)[1] = dup(redir_out(param->f_matrix));
	dup2((*fds)[0], STDIN_FILENO);
	dup2((*fds)[1], STDOUT_FILENO);
}

void	init_fd_child(t_data *param, int (*fds)[2], int fd)
{
	int	fd_tmp;

	fd_tmp = 0;
	(*fds)[1] = redir_out(param->f_matrix);
	fd_tmp = redir_in(param->f_matrix);
	if (fd_tmp == 0)
		(*fds)[0] = fd;
	else
		(*fds)[0] = fd_tmp;
}

void	redir_fd_child(int fds[2], int end[2], int i, int j)
{
	dup2(fds[0], STDIN_FILENO);
	if (fds[1] != 1)
		dup2(fds[1], STDOUT_FILENO);
	else if (i < j - 1)
		dup2(end[1], STDOUT_FILENO);
}
