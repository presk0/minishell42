/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/31 13:24:21 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_bonus(char *str, int i)
{
	if (str[i] == ';' || \
		(!ft_strncmp(&str[i], "||", 2) || !ft_strncmp(&str[i], "&&", 2)))
		return (1);
	else
		return (0);
}

int	check_error(t_data *param)
{
	int	i;
	int	is_quoted;

	ft_is_quoted(NULL, 0);
	i = 0;
	while (param->input[i] != '\0')
	{
		is_quoted = ft_is_quoted(param->input, i);
		if (!is_quoted && is_bonus(param->input, i))
		{
			param->retour = 2;
			free(param->input);
			param->input = NULL;
			write(2, "Aux chiottes les bonus\n", 23);
			return (1);
		}	
		i++;
	}
	return (0);
}

/* keep prompting if line not finished */
static int	line_not_finished(char *line)
{
	int		squote;
	int		dquote;
	int		i;

	squote = 0;
	dquote = 0;
	i = 0;
	while (line && line[i])
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
	if (!line)
		return (0);
	quote_type = line_not_finished(line);
	while (quote_type)
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
		quote_type = line_not_finished(line);
	}
	return (line);
}

int	get_input(t_data *param)
{
	char	*input;
	int		ret;

	ret = 1;
	input = read_multilines("42mminishell $ ");
	param->input = input;
	if (param->input == NULL)
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	return (ret);
}
