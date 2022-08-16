/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 08:24:43 by swalter           #+#    #+#             */
/*   Updated: 2022/08/16 08:24:43 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_exit(t_data *param)
{
    if (!ft_memcmp(param->argv[0], "exit", 5))
		run_exit(param);

}

void	run_exit(t_data *param)
{
	int	i;

    if (param->argc > 2)
	{
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        param->retour = 1;
    } 
	else
	{
        i = 0;
        while (param->argc > 1 && ft_isdigit(param->argv[1][i]))
            i++;
        if (param->argc > 1 && param->argv[1][i]) {
            ft_putstr_fd("minishell: exit: : numeric argument required\n", 2);
            param->retour = 2;
        }
        if (param->argc > 1 && param->retour != 2)
            i = ft_atoi(param->argv[1]);
        else
            i = param->retour;
        //free_param(param);
        exit(i);
    }
}    
