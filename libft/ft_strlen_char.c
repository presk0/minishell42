/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:29:28 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_char(char *str, char sep)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (*str && *str++ != sep)
			len++;
	}
	return (len);
}

/*
#include <stdio.h>
int main()
{
	fprintf(stderr, "%zu\n", ft_strlen_char(NULL, 0));
	fprintf(stderr, "%zu\n", ft_strlen_char("a", ' '));
	fprintf(stderr, "%zu\n", ft_strlen_char(" a", ' '));
	fprintf(stderr, "%zu\n", ft_strlen_char("a ", ' '));
	fprintf(stderr, "%zu\n", ft_strlen_char(" a ", ' '));
	fprintf(stderr, "%zu\n", ft_strlen_char("a a", ' '));
	fprintf(stderr, "%zu\n", ft_strlen_char("a a ", ' '));
	fprintf(stderr, "%zu\n", ft_strlen_char(" a a", ' '));
	fprintf(stderr, "%zu\n", ft_strlen_char(" a a ", ' '));
}

*/
