/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/12 19:17:10 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* keep prompting if line not finished */
static int	line_not_finished(char *line)
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
		if (line[i] == '\'' && !dquote)
			squote = !squote;
		if (line[i] == '\"' && !squote)
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
