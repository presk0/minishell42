/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:18:16 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 08:18:32 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_env(char **envp, int i)
{
	char	**new;
	int		j;

	new = ft_calloc(sizeof(char *), ft_matrixlen(envp));
	j = 0;
	while (j < i)
	{
		new[j] = ft_strdup(envp[j]);
		j++;
	}
	i++;
	while (envp[i])
	{
		new[j] = ft_strdup(envp[i]);
		i++;
		j++;
	}
	j = 0;
	while (new[j])
		j++;
	free(envp);
	return (new);
}

char	*get_env(char **envp, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = ft_strlen(env);
	i = 0;
	while (envp[i] && ft_memcmp(env, envp[i], len))
		i++;
	if (envp[i])
		tmp = envp[i] + len;
	else
		tmp = 0;
	free(env);
	return (tmp);
}
