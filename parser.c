/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/09/19 08:22:39 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_data *param)
{
	int		i;
	int		j;
	int		end[2];
	int		fds[2];

	j = set_cmds(param);
	i = 0;
	if (j == 1)
		single_cmd(param);
	else
	{
		while (i < j)
		{
			exec_pipes(param, &end, &fds, i, j);
			i++;
		}
	}
	i = 3;
	while (i < 256)
		close(i++);
}
