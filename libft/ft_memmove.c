/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	ii;

	ii = 0;
	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		while (ii < len)
		{
			((char *) dst)[ii] = ((char *) src)[ii];
			ii++;
		}
	}
	else
	{
		while (ii < len)
		{
			((char *) dst)[len - ii - 1] = ((char *) src)[len - ii - 1];
			ii++;
		}
	}
	return (dst);
}

/*
//
#include <string.h>
#include <stdio.h>
int test_memmove(int len)
{
	char	s1[] = "0123456789";
	char	s2[] = "0123456789";
	int		ii = 0;

	memmove(s1 + 3, s1 + 2, len);
	ft_memmove(s2 + 3, s2 + 2, len);
	if (ft_strncmp(s1, s2, 1000))
	{
		fprintf(stderr, "memmove(str) = [%s]\n\
			ft_memmove(str) = [%s]\n\
			len = %d\n\
			", s1, s2, len);
		fprintf(stderr, "\n");
		return (1);
	}
	memmove(s1 + 3, s1 + 2, len);
	ft_memmove(s2 + 3, s2 + 2, len);
	if (ft_strncmp(s1, s2, 1000))
	{
		fprintf(stderr, " memmove(str) = [%s]\n\
			ft_memmove(str) = [%s]\n\
			len = %d\n\
			", s1, s2, len);
		fprintf(stderr, "\n");
		return (1);
	}
	memmove(s1 + 3, s1 + 3, len);
	ft_memmove(s2 + 3, s2 + 3, len);
	if (ft_strncmp(s1, s2, 1000))
	{
		fprintf(stderr, " memmove(str) = [%s]\n\
			ft_memmove(str) = [%s]\n\
			len = %d\n\
			", s1, s2, len);
		fprintf(stderr, "\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int ii = 0;

	while (ii < 5)
	{
		test_memmove(ii);
		ii++;
	}
	ii = 0;
	while (ii < 6)
	{
		test_memmove(ii);
		ii++;
	}
}
*/
