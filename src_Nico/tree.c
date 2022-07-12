/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/11 16:27:24 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_cmd_tree *root, int level)
{
	if (root == NULL)
		return;
	for (int i = 0; i < level; i++)
		i == level - 1 ? printf("|-") : printf("  ");
	printf("%s\n", root->data);
	print_tree(root->left, level + 1);
	print_tree(root->right, level + 1);
}

void	node_split_multisep(t_cmd_tree **root, char **sep)
{
	int			i;
	int			j;
	int			cmd_len;
	char		*cmd_line;
	char		is_quoted;

	if(!root || !(*root))
		return ;
	cmd_line = (*root)->data;
	cmd_len = ft_strlen(cmd_line);
	i = 0;
	while (cmd_line && cmd_line[i])
	{
		j = 0;
		is_quoted = ft_is_quoted(cmd_line, i);
		while (sep[j])
		{
			if (!is_quoted && !ft_strncmp(&cmd_line[i], sep[j], ft_strlen(sep[j])))
			{
				(*root)->data = ft_substr(sep[j], 0, ft_strlen(sep[j]));
//				//reverse branches for a input, to facilitate priority execution
//				if (!ft_strncmp("<<", sep[j], ft_strlen(sep[j])))
//				{
//					(*root)->right = new_node(ft_substr(cmd_line, 0, i), (*root));
//					(*root)->left = new_node(ft_substr(cmd_line, i + ft_strlen(sep[j]), cmd_len), (*root));
//				}
//				else
//				{
					(*root)->left = new_node(ft_substr(cmd_line, 0, i), (*root));
					(*root)->right = new_node(ft_substr(cmd_line, i + ft_strlen(sep[j]), cmd_len), (*root));
//				}
				free(cmd_line);
				cmd_line = NULL;
				break;
			}
			j++;
		}
		//if ((*root)->right)
		//	break ;
		i++;
	}
	//if ((*root)->right)
	//	node_split_multisep(&(*root)->right, sep);
}

// f = node_split multisep
void	tree_parse_split(t_cmd_tree **node, char **sep, void (*f)(t_cmd_tree **, char **))
{
	if (!ft_is_operand((*node)->data))
		(*f)(node, sep);
	if ((*node)->left)
		tree_parse_split(&(*node)->left, sep, f);
	if ((*node)->right)
		tree_parse_split(&(*node)->right, sep, f);
}

void	tree_parsing(t_cmd_tree *node)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		perror(NULL);
	else if (pid == 0)
	{
		rec_tree_parsing(node);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}	
}

void	rec_tree_parsing(t_cmd_tree *node)
{
	int	piped;

	//fprintf(stderr, "[tree_parsind] %s\n", node->data);
	piped = 0;
	if (!node)
		return ;
	else if (!ft_strncmp(node->data, "|", 2))
	{
		node_pipex(node);
		piped++;
	}
	if (node->left && (!piped || node->pid == 0))
		rec_tree_parsing(node->left);
	if (node->right && (node->pid || (!node->pid && !piped)))
		rec_tree_parsing(node->right);
	if (!ft_is_operand(node->data))
		node_exe(node);
}

void	free_tree(t_cmd_tree *node)
{
	if (node)
	{
		if (node->left)
			free_tree(node->left);
		if (node->right)
			free_tree(node->right);
		if (!node->right && !node->left)
			free_node(node);
	}
}
