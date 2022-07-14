/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/13 20:03:43 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	split with pipes 		=> matrix
	split with << or <    	=> consider only the last one
	split with > >> 		=> make all files and write (or append) only the last
*/

void		parser(t_data *param)
{
	int i;
	char **cmd_matrix;
	char **sep;

	sep = ft_split(">>,>,<<,<", ',');
	i = 0;
	// fork 
	while (param->cmds[i])
	{
		// pipe
		cmd_matrix = ft_split_multistrsep(param->input, sep, 1);
		// check input file
		// clean input line
		// make (all) output files
		i++;
	}
	free_matrix(sep);
	free_matrix(param->cmds);
}

