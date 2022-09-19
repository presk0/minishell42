/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:21:52 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 08:22:00 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (matrix);
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
