/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:08:18 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_strnlen(char *s, size_t max)
{
	unsigned int	ii;

	ii = 0;
	while (s[ii] && ii < max)
		ii++;
	return (ii);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstr_len;

	dstr_len = ft_strnlen(dst, dstsize);
	if (dstr_len == dstsize)
		return (dstr_len + ft_strlen(src));
	return (dstr_len + ft_strlcpy(dst + dstr_len,
			(char *) src, dstsize - dstr_len));
}
/*
//
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// MAIN
int test_strlcat(char *str, char *to_append, int len)
{
	char	*s1;
	char	*s2;
	int		ret0;
	unsigned int	ret1 = 0;
	unsigned int	ret2 = 0;

	s1 = malloc(sizeof(char) * (strlen(str) + strlen(to_append) + 2));
	s2 = malloc(sizeof(char) * (strlen(str) + strlen(to_append) + 2));
	strcpy(s1, str);
	strcpy(s2, str);
	if ((ret0 = strncmp(s1, s2, len)) || (ret1 = strlcat(s1, to_append, len))\
	!= (ret2 = ft_strlcat(s2, to_append, len)))
	{
		fprintf(stderr, "Error when len = %d, src = [%s], dst = [%s]\n\
			%3d <-- s1 (   strlcat): [%s]\n\
			%3d <-- s2 (ft_strlcat): [%s]\n\n",\
			len, to_append, str, ret1, s1, ret2, s2);
		return (0);
	}
	return (1);
}

int	main(void)
{
	int ii = 0;
	char s_abc[5] = "abc";
	char s_c[] = "c";
	char s_empty[] = "";

	while (ii < 5)
	{
		test_strlcat(s_abc, s_c, ii);
		ii++;
	}
	ii = 0;
	while (ii < 5)
	{
		test_strlcat(s_abc, s_empty, ii);
		ii++;
	}
	ii = 0;
	while (ii < 2)
	{
		test_strlcat(s_abc, s_empty, ii);
		ii++;
	}
}
*/
