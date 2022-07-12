#include "minishell.h"


int	check_semicolon(t_data *param)
{
	if (!param->str || !ft_memcmp(param->str, ";", 2))
	{
		if (param->str)
		{
			ft_putstr_fd("minishell; syntax error near unexpected token `;'\n", 2);
			param->retour = 2;
		}
		free(param->str);
		param->str = 0;
		return (1);
	}
	return (0);
}

void		rm_char(char **str, int j)
{
	char *before;
	char *after;

	before = ft_strldup(*str, j);
	after = ft_strdup(*str + j + 1);
	free(*str);
	*str = ft_strjoin(before, after);
	free(after);
	free(before);
}

static void	rm_backslash(char **arg, int *i)
{
	while ((*arg)[*i])
	{
		if ((*arg)[*i] == '\\' && is_token((*arg)[*i + 1]))
			rm_char(arg, *i);
		else if ((*arg)[*i] == '"')
			break ;
		(*i)++;
	}
}

void		rm_token(char **arg)
{
	int		i;

	i = 0;
	while ((*arg)[i])
	{
		if ((*arg)[i] == '\'')
		{
			rm_char(arg, i);
			i += ft_strlen_char(*arg + i, '\'');
			rm_char(arg, i);
		}
		else if ((*arg)[i] == '"')
		{
			rm_char(arg, i);
			rm_backslash(arg, &i);
			rm_char(arg, i);
		}
		else if (((*arg)[i] == '\\') &&
		(is_token((*arg)[i + 1]) || (*arg)[i + 1] == '\''))
			rm_char(arg, i++);
		else
			i++;
	}
}

void	skip_spaces(char **str)
{
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
}

int		ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int		is_token(char c)
{
	if (c == '"' || c == '\\')
		return (1);
	return (0);
}
