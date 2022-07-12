/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	les parametres de f sont imposes arbitrairement : ii et s[ii] */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	ii;
	char			*ret;

	if (s)
	{
		ret = (char *) malloc(sizeof(char) * (ft_strlen((char *) s) + 1));
		if (!ret)
			return (NULL);
		ii = 0;
		while (s[ii] != '\0')
		{
			ret[ii] = (*f)(ii, s[ii]);
			ii++;
		}
		ret[ii] = '\0';
		return (ret);
	}
	return (NULL);
}

/*
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// MAIN
char	f(unsigned int ii, char c)
{
	if (ii % 2)
		return (int) (c);
	else
		return (int) ('-');
}

int	main(void)
{
	char str[] = "abcdef";
	//char (*func)(unsigned int, char);
	fprintf(stderr, "%s\n", ft_strmapi(str, &f));
}
*/
