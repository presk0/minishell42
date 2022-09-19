/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_split_multisep.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:20:23 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 08:21:07 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	refresh_matrix(char *str, char ***matrix, char *sep, int i, \
	int keep_sep)
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

static void	init_vars(int *i, char ***matrix_split, char *str, \
	char ***sep_init, char **sep)
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
	int			is_quoted;
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
