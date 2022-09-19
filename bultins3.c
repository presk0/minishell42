/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:42:36 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 08:43:00 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(t_data *param, int fd)
{
	int	i;

	i = 0;
	if (param->argc != 1)
	{
		ft_putstr_fd(" env : permission denied\n", 2);
		param->retour = 126;
		return ;
	}
	while (param->envp[i])
	{
		ft_putstr_fd(param->envp[i], fd);
		write(fd, "\n", 1);
		i++;
	}
}

void	error(t_data *param)
{
	if (param->argc > 0 && !ft_memcmp(param->argv[0], "$?", 3))
		printf("%d\n", param->retour);
}
