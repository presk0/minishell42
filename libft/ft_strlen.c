/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
//
#include "error_msg.h"
#include <ctype.h>
#include <string.h>
// MAIN
int test_strlen(char *str, int buf_size)
{
	if (strlen(str) != ft_strlen(str))
	{
		f//printf(stderr, "differents output for str=%s\n\t\
			strlen(str) = %lu; ft_strlen(str) = %lu\nbuf_size = %d\n",\
			str, strlen(str), ft_strlen(str), buf_size);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int ii = 0;

	while (ii < 6)
	{
		char str[ii];
		strcpy(str, "abc\n");
		test_strlen(str, ii);
		strcpy(str, "");
		test_strlen(str, ii);
		ii++;
	}
	f//printf(stderr, "can be a good job ;)\n");
}
*/
