/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned int	ii;

	ii = 0;
	while (ii < n)
	{
		*((char *) s + ii) = '\0';
		ii++;
	}
	return (s);
}

/*
//
#include "error_msg.h"
#include <ctype.h>
#include <string.h>
// MAIN
int test_bzero(char *str, int c, int len, int buf_size)
{
	char	s1[1000];
	char	s2[1000];
	int		ii = 0;

	strcpy(s1, str);
	strcpy(s2, str);
	bzero(s1, len);
	ft_bzero(s2, len);
	while (ii < len)
	{
		if (s1[ii] != s2[ii])
		{
			fprintf(stderr, "differents output for str=[%s]\nbzero(str) = [%s]\n\
			ft_bzero(str) = [%s]\nlen/str_bufsize = %d\nbuf_size = %d\n"\
			, str, s1, s2, len, buf_size);
			fprintf(stderr, "\n");
			fprintf(stderr, "\n");
			return (1);
		}
		ii++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int ii = 0;
	int jj = 0;
	char c = 'a';

	while (ii < 6)
	{
		char str[ii];
		strcpy(str, "abc\n");
		jj = 0;
		while (jj < ii)
		{
			test_bzero(str, c, jj, ii);
			jj++;
		}
		strcpy(str, "");
		jj = 0;
		while (jj < ii)
		{
			test_bzero(str, c, jj, ii);
			jj++;
		}
		ii++;
	}
	fprintf(stderr, "can be a good job ;)\n");
}
*/
