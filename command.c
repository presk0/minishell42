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

int	redir_out(char **f_matrix)
{
	int		ret;
	int 	len;
	int	fd;
	int	i;

(void) ret;
	len = ft_matrixlen(f_matrix);
	i = 0;
	fd = 1;
	while (i < len)
	{
		if (!ft_memcmp(f_matrix[i], ">", 2))
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (!ft_memcmp(f_matrix[i], ">>", 3))
		{
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
		}
		i++;
	}
	return (fd);
}

int	redir_in(char **f_matrix)
{
	int		ret;
	int 	len;
	int 	fd;
	int	i;
	int last_redir;

(void)ret;
	len = ft_matrixlen(f_matrix);
	i = 0;
	last_redir = 0;
	fd = 0;
	while (i < len && f_matrix[i + 1] && f_matrix[i])
	{
		if (!ft_memcmp(f_matrix[i], "<", 2))
		{
			fd = open(f_matrix[i + 1], O_RDONLY, 0666);
		}
			/*
		else if (!ft_memcmp(f_matrix[i], "<<", 3))
		{
			fd = open(f_matrix[i + 1], O_RDONLY, 0666);
			ret = 0;
			while ((ret = read(fd, &c, 1)))
				if (ret == -1)
				{
					write(2, "Couldn't read file\n", 19);
					break ;
				}
		}
		*/
		if (!ft_memcmp(f_matrix[i], "<", 1))
		{
			if (last_redir)
				close(last_redir);
			last_redir = fd;
		}
		i++;
	}
	//printf(stderr, "[redir_in] end fd[0] = %d\n", fd);
	return (fd);
}

