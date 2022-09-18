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

int	is_available_var_name(char *var, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		if (!(ft_isalnum(var[j]) || var[j] == '_'))
		{
			free(var);
			write(2, "not a valid identifier\n", 23);
			return (0);
		}
		j++;
	}
	return (1);
}

char	**export_command(t_data *param, int j)
{
	int		i;
	char	*new_var;
	int		spliter_index;
	char	**quote_split;

	i = 0;
	new_var = param->argv[j]; //test=blabla
	// if test='bla bla', ce qui est entre quote est stocke dans l;argument suivant
	if (new_var[ft_strlen(new_var) - 1] == '=' && param->argv[j + 1])
	{
		new_var = ft_strjoin(param->argv[j], param->argv[j + 1]);
		free(param->argv[j]);
		param->argv[j] = NULL;
		free(param->argv[j + 1]);
		param->argv[j + 1] = NULL;
		param->argv[j] = new_var;
	}
	quote_split = quotes_spaces_split(new_var);
	new_var = matrix_to_str(quote_split);
	ft_free_split(&quote_split);
	spliter_index = ft_strlen_char(new_var, '=');
	if (is_available_var_name(new_var, spliter_index))
	{
		while (param->envp[i])
		{
			if (!ft_strncmp(new_var, param->envp[i], spliter_index + 1))
			{
				param->envp = free_matrix_line(param->envp, i);
				break ;
			}
			i++;
		}
		param->envp = ft_append_tab(param->envp, new_var);
	}
	return (param->envp);
}

/*
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
*/
char	**run_export(t_data *param)
{
	char	**env;

	env = param->envp;
	if (param->argv[1] == NULL)
		print_env_tri(param);
	else
		param->envp = export_command(param, 1); 
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
