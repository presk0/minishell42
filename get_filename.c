/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_filename.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/19 14:11:43 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *pop_input_filenames(char *cmd)
{
    char    *cmd_cpy;
    char    **sep;
    char    **fname_matrix;
    char    **cmd_split;
    int     i;

    sep = ft_split("<<,<", ',');
    cmd_cpy = cmd;
    cmd_split = ft_split_multisep(cmd, sep, 1);
    i = 1;
    fname_matrix = NULL;
    if (cmd_split && cmd_split[i])
    {
        while (cmd_split[i])
        {
            fname_matrix = ft_append_tab(fname_matrix, pop_first_wd(&cmd_split[i++]));
        }

    }
    return (fname_matrix);
}