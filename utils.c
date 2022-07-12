/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/12 20:40:33 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_append_tab(char **tableau, char *str)
{
	int		tab_len;
	char	**new_tab;

	if (!str)
		return (tableau);
	tab_len = 0;
	if (tableau)
		while (tableau[tab_len])
			tab_len++;
	new_tab = malloc((tab_len++ + 2) * sizeof(char *));
	//if (!new_tab)
	//	return (NULL);
	new_tab[tab_len--] = NULL;
	new_tab[tab_len] = str;
	while (tab_len--)
		new_tab[tab_len] = tableau[tab_len];
	free(tableau);
	tableau = NULL;
	return (new_tab);
}

int	ft_is_quoted(char *c, int i)
{
	static int	squote;
	static int	dquote;

	if (!c)
	{
		squote = 0;
		dquote = 0;
	}
	else
	{
		if (c[i] == '\'' && !dquote) // not_escaped(c, i) && 
			squote = !squote;
		else if (c[i] == '\"' && !squote) // not_escaped(c, i) && 
			dquote = !dquote;
		if (dquote)
			return (2);
		if (squote)
			return (1);
	}
	return (0);
}
