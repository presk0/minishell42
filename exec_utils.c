/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:20:01 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 08:20:05 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_failed(t_data *param, char ***cmd)
{
	param->retour = 126;
	ft_putstr_fd("command not found\n", 2);
	ft_free_split(cmd);
	exit(param->retour);
}
