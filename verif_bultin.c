/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_bultin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 08:26:00 by swalter           #+#    #+#             */
/*   Updated: 2022/08/17 11:41:08 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_bultin(t_data *param)
{
	if (!ft_memcmp("echo", param->input_cleaned, 4))
		return (1);
	else if (!ft_memcmp(param->input_cleaned, "pwd", 4))
		return (1);
	else if (!ft_memcmp(param->input_cleaned, "export", 6))
		return (1);
	else if (!ft_memcmp(param->input_cleaned, "env", 4))
		return (1);
	else if (!ft_memcmp(param->input_cleaned, "unset", 5))
		return (1);
	else if (!ft_strncmp("cd", param->input_cleaned, 2))
		return (1);
	else if (!ft_strncmp("exit", param->input_cleaned, 4))
		return (1);
	//else if (!ft_memcmp(param->input_cleaned, "/", 1) || !ft_memcmp(param->input_cleaned, "./", 2) || !ft_memcmp(param->input_cleaned, "../", 3))
//			return (1);	
	else
		return (0);
}

int	verif_bultin(t_data *param)
{
	char	*to_trim;

	to_trim = param->input_cleaned;
	param->input_cleaned = ft_strtrim(to_trim, " \t");
	free(to_trim);
	if (param->input_cleaned)
	{
		if (ft_is_bultin(param))
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}
