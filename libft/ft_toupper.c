/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= (int) 'a' && c <= (int) 'z')
		return (c - 32);
	else
		return (c);
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
		if (toupper(ii) != ft_toupper(ii))
		{
			f//printf(stderr, "toupper(%c) = %d\n", (char)ii, toupper(ii));
			f//printf(stderr, "ft_toupper(%c) = %d\n", (char)ii, ft_toupper(ii));
			return (error_msg(ii, "toupper"));
		}
		ii++;
	}
	f//printf(stderr, "You r da man ;)\n");
	return (0);
}
*/
