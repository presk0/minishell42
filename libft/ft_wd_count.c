/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wd_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:09:34 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
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
	fprintf(stderr, "%d\n", ft_wd_count(NULL, 0));
	fprintf(stderr, "%d\n", ft_wd_count("a", ' '));
	fprintf(stderr, "%d\n", ft_wd_count(" a", ' '));
	fprintf(stderr, "%d\n", ft_wd_count("a ", ' '));
	fprintf(stderr, "%d\n", ft_wd_count(" a ", ' '));
	fprintf(stderr, "%d\n", ft_wd_count("a a", ' '));
	fprintf(stderr, "%d\n", ft_wd_count("a a ", ' '));
	fprintf(stderr, "%d\n", ft_wd_count(" a a", ' '));
	fprintf(stderr, "%d\n", ft_wd_count(" a a ", ' '));
}
*/
