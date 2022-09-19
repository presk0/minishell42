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

static void	refresh_matrix_keep_sep(char *str, char ***matrix, char *sep, int i)
{
	char	*str_split[3];
	int		sep_len;

	sep_len = ft_strlen(sep);
	str_split[0] = ft_substr(str, 0, i);
	str_split[1] = ft_substr(str, i, sep_len);
	str_split[2] = ft_substr(str, i + sep_len, ft_strlen(str));
	*matrix = free_matrix_line(*matrix, ft_matrixlen(*matrix) - 1);
	*matrix = ft_append_tab(*matrix, str_split[0]);
	*matrix = ft_append_tab(*matrix, str_split[1]);
	*matrix = ft_append_tab(*matrix, str_split[2]);
}

static void	refresh_matrix_no_sep(char *str, char ***matrix, char *sep, int i)
{
	char	*str_split[3];
	int		sep_len;

	sep_len = ft_strlen(sep);
	str_split[0] = ft_substr(str, 0, i);
	str_split[2] = ft_substr(str, i + sep_len, ft_strlen(str));
	*matrix = free_matrix_line(*matrix, ft_matrixlen(*matrix) - 1);
	*matrix = ft_append_tab(*matrix, str_split[0]);
	*matrix = ft_append_tab(*matrix, str_split[2]);
}

static char	**init_vars(int *i, char ***matrix_split, char *str, \
	char **sep)
{
	ft_is_quoted(NULL, 0);
	*matrix_split = NULL;
	*matrix_split = ft_append_tab(*matrix_split, ft_strdup(str));
	*i = -1;
	return (sep);
}

static char	**init_loop(int *is_quoted, char **str, int *i, char **sep_init)
{
	*is_quoted = ft_is_quoted(*str, *i);
	return (sep_init);
}

char	**ft_split_multistrsep(char *str, char **sep, int keep_sep)
{
	int			i;
	int			is_quoted;
	char		**matrix_split;
	char		**sep_init;

	sep_init = init_vars(&i, &matrix_split, str, sep);
	while (str && ++i < (int)ft_strlen(str))
	{
		sep = init_loop(&is_quoted, &str, &i, sep_init);
		while (sep && *sep)
		{
			if (!is_quoted && !ft_strncmp(&str[i], *sep, ft_strlen(*sep)))
			{
				if (keep_sep)
					refresh_matrix_keep_sep(str, &matrix_split, *sep, i);
				else
					refresh_matrix_no_sep(str, &matrix_split, *sep, i);
				bloody_normi(&str, &matrix_split, &i);
			}
			sep++;
		}
	}
	return (matrix_split);
}
