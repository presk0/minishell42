/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/09/19 08:24:50 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

void	del_first_word(char **str)
{
	int		i;
	char	*new_str;
	int		is_quoted;

	new_str = NULL;
	i = 0;
	ft_is_quoted(NULL, 0);
	if (str && (*str))
	{
		while (is_blank((*str)[i]) && (*str)[i])
			i++;
		is_quoted = ft_is_quoted((*str), i);
		while ((!is_blank((*str)[i]) || is_quoted) && (*str)[i])
		{
			i++;
			is_quoted = ft_is_quoted((*str), i);
		}
		while (is_blank((*str)[i]) && (*str)[i])
			i++;
		new_str = ft_substr((*str), i, ft_strlen(*str));
	}
	free(*str);
	*str = new_str;
}

char	*return_first_word(char *str)
{
	int		start;
	int		end;
	char	*new_str;
	int		is_quoted;

	new_str = NULL;
	start = 0;
	if (str)
	{
		while (str[start] && is_blank(str[start]))
			start++;
		end = start;
		is_quoted = ft_is_quoted(str, end);
		while ((!is_blank(str[end]) || is_quoted) && str[end])
		{
			end++;
			is_quoted = ft_is_quoted(str, end);
		}
		new_str = ft_substr(str, start, end - start);
	}
	return (new_str);
}

char	*pop_first_wd(char **cmd)
{
	char	*first_word;

	first_word = NULL;
	if (cmd)
	{
		first_word = return_first_word(*cmd);
		del_first_word(cmd);
	}
	return (first_word);
}

int	is_available_var_name(char *var, int i)
{
	int	j;

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
