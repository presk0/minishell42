/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/13 19:36:43 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char		**ft_split_mini(char *s, char c)
{
	char	**mat;
	char	sep[2];

	if (!s)
		return (NULL);
	sep[0] = c;
	sep[1] = '\0';
	mat = ft_split_strsep(s, &c, 1);
	return (mat);
}
*/

/* str free inside the function */
/* doesn't split if in quotes */
/* /!\ add \0 line if is empty before or after *sep */
char	**ft_split_strsep(char *str, char *sep, int is_char)
{
	int			i;
	int			matrix_len;
	int			sep_len;
	char		is_quoted;
	char		*str_split[2];
	char		**matrix_split;

	if(!str)
		return NULL;
	if (is_char)
		sep_len = 1;
	else
		sep_len = ft_strlen(sep);
	ft_is_quoted(NULL, 0);
	matrix_split = NULL;
	matrix_len = 1;
	i = 0;
	while (str[i])
	{
		is_quoted = ft_is_quoted(str, i);
		if (!is_quoted && !ft_strncmp(&str[i], sep, sep_len))
		{
			str_split[0] = ft_substr(str, 0, i);
			str_split[1] = ft_substr(str, i + sep_len, ft_strlen(str));
			if (matrix_split)
			{
				matrix_split = free_matrix_line(matrix_split, matrix_len - 1);
				//free(str);
			}
			matrix_split = ft_append_tab(matrix_split, str_split[0]);
			matrix_split = ft_append_tab(matrix_split, str_split[1]);
			str = matrix_split[matrix_len++];
			i = 0;
		}
		if (i < (int)ft_strlen(str))
			i++;
	}
	return (matrix_split);
}

static void refresh_matrix(char *str, char ***matrix, char *sep, int i, int keep_sep)
{
	char	*str_split[3];
	int		sep_len;

	sep_len = ft_strlen(sep);
	str_split[0] = ft_substr(str, 0, i);
	if (keep_sep)
		str_split[1] = ft_substr(str, i, sep_len);
	str_split[2] = ft_substr(str, i + sep_len, ft_strlen(str));
	*matrix = free_matrix_line(*matrix, ft_matrixlen(*matrix) - 1);
	*matrix = ft_append_tab(*matrix, str_split[0]);
	if (keep_sep)
		*matrix = ft_append_tab(*matrix, str_split[1]);
	*matrix = ft_append_tab(*matrix, str_split[2]);
}

static void	init_vars(int *i, char ***matrix_split, char *str, char ***sep_init, char **sep)
{
	ft_is_quoted(NULL, 0);
	*matrix_split = NULL;
	*matrix_split = ft_append_tab(*matrix_split, ft_strdup(str));
	*i = -1;
	*sep_init = sep;
}

char	**ft_split_multistrsep(char *str, char **sep, int keep_sep)
{
	int			i;
	char		is_quoted;
	char		**matrix_split;
	char		**sep_init;

	init_vars(&i, &matrix_split, str, &sep_init, sep);
	while (str && ++i < (int)ft_strlen(str))
	{
		is_quoted = ft_is_quoted(str, i);
		sep = sep_init;
		while (sep && *sep)
		{
			if (!is_quoted && !ft_strncmp(&str[i], *sep, ft_strlen(*sep)))
			{
				refresh_matrix(str, &matrix_split, *sep, i, keep_sep);
				str = matrix_split[ft_matrixlen(matrix_split) - 1];
				i = -1;
			}
			sep++;
		}
	}
	return (matrix_split);
}
