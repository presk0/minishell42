/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/23 18:29:59 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void		parser(t_data *param)
{
	int		i;
	char	**sep;
	int		*fd;
	
	fd = malloc(sizeof(int) * 2);
	// if (!fd)
	// 	error;
	fd[0] = 0;
	fd[1] = 1;

	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	ft_free_split(sep);
	sep = NULL;
	i = 0;
	sep = ft_split(">>,>,<<,<", ',');
	
	while (param->cmds[i])
		i++;
	if (i == 1)
	{
		param->f_matrix = pop_names_from_sep(param, 0, sep);
		execute(param, 0, fd);
	}	
	else
	{	
		int j = i;
		i = 0;
		while (i < j - 1)
		{
			param->f_matrix = pop_names_from_sep(param, i, sep);
			child_process(param, i, &fd);
			i++;
		}
		param->f_matrix = pop_names_from_sep(param, i, sep);
		//fd[0] = STDIN_FILENO;
		//fd[1] = STDOUT_FILENO;
		execute(param, i, fd);
	}
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
//	dup2(0, STDIN_FILENO);
}

