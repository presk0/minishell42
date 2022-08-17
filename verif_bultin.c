/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_bultin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 08:26:00 by swalter           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/16 16:06:38 by swalter          ###   ########.fr       */
=======
/*   Updated: 2022/08/16 10:34:52 by swalter          ###   ########.fr       */
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_bultin(t_data *param)
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
<<<<<<< HEAD
	else if (!ft_memcmp(param->input_cleaned, "/", 1) || !ft_memcmp(param->input_cleaned, "./", 2) || !ft_memcmp(param->input_cleaned, "../", 3))
		return (1);	
=======
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
	else
		return (0);
}
