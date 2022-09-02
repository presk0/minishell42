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

void	set_in(char **argv)
{
	int		fd;
	int		i;

	i = 0;
	while (argv[i] && ft_memcmp(argv[i], "<", 2))
		i++;
	if (argv[i])
	{
		fd = open(argv[i + 1], O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("Couldn't read from file.\n", 2);
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}

int	redir_out(t_data *param)
{
	int 	len;
	int	i;
	int	nb_redir;

	len = ft_matrixlen(param->f_matrix);
	i = 0;
	nb_redir = 0;
	while (i < len)
	{
		if (!ft_memcmp(param->f_matrix[i], ">", 2))
		{
			if (nb_redir < 255)
				param->fd_out[nb_redir++] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		}
		else if (!ft_memcmp(param->f_matrix[i], ">>", 3))
		{
			if (nb_redir < 255)
				param->fd_out[nb_redir++] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
		}
		i++;
	}
	return (nb_redir);
}

int	redir_in(t_data *param)
{
	int 	len;
	int	i;
	int	nb_redir;

	len = ft_matrixlen(param->f_matrix);
	i = 0;
	nb_redir = 0;
	while (i < len && param->f_matrix[i + 1] && param->f_matrix[i])
	{
		if (!ft_memcmp(param->f_matrix[i], "<", 2))
		{
			if (nb_redir < 255)
				param->fd_in[nb_redir++] = open(param->f_matrix[i + 1], O_RDONLY, 0666);
		}
		i++;
	}
	return (nb_redir);
	//printf(stderr, "[redir_in] end fd);
}

