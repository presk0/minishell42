/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		else
		{
			s1++;
			s2++;
			n--;
		}
	}
	return (0);
}

/*
//
#include <string.h>
#include <stdio.h>
// MAIN
int test_strncmp(char *s1, char *s2, int len)
{
	if (ft_strncmp(s1, s2, len) == strncmp(s1, s2, len))
		return (1);
	else
	{
		fprintf(stderr, "[BUG]\ns1 = [%s], \ns2 [%s]\nstrncmp = %d\nft_strncmp = %d\n\
		len = %d\n\n", s1, s2, strncmp(s1, s2, len), ft_strncmp(s1, s2, len), len);
		return (0);
	}
}

int	main()
{
	int ii = 0;
	char s1[100];
	char s2[100];

	while (ii < 5)
	{
		strcpy(s1, "a");
		strcpy(s2, "a");
		test_strncmp(s1, s2, ii);

		strcpy(s1, "a");
		strcpy(s2, "");
		test_strncmp(s1, s2, ii);

		strcpy(s1, "");
		strcpy(s2, "a");
		test_strncmp(s1, s2, ii);

		strcpy(s1, "a");
		strcpy(s2, "ab");
		test_strncmp(s1, s2, ii);

		strcpy(s1, "ab");
		strcpy(s2, "az");
		test_strncmp(s1, s2, ii);

		strcpy(s1, "bc");
		strcpy(s2, "ac");
		test_strncmp(s1, s2, ii);

		strcpy(s1, "abcfghdfgh");
		strcpy(s2, "abcfgz");
		test_strncmp(s1, s2, ii);
		ii++;
	}
}
*/
