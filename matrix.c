/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/31 14:46:18 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_f_matrix(char **f_matrix)
{
	int	i;

	i = 1;
	if (f_matrix)
	{
		while (f_matrix[i])
		{
			if (!strncmp(f_matrix[i], "", 2))
			{
				write(2, "syntax error near unexpected token `newline'\n", 45);
				return (0);
			}
			if (!f_matrix[++i])
				return (1);
			i++;
		}
	}
	return (1);
}

int	set_f_matrix(t_data *param, int i)
{
	char	**sep;

	sep = ft_split(">>,>,<<,<", ',');
	param->f_matrix = pop_names_from_sep(param, i, sep);
	if (!check_f_matrix(param->f_matrix))
	{
		ft_free_split(&sep);
		return (-1);
	}
	else
	{
		ft_free_split(&sep);
		return (1);
	}
}

char	**ft_append_tab(char **matrix, char *str)
{
	int		tab_len;
	char	**new_tab;

	if (!str)
		return (matrix);
	tab_len = 0;
	if (matrix)
		while (matrix[tab_len])
			tab_len++;
	new_tab = malloc((tab_len++ + 2) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	new_tab[tab_len--] = NULL;
	new_tab[tab_len] = str;
	while (tab_len--)
		new_tab[tab_len] = matrix[tab_len];
	free(matrix);
	matrix = NULL;
	return (new_tab);
}

char	*matrix_to_str(char **matrix)
{
	int		i;
	char	*str;
	char	*new_str;
	char	*str_add_space;

	str = NULL;
	if (matrix)
		str = ft_strdup(matrix[0]);
	i = 1;
	while (matrix[i] != NULL)
	{
		if (matrix[i][0] != '\0')
		{
			str_add_space = ft_strjoin(str, " ");
			new_str = ft_strjoin(str_add_space, matrix[i]);
			if (str)
				free(str);
			if (str_add_space)
				free(str_add_space);
			str_add_space = NULL;
			str = new_str;
		}
		i++;
	}
	return (str);
}
