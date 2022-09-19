/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:29:28 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
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
	f//printf(stderr, "%zu\n", ft_strlen_char(NULL, 0));
	f//printf(stderr, "%zu\n", ft_strlen_char("a", ' '));
	f//printf(stderr, "%zu\n", ft_strlen_char(" a", ' '));
	f//printf(stderr, "%zu\n", ft_strlen_char("a ", ' '));
	f//printf(stderr, "%zu\n", ft_strlen_char(" a ", ' '));
	f//printf(stderr, "%zu\n", ft_strlen_char("a a", ' '));
	f//printf(stderr, "%zu\n", ft_strlen_char("a a ", ' '));
	f//printf(stderr, "%zu\n", ft_strlen_char(" a a", ' '));
	f//printf(stderr, "%zu\n", ft_strlen_char(" a a ", ' '));
}

*/
