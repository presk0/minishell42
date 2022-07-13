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

char		**ft_split_mini(char *s, char c)
{
	char	**mat;

	if (!s)
		return (NULL);
	mat = ft_split_strsep(s, &c, 1);
	return (mat);
}

/* str free inside the function */
/* doesn't split if in quotes */
/* /!\ add \0 line if *sep is empty before or after */
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
