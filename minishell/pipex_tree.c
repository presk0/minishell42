/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/02 17:34:18 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_subtree(t_cmd_tree *node, int fd[2], pid_t pid)
{
	if (node)
	{
		node->fds[0] = fd[0];
		node->fds[1] = fd[1];
		// pid init value = 1
		node->pid = pid;
		if (node->right)
			init_subtree(node->right, fd, pid);
		if (node->left)
			init_subtree(node->left, fd, pid);
	}
}

// copy node->fds in all subtree
void	node_pipex(t_cmd_tree *node)
{
	if (pipe(node->fds) == -1)
	{
		//carry error
		perror(NULL);
	}
	node->pid = fork();
	if (node->pid == -1)
		perror(NULL);
	else if (node->pid == 0)
	{
		close(node->fds[0]);
		dup2(node->fds[1], STDOUT_FILENO);
		if (node->left)
			init_subtree(node->left, node->fds, node->pid);
		// and execute
	}
	else
	{
		close(node->fds[1]);
		dup2(node->fds[0], STDIN_FILENO);
		if (node->right)
			init_subtree(node->right, node->fds, node->pid);
		waitpid(node->pid, NULL, 0);
		// cpy subtree
	}
}
