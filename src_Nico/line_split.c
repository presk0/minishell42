/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/12 16:39:10 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cat > test < exit.c < tags > test2		works
	cat > test < exit.c < tags				works
	Meaning however redirections, considering inputs and outputs however the orders
	(inside higher priority operands)

	=> ecriture polonaise
*/

int	ft_is_operand(char *data)
{
	char	**ope_len_2;
	char	**ope_len_1;
	int		i;

	ope_len_2 = ft_split("&& || >> <<", ' ');
	ope_len_1 = ft_split("| > <", ' ');
	i = 0;
	if (ft_strlen(data) == 2)
	{
		while (ope_len_2[i])
		{
			if (!ft_strncmp(data, ope_len_2[i], 2))
				return (1);
			i++;
		}
	}
	i = 0;
	if (ft_strlen(data) == 1)
	{
		while (ope_len_1[i])
		{
			if (!ft_strncmp(data, ope_len_1[i], 1))
				return (1);
			i++;
		}
	}
	return (0);
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

t_cmd_tree	*line_to_tree(char *cmd_line, char **envp[])
{
	t_cmd_tree	*root;
	char		**sep;

	sep = ft_split("&& ||", ' ');
	root = new_node(cmd_line, NULL);
	root->envp = envp;
	tree_parse_split(&root, sep, &node_split_multisep);
	free(sep);
	sep = ft_split("|", ' ');
	tree_parse_split(&root, sep, &node_split_multisep);
	free(sep);
	sep = ft_split(">> >", ' ');
	tree_parse_split(&root, sep, &node_split_multisep);
	free(sep);
	sep = ft_split("<< <", ' ');
	tree_parse_split(&root, sep, &node_split_multisep);
	free(sep);
	tree_parse_split(&root, *envp, &convert_var_in_node);
	return (root);
}
