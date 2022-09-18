#include "minishell.h"

int	quote_empty(char *first_quote)
{
	if (first_quote)
	{
		if (first_quote[0] == first_quote[1])
			return (1);
		else if (first_quote[0] && first_quote[1])
			return (0);
	}
	return (-1);
}

/* spaces num if not quoted */
int	line_presplit(char *cmd)
{
	int	quote;
	int	i;
	int	tab_len;
	int	last_quote;

	ft_is_quoted(NULL, 0);
	last_quote = 0;
	quote = 0;
	i = 0;
	tab_len = 1;
	while (cmd[i])
	{
		quote = ft_is_quoted(cmd, i);
		if (quote != last_quote)
		{
			cmd[i] = '\0';
			tab_len++;
			last_quote = quote;
		}
		if (cmd[i] == ' ' && !quote && tab_len++)
			cmd[i] = '\0';
		i++;
	}
	return (tab_len);
}

char	**quotes_spaces_split(char *line)
{
	int		i;
	int		nb_split;
	int		next;
	char	**matrix;

	nb_split = line_presplit(line);
	matrix = malloc(sizeof(char *) * (nb_split + 1));
	i = 0;
	next = 0;
	while (i < nb_split)
	{
		matrix[i] = ft_strdup(&line[next]);
		next += ft_strlen(&line[next]) + 1;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

int	rm_null_lines(char ***cmd_split)
{
	int	new_i;
	int	i;

	new_i = 0;
	i = 0;
	while ((*cmd_split)[i])
	{
		if (*(*cmd_split)[i] != '\0')
		{
			if (i != new_i)
				(*cmd_split)[new_i] = (*cmd_split)[i];
			new_i++;
		}
		else
			free((*cmd_split)[i]);
		i++;
	}
	return (new_i);
}

