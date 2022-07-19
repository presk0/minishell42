/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/19 15:07:21 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **pop_names_from_sep(t_data *param, char **sep)
{
    char    *cmd_cpy;
    char    **fname_matrix;
    char    **cmd_split;
    int     i;

    cmd_cpy = param->input_cleaned;
    cmd_split = ft_split_multistrsep(cmd_cpy, sep, 1);
    i = 1;
    fname_matrix = NULL;
    if (cmd_split && cmd_split[i])
    {
        while (cmd_split[i])
        {
            fname_matrix = ft_append_tab(fname_matrix, pop_first_wd(&cmd_split[i++]));
        }
        free(param->input_cleaned);
        param->input_cleaned = matrix_to_str(cmd_split);
        ft_free_split(cmd_split);
    }
    return (fname_matrix);
}