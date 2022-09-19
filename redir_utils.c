/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:24:05 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 08:24:09 by swalter          ###   ########.fr       */
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

static int	redir_if_file_exist(int *fd, char **f_matrix, int *last_fd, int i)
{
	*fd = open(f_matrix[i + 1], O_RDONLY, 0666);
	if (*fd != -1)
	{
		refresh_fd(last_fd, fd);
		return (1);
	}
	else
	{
		write(2, "No such file or directory\n", 27);
		*fd = 0;
		return (0);
	}
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
			redir_if_file_exist(&fd, f_matrix, &last_fd, i);
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
