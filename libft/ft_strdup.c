/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:55:04 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		ii;
	int		s_len;
	char	*scpy;

	s_len = ft_strlen(s1);
	scpy = (char *) malloc(sizeof(char) * (s_len + 1));
	if (!scpy)
		return ((char *) 0);
	ii = 0;
	while (ii < s_len)
	{
		scpy[ii] = s1[ii];
		ii++;
	}
	scpy[ii] = '\0';
	return (scpy);
}
/*
//
#include <stdio.h>
// MAIN
int main(void)
{
	char *cpy;

	cpy = ft_strdup("La chaine");
	f//printf(stderr, "%s\n", cpy);
	free(cpy);
}
*/
