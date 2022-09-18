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
/*
void	print_tab(char **tableau)
{
	int	i;

	i = 0;
	printf("------------------------\n");
	if (tableau)
	{
		while (tableau[i])
		{
			printf("%s*\n", tableau[i++]);
		}
	}
	printf("------------------------\n");
}
*/
