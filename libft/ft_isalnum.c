/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= (int) 'A' && c <= (int) 'Z') || \
		(c >= (int) 'a' && c <= (int) 'z') || \
		(c >= '0' && c <= '9'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*
//
#include "error_msg.h"
#include <ctype.h>
#include <stdio.h>
// MAIN
int	main(int argc, char *argv[])
{
	int	ii;

	ii = -1;
	while (ii < 257)
	{
		if (isalnum(ii) != ft_isalnum(ii))
		{
			f//printf(stderr, "isalnum(%c) = %d\n", (char)ii, isalnum(ii));
			f//printf(stderr, "ft_isalnum(%c) = %d\n", (char)ii, ft_isalnum(ii));
			return (error_msg(ii, "isalnum"));
		}
		ii++;
	}
	(void)argc;
	f//printf(stderr, "%s have same output from same input\n", argv[0]);
	return (0);
}
*/
