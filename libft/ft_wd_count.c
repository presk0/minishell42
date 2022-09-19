/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wd_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:09:34 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wd_count(char *str, char sep)
{
	int		wd_nb;

	wd_nb = 0;
	if (str)
	{
		while (*str == sep)
			str++;
		while (*str)
		{
			str = ft_get_next_wd(str, sep);
			if (str != NULL)
				wd_nb++;
		}
	}
	else
		error_msg("str == NULL in wc str");
	return (wd_nb);
}

/*
#include <stdio.h>
int main()
{
	f//printf(stderr, "%d\n", ft_wd_count(NULL, 0));
	f//printf(stderr, "%d\n", ft_wd_count("a", ' '));
	f//printf(stderr, "%d\n", ft_wd_count(" a", ' '));
	f//printf(stderr, "%d\n", ft_wd_count("a ", ' '));
	f//printf(stderr, "%d\n", ft_wd_count(" a ", ' '));
	f//printf(stderr, "%d\n", ft_wd_count("a a", ' '));
	f//printf(stderr, "%d\n", ft_wd_count("a a ", ' '));
	f//printf(stderr, "%d\n", ft_wd_count(" a a", ' '));
	f//printf(stderr, "%d\n", ft_wd_count(" a a ", ' '));
}
*/
