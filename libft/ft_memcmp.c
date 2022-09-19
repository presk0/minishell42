/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* comparaison en unsigned char ? */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	ii;

	ii = 0;
	while (ii < n)
	{
		if (*((unsigned char *) s1 + ii) == *((unsigned char *) s2 + ii))
		{
			ii++;
		}
		else
			return (*((unsigned char *) s1 + ii)
				- *((unsigned char *) s2 + ii));
	}
	return (0);
}
