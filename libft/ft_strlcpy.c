/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	while (*src && (dstsize-- - 1))
	{
		*(dst++) = *(src++);
	}
	*dst = '\0';
	return (src_len);
}

//size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen)
//{
//	size_t	src_len;
//
//	src_len = ft_strlen(src);
//	if (src_len + 1 < maxlen)
//	{
//		ft_memcpy(dst, src, src_len + 1);
//	}
//	else if (maxlen != 0)
//	{
//		ft_memcpy(dst, src, maxlen - 1);
//		dst[maxlen - 1] = '\0';
//	}
//	return (src_len);
//}
//
/*
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	while (*src && *dst && (dstsize-- - 1))
	{
		*(dst++) = *(src++);
	}
	*dst = '\0';
	return (src_len);
}
*/
/*
//
#include "error_msg.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
// MAIN
int test_strlcpy(char *to_cpy, int len)
{
	char	*s1;
	char	*s2;
	int		ii = 0;
	int		jj = 0;

	s1 = malloc(sizeof(char) * 20);
	s2 = malloc(sizeof(char) * 20);
	strlcpy(s1, to_cpy, len);
	ft_strlcpy(s2, to_cpy, len);
	return (strncmp(s1, s2, len));
}

int	main(int argc, char *argv[])
{
	int ii = 0;

	while (ii < 5)
	{
		test_strlcpy("abc", ii);
		ii++;
	}
	ii = 0;
	while (ii < 2)
	{
		test_strlcpy("", ii);
		ii++;
	}
	fprintf(stderr, "can be a good job ;)\n");
}
*/
