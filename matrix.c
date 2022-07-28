/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/28 12:40:44 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	//if (!new_tab)
	//	return (NULL);
	new_tab[tab_len--] = NULL;
	new_tab[tab_len] = str;
	while (tab_len--)
		new_tab[tab_len] = matrix[tab_len];
	free(matrix);
	matrix = NULL;
	return (new_tab);
}

int	ft_matrixlen(char **matrix)
{
	int	len;

	len = 0;
	if (matrix)
	{
		while (matrix[len])
			len++;
	}
	return (len);
}

char	**free_matrix_line(char **matrix, int line_nb)
{
	int		matrix_len;
	int		i;
	char	**new_matrix;

	matrix_len = 0;
	if (!matrix)
		return (NULL);
	matrix_len = ft_matrixlen(matrix);
	if (matrix_len < line_nb)
		return(matrix);
	new_matrix = malloc(sizeof(char *) * matrix_len);
	i = -1;
	while (++i < line_nb)
		new_matrix[i] = matrix[i];
	free(matrix[i]);
	matrix[i] = NULL;
	while (i < matrix_len - 1)
	{
		new_matrix[i] = matrix[i + 1];
		i++;
	}
	new_matrix[i] = NULL;
	free(matrix);
	matrix = NULL;
	return (new_matrix);
}

void	print_tab(char **tableau)
{
	int	i;

	i = 0;
	fprintf(stderr, "------------------------\n");
	if (tableau)
	{
		while (tableau[i])
		{
			fprintf(stderr, "%s*\n", tableau[i++]);
		}
	}
	fprintf(stderr, "------------------------\n");
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
/*
char	**ft_insert_line(char **main_matrix, char *insert_matrix, int line_nb)
{
	int		main_mat_len;
	char	new_matrix;

	main_mat_len = ft_matrixlen(main_matrix);
	if (line_nb > main_mat_len)
		line_nb == main_mat_len;
	else
	{

	}

}
*/