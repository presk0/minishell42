/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/20 18:50:14 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **pop_names_from_sep(t_data *param, int i, char **sep)
{
    char    *cmd_cpy;
    char    **fname_matrix;
    char    **cmd_split;
    int     j;

    cmd_cpy = param->cmds[i];
    cmd_split = ft_split_multistrsep(cmd_cpy, sep, 1);
    j = 1;
    fname_matrix = NULL;
    if (cmd_split && cmd_split[j])
    {
        while (cmd_split[j])
        {
            fname_matrix = ft_append_tab(fname_matrix, pop_first_wd(&cmd_split[j++]));
        }
        free(param->input_cleaned);
        param->input_cleaned = matrix_to_str(cmd_split);
		printf("[input_cleaned in pop_manes_from_sep] %s\n", param->input_cleaned);
        ft_free_split(cmd_split);
    }
    return (fname_matrix);
}