/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
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
			fprintf(stderr, "tolower(%c) = %d\n", (char)ii, tolower(ii));
			fprintf(stderr, "ft_tolower(%c) = %d\n", (char)ii, ft_tolower(ii));
			return (error_msg(ii, "tolower"));
		}
		ii++;
	}
	fprintf(stderr, "You r da man ;)\n");
	return (0);
}
*/
