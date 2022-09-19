/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/23 14:20:32 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pop_names_from_sep_refresh(t_data *param, char ***cmd_split)
{
	if (param->input_cleaned)
		free(param->input_cleaned);
	param->input_cleaned = NULL;
	param->input_cleaned = matrix_to_str(*cmd_split);
	ft_free_split(cmd_split);
}

char	**pop_names_from_sep(t_data *param, int i, char **sep)
{
	char	*cmd_cpy;
	char	**fname_matrix;
	char	**cmd_split;
	int		j;

	cmd_cpy = param->cmds[i];
	cmd_split = ft_split_multistrsep(cmd_cpy, sep, 1);
	j = 1;
	fname_matrix = NULL;
	if (cmd_split && cmd_split[j])
	{
		while (cmd_split[j])
		{
			fname_matrix = ft_append_tab(fname_matrix, \
				pop_first_wd(&cmd_split[j++]));
		}
		pop_names_from_sep_refresh(param, &cmd_split);
	}
	else
		pop_names_from_sep_refresh(param, &cmd_split);
	return (fname_matrix);
}
