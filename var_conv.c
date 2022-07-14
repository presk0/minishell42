/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/11 18:09:19 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_var_len(char *var_start)
{
	size_t	len;

	len = 0;
	if (var_start)
	{
		while (*var_start && (ft_isalnum(*var_start) || *var_start == '_'))
		{
			var_start++;
			len++;
		}
	}
	return (len);
}

char	*return_env_var(char *var, char *envp[])
{
	size_t	i;
	size_t var_len
	size_t	spliter_index;

	var_len = ft_var_len(var);
	i = 0;
	if (!var || !envp)
		return (NULL);
	while (envp[i])
	{
		spliter_index = ft_strlen_char(envp[i], '=');
		if (!ft_strncmp(var, envp[i], spliter_index))
		{
			if (spliter_index == var_len)
				return (ft_substr(envp[i], spliter_index + 1, \
					ft_strlen(envp[i]) - spliter_index));
		}
		i++;
	}
	return (NULL);
}

//var_len does not consider the $
char	*convert_var(char *line, int i_dollar, char *var_substitution, int var_len)
{
	char	*replacing_line;
	int		new_len;
	int		i;
	int		j;

	new_len = ft_strlen(line) - ++var_len + ft_strlen(var_substitution) + 1;
	replacing_line = malloc(new_len);
	if (!replacing_line)
		return (NULL);
	i = 0;
	while (i < i_dollar)
	{
		replacing_line[i] = line[i];
		i++;
	}
	j = i + var_len;
	while (var_substitution && *var_substitution)
		replacing_line[i++] = *var_substitution++;
	while (line[j])
		replacing_line[i++] = line[j++];
	replacing_line[i] = '\0';
	return (replacing_line);
}

char	*convert_var_in_line(char *line, char *envp[])
{
	int		i;
	int		is_quoted;
	char	*var_content;
	char	*new_line;
	size_t	var_len;
	
	i = 0;
	ft_is_quoted(NULL, 0);
	while (line && line[i])
	{
		is_quoted = ft_is_quoted(line, i);
		if (line[i] == '$' && (is_quoted == 0 || is_quoted == 2))
		{
			var_len = ft_var_len(&line[i + 1]);
			var_content = return_env_var(&line[i + 1], var_len, envp);
			if (var_content)
			{
				new_line = convert_var(line, i, var_content, var_len);
				free(var_content);
				free(line);
				line = new_line;
			}
		}
		i++;
	}
	return (line);
}
