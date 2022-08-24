/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/24 14:51:31 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		parser(t_data *param)
{
	int		i;
	int		nb_cmd;
	char	**sep;
	int		*fd;
	
	fd = malloc(sizeof(int) * 2);
	// if (!fd)
	// 	error;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);

	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	ft_free_split(sep);
	sep = NULL;
	nb_cmd = 0;
	sep = ft_split(">>,>,<<,<", ',');
	
	while (param->cmds[nb_cmd])
		nb_cmd++;
	i = 0;
	while (i < nb_cmd - 1)
	{
		param->f_matrix = pop_names_from_sep(param, i, sep);
		fprintf(stderr, "[parser] param->cmds[i] =  %s\n", param->cmds[i]);
		child_process(param, i, &fd);
		i++;
	}
	param->f_matrix = pop_names_from_sep(param, i, sep);
	fprintf(stderr, "[parser] param->cmds[i] =  %s\n", param->cmds[i]);
	execute(param, 0, fd);
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
//	dup2(0, STDIN_FILENO);
}

