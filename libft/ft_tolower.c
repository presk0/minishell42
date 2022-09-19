/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= (int) 'A' && c <= (int) 'Z')
	{
		return (c + 32);
	}
	else
	{
		return (c);
	}
}
/*
//
#include "error_msg.h"
#include <ctype.h>
#include <stdio.h>
// MAIN
int	main(void)
{
	int	ii;

	ii = -1;
	while (ii < 257)
	{
		if (tolower(ii) != ft_tolower(ii))
		{
			f//printf(stderr, "tolower(%c) = %d\n", (char)ii, tolower(ii));
			f//printf(stderr, "ft_tolower(%c) = %d\n", (char)ii, ft_tolower(ii));
			return (error_msg(ii, "tolower"));
		}
		ii++;
	}
	f//printf(stderr, "You r da man ;)\n");
	return (0);
}
*/
