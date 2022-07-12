/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
    Ctrl+C - SIGINT
    Ctrl+\ - SIGQUIT
    Ctrl+Z - SIGTSTP
*/
int	ft_exit(void)
{
	fprintf(stderr, "bye\n");
	clear_history();
	exit(0);
	return (0);
}

void	sig_func(int sig)
{
	(void)sig;
	fprintf(stderr, "Carry your sigaction\n");
//	if (sig == SIGINT)
//		return ;
//	if (sig == SIGQUIT)
//	{
//		fprintf(stderr, "bye\n");
//		clear_history();
//		exit(0);
//	}
}
