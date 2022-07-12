/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:29:43 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_tree	*new_node(char *data, t_cmd_tree *parent)
{
	t_cmd_tree	*node;

	node = (t_cmd_tree *)malloc(sizeof(t_cmd_tree));
	if (!node)
	{
		if (data)
			free(data);
		return (NULL);
	}
	node->data = data;
	node->right = NULL;
	node->fds[0] = -1;
	node->fds[1] = -1;
	node->oparend = parent;
	node->ignore_node = 0;
	node->pid = 1;
	node->left = NULL;
	if (parent)
		node->envp = parent->envp;
	return (node);
}

void	free_node(t_cmd_tree *node)
{
	if (node)
	{
		if (node->data)
			free(node->data);
		free(node);
	}
}

// || doesnt 
void	node_exe(t_cmd_tree *node)
{
	if (!node || node->ignore_node)
		return ;
//	else if (!ft_strncmp(node->data, "&&", 3))
//	{
//		if (node->fds_err[0] != 0)
//			node->right->ignore_node = 1;
//	}
//	else if (!ft_strncmp(node->data, ">", 2)
//		node_redir_out(node);
//	else if (!ft_strncmp(node->data, ">>", 3)
//		node_redir_append(node);
//	else if (!ft_strncmp(node->data, "<", 3)
//		node_redir_in(node);
//	else if (!ft_strncmp(node->data, "<<", 3)
//		node_redir_heredoc(node);
	else
		node_cmd(node);
}