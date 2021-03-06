#include "minishell.h"

char		**copy_args(t_data *param)
{
	int		i;
	char	**args;

	i = 0;
	while (param->argv[i] && ft_memcmp(param->argv[i], "<", 2))
		i++;
	args = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (param->argv[i] && ft_memcmp(param->argv[i], "<", 2))
	{
		args[i] = ft_strdup(param->argv[i]);
		i++;
	}
	return (args);
}

static int	ft_strlen_arg(char *str)
{
	int i;

	i = 0;
	if (str[i] == '<' || str[i] == '>' || str[i] == '=' || str[i] == '|')
		i = ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<') || (str[i] == '|' && str[i + 1] == '|')) ? 2 : 1;
	else
	{
		while (str[i] && !ft_isspace(str[i]) && str[i] != '<' &&
		str[i] != '>' && str[i] != '=' && str[i] != '|')
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				i++;
				i += ft_strlen_arg_token(str + i, str[i - 1]);
				if (!(str[i]))
					return (i);
			}
			i++;
		}
		if (str[i] == '=')
			i++;
	}
	return (i);
}

/* param argc (unserquotes are one word) */
int			count_args(char *str)
{
	int		n;

	n = 0;
	skip_spaces(&str);
	while (*str)
	{
		skip_spaces(&str);
		n++;
		str += ft_strlen_arg(str);
		skip_spaces(&str);
	}
	return (n);
}

void		set_args(char **argv, char *str, int argc)
{
	int		i;
	int		len;

	i = 0;
	skip_spaces(&str);
	while (i < argc)
	{
		skip_spaces(&str);
		len = ft_strlen_arg(str);
		argv[i] = ft_strldup(str, len);
		rm_token(&(argv[i]));
		i++;
		str += len;
		skip_spaces(&str);
	}
}
