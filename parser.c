/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/17 12:41:20 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void init_fd(t_data *param, int **fd, int **io_fd)
{
	int		i;
	int		len;
	(void)io_fd;
	if (!fd)
		return ;
	i = 0;
	if (!*fd)
		return ;
	(*fd)[0] = 0;
	(*fd)[1] = 1;
	(*io_fd)[0] = 0;
	(*io_fd)[1] = 1;
	if (param->f_matrix)
	{
		//printf(stderr, "[init_fd]\n");
		//print_tab(param->f_matrix);
		len = ft_matrixlen(param->f_matrix);
		while (i < len)
		{
			if (!ft_memcmp(param->f_matrix[i], ">", 2) && param->f_matrix[i + 1])
			{
				(*io_fd)[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
				//printf(stderr, "[init_fd] file opened: fd[1]= %d\n", (*io_fd)[1]);
			}
			else if(!ft_memcmp(param->f_matrix[i], ">>", 3) && param->f_matrix[i + 1])
			{
				(*io_fd)[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
				//printf(stderr, "[init_fd] file opened: fd[1]= %d\n", (*io_fd)[1]);
			}
			else if (!ft_memcmp(param->f_matrix[i], "<", 2) && param->f_matrix[i + 1])
			{
				(*io_fd)[0] = open(param->f_matrix[i + 1], O_RDONLY, 0666);
				//printf(stderr, "[init_fd] file opened: fd[0]= %d\n", (*io_fd)[0]);
			}
			i++;
		}
		//printf(stderr, "[init_fd] before_check: fd[0]= %d, fd[1]=%d\n", (*fd)[0], (*fd)[1]);
	}
	dup2((*io_fd)[0], (*fd)[0]);
	dup2((*io_fd)[1], (*fd)[1]);
}

void	reinit_after_pipe(t_data *param, int **io_fd)
{
	if (param->f_matrix)
		ft_free_split(&param->f_matrix);
	param->f_matrix = NULL;
	if ((*io_fd)[0] != STDIN_FILENO)
	{
		close((*io_fd)[0]);
		(*io_fd)[0] = STDIN_FILENO;
	}
	if ((*io_fd)[1] != STDOUT_FILENO)
	{
		close((*io_fd)[1]);
		(*io_fd)[1] = STDOUT_FILENO;
	}
}

