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
    int j = 0;
	char	**cmd_split;

	param->cmds = ft_split_strsep(param->str, "|", 1);
	i = 0;
	while (param->cmds[i])
	{
		// check input file
		// clean input line

		param->cmds = ft_split_strsep(param->str, "<", 0);
		/*
		check_env(&(param->cmds[i]), param);
		param->argc = count_args(param->cmds[i]);
		param->argv = (char **)ft_calloc(sizeof(char *), (param->argc + 1));
		set_args(param->argv, param->cmds[i], param->argc);
        printf("argv = %s\n", param->argv[0]);
        param->export = check_export(param);
        check_command(param);
		*/
		free_matrix(param->argv);
		i++;
	}
	free(param->str);
	param->str = NULL;
	free_matrix(param->cmds);
}