/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len_s1;
	unsigned int	ii;
	char			*ret;

	if (!s1)
		return (NULL);
	ii = 0;
	len_s1 = ft_strlen((char *) s1);
	ret = (char *) malloc(sizeof(char) * (ft_strlen((char *) s2) + len_s1 + 1));
	if (!ret)
		return (NULL);
	ii = 0;
	while (ii < len_s1)
	{
		ret[ii] = s1[ii];
		ii++;
	}
	while (s2[ii - len_s1])
	{
		ret[ii] = s2[ii - len_s1];
		ii++;
	}
	ret[ii] = '\0';
	return (ret);
}

/*
//
#include <stdio.h>
#include <string.h>
#include "libft.h"
// MAIN
int main(void)
{
	char s1[1000];
	char s2[1000];
	char *verif;

	strcpy(s1, "ch1 ");
	strcpy(s2, "ch2");
	verif = ft_strjoin(s1, s2);
	if (ft_strncmp(verif, "ch1 et ch2", 20))
	{
		f//printf(stderr, "Pb at ft_strjoin\n");
	}
	free(verif);
}
*/
