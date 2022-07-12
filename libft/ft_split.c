/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:31:55 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**make_tab(char **ret, char const *s, char c, unsigned int nb_wd)
{
	size_t	i_wd;
	size_t	wd_len;

	i_wd = 0;
	while (i_wd < nb_wd)
	{
		while (*s == c)
			s++;
		wd_len = ft_strlen_char((char *)s, c);
		if (wd_len != 0)
		{
			ret[i_wd] = (char *) malloc(sizeof(char) * (wd_len + 1));
			if (!ret[i_wd])
				return (NULL);
		}
		ft_strlcpy(ret[i_wd], s, wd_len + 1);
		ret[i_wd][wd_len] = '\0';
		s += wd_len;
		i_wd++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char			**ret;
	unsigned int	nb_wd;

	if (!s)
		return (NULL);
	nb_wd = ft_wd_count((char *) s, c);
	ret = (char **) malloc((nb_wd + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret = make_tab(ret, s, c, nb_wd);
	ret[nb_wd] = NULL;
	return (ret);
}

/*
//
#include <string.h>
#include <stdio.h>
// MAIN

void put_header(void)
{
	fprintf(stderr, "****************************************************\n");
}

int main(void)
{
	char	**sortie;
	int		ii;

	put_header();
	sortie = ft_split("Phrase de      test", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 fprintf(stderr, "%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split("P", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 fprintf(stderr, "%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split("", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 fprintf(stderr, "%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split(" a ", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 fprintf(stderr, "%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split(" a", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 fprintf(stderr, "%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split("a ", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 fprintf(stderr, "%s\n", sortie[ii++]); 

	put_header();
	ii = 0;
	while (sortie[ii] != NULL)
		 fprintf(stderr, "%s\n", sortie[ii++]); 
		 fprintf(stderr, "+++++++++"); 
}
	char s[10];
	strcpy(s, "");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "  ");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "a");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "a ");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, " a");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, " a ");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "  aa  ");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "bb   bb");
	fprintf(stderr, "for [%s] -> %d\n", s, _count(s, ' '));
}
*/
