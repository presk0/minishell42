/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// from nickdotht 
char	*ft_strnstr(const char *str, const char *ndl, size_t len)
{
	size_t		i_str;
	size_t		i_ndl;
	size_t		i_cmp;
	int			found;

	i_str = -1;
	found = 1;
	if (!ft_strlen(ndl))
		return ((char *)str);
	while (*(str + ++i_str) && i_str < len)
	{
		i_ndl = 0;
		if (*(str + i_str) == *(ndl))
		{
			i_cmp = i_str;
			found = 1;
			while (*(str + i_cmp) && *(ndl + i_ndl)
				&& i_ndl < len && i_cmp < len)
				if (*(str + i_cmp++) != *(ndl + i_ndl++))
					found = 0;
			if (found && !*(ndl + i_ndl))
				return ((char *)str + i_str);
		}
	}
	return (NULL);
}

/*
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	len_needle;
	unsigned int	ii;
	unsigned int	jj;

	len_needle = ft_strlen(needle);
	if (!len_needle)
		return ((char *) haystack);
	if (!haystack)
		return (NULL);
	if (len < len_needle)
		return (NULL);
	else
		len -= len_needle - 1;
	ii = 0;
	while (ii < len && haystack[ii])
	{
		jj = 0;
		while (needle[jj] == haystack[ii + jj] && haystack[ii + jj] && jj < len_needle)
			jj++;
		if (jj == len_needle)
			return ((char *) haystack + ii);
		else
			ii++;
	}
	return (NULL);
}
*/

/*
//
#include <stdio.h>
#include <string.h>
// MAIN
int test_strnstr(char *haystack, char *needle, unsigned int len)
{
	char *r1, *r2;
	if ((r1 = ft_strnstr(haystack, needle, len)) !=\
   	(r2 = strnstr(haystack, needle, len)))
	{
		fprintf(stderr, "[BUG] strnstr:\n\
			outputs differents when:\n\
			haystack = [%s]; needle = [%s]; len = %d\n\
			ft_strnstr(haystack, needle, len)	= [%s]\n\
		   	strnstr(haystack, needle, len))		= [%s]\n",\
			haystack, needle, len, r1, r2);
	
		return (1);
	}
	return (0);
}

int main(void)
{
	for (int i = 0; i < 5; i++)
	{
		test_strnstr("", "", i);
		test_strnstr("abc", "", i);
		test_strnstr("", "abc", i);
		test_strnstr("abc", "a", i);
		test_strnstr("abc", "b", i);
		test_strnstr("abc", "c", i);
		test_strnstr("abc", "X", i);
		test_strnstr("zabc", "abc", i);
		test_strnstr("abcz", "abc", i);
	}
		test_strnstr("MZIRIBMZIRIBMZE123", "MZIRIBMZE", 99);
}
*/
