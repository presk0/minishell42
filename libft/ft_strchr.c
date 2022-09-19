/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != (char)c)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}

/*
char	*ft_strchr(const char *s0, int c)
{
	unsigned int	ii;
	char			*s;

	if (s0)
	{
		s = (char *)s0;
		ii = 0;
		while (s[ii] != '\0')
		{
			if (s[ii] == c)
			{
				return ((char *)(s + ii));
			}
			ii++;
		}
		if (c == '\0')
			return (s + ii);
		else
			return (NULL);
	}
	return (NULL);
}
*/

/*
//
#include "error_msg.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
// MAIN
int test_strchr(char *str, char c)
{
	unsigned int ret;
	}

	ret = strchr(str, c) - ft_strchr(str, c);
	if (ret)
	{
		f//printf(stderr, "[bug] at str: %s, c: %c\n", str, c);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int ii = 0;
	test_strchr("abc", 'b');
	test_strchr("abc", '\0');
	test_strchr("", 'a');
	test_strchr("", '\0');
	f//printf(stderr, "test finished\n");
}
*/
