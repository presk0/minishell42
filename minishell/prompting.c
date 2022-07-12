/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/06/25 21:59:03 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_escaped(char *str, int i)
{
	if (str)
	{
		if (!i || str[i - 1] != '\\')
			return (1);
		else
			return (0);
	}
	return (0);
}

/* keep prompting if line not finished */
int	line_not_finished(char *line)
{
	int		squote;
	int		dquote;
	int		i;

	squote = 0;
	dquote = 0;
	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\'' && not_escaped(line, i) && !dquote)
			squote = !squote;
		if (line[i] == '\"' && not_escaped(line, i) && !squote)
			dquote = !dquote;
		i++;
	}
	if (dquote)
		return (2);
	if (squote)
		return (1);
    return (0);
}

char	*read_multilines(char *prompt)
{
	char	*line;
	char	*line_cpy;
	char	*tmp;
	int		quote_type;

	line = readline(prompt);
	while ((quote_type = line_not_finished(line)))
	{
		if (quote_type == 1)
			prompt = "quote> ";
		else
			prompt = "dquote> ";
		line_cpy = line;
		tmp = readline(prompt);
		line = ft_strjoin(line, tmp);
		free(line_cpy);
		free(tmp);
	}
	return (line);
}
