/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/06/30 14:56:15 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_left_child(t_cmd_tree *node)
{
	if (node && node->oparend)
	{
		if (node->oparend->left == node)	
			return (1);
	}
	return (0);
}

int	ft_is_leave(t_cmd_tree *node)
{
	if (node && !node->left && !node->right)
		return (1);
	else
		return (0);
}

int	ft_is_last_ope(t_cmd_tree *node)
{
	if (node && (!node->left || ft_is_leave(node->left)) && (!node->right || ft_is_leave(node->right)))
		return (1);
	else
		return (0);
}
