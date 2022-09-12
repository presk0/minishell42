/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:03:16 by swalter           #+#    #+#             */
/*   Updated: 2022/08/31 15:08:32 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_command2(t_data *param, int j)
{
	int		i;
	char	**cpy;
	int		len;
	int		a;

	a = 0;
	i = 0;
	len = 0;
	while (param->argv[j][a] != '=')
	{
			len++;
			a++;
	}		
	while (param->envp[i] && ft_memcmp(param->envp[i], param->argv[j], len))
		i++;
	if (!param->envp[i])
	{
		cpy = copy_env(param->envp, 1);
		cpy[i] = param->argv[j];
		ft_free_split(&param->envp);
	}
	else
	{
		cpy = param->envp;
		free(param->envp[i]);
		param->envp[i] = param->argv[j];
	}
	return (cpy);
}

char	**run_export(t_data *param)
{
	char	**env;

	env = param->envp;
	if (param->argv[1] == NULL)
		print_env_tri(param);
	else
		param->envp = export_command2(param, 1); 
	return (env);
}

static char	**tri_env(t_data *param)
{
	char	**tableau;
	int		i;
	char	*temp;

	tableau = param->envp;
	i = 0;
	while (tableau[i] && tableau[i + 1])
	{
		if (strcmp(tableau[i], tableau[i + 1]) > 0)
		{
			temp = tableau[i];
			tableau[i] = tableau[i + 1];
			tableau[i + 1] = temp;
			i = -1;
		}
		i++;
	}
	return (tableau);
}

void	print_env_tri(t_data *param)
{
	int		i;
	char	**tabl;

	i = 0;
	tabl = tri_env(param);
	while (tabl[i] != NULL)
	{
		printf("declare -x ");
		printf("%s\n", tabl[i]);
		i++;
	}
}
