/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/19 14:30:54 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	norminette_sucks(char **str, int *i, char ***matrix_split, \
	int sep_len, int *matrix_len)
{
	char	*str_split[2];

	str_split[0] = ft_substr(*str, 0, *i);
	str_split[1] = ft_substr(*str, *i + sep_len, ft_strlen(*str));
	if (*matrix_split)
		*matrix_split = free_matrix_line(*matrix_split, *matrix_len - 1);
	*matrix_split = ft_append_tab(*matrix_split, str_split[0]);
	*matrix_split = ft_append_tab(*matrix_split, str_split[1]);
	*str = (*matrix_split)[(*matrix_len)++];
	*i = 0;
}

static void	init_vars_split_strsep(int is_char, char *sep, int *sep_len, \
	char ***matrix_split, int *matrix_len)
{
	if (is_char)
		*sep_len = 1;
	else
		*sep_len = ft_strlen(sep);
	ft_is_quoted(NULL, 0);
	*matrix_split = NULL;
	*matrix_len = 1;
}

/* str free inside the function */
/* doesn't split if in quotes */
/* /!\ add \0 line if is empty before or after *sep */
char	**ft_split_strsep(char *str, char *sep, int is_char)
{
	int			i;
	int			matrix_len;
	int			sep_len;
	char		**matrix_split;
	char		is_quoted;

	if (!str)
		return (NULL);
	init_vars_split_strsep(is_char, sep, &sep_len, &matrix_split, &matrix_len);
	i = 0;
	while (str[i])
	{
		is_quoted = ft_is_quoted(str, i);
		if (!is_quoted && !ft_strncmp(&str[i], sep, sep_len))
			norminette_sucks(&str, &i, &matrix_split, sep_len, &matrix_len);
		if (i < (int)ft_strlen(str))
			i++;
	}
	return (matrix_split);
}
