/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:24:22 by swalter           #+#    #+#             */
/*   Updated: 2022/10/05 08:57:40 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
	if (sig == SIGQUIT)
		return ;
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_sig(void)
{
	if (signal(SIGINT, &ft_sig_handler) == SIG_ERR || signal(SIGQUIT,
			&ft_sig_handler) == SIG_ERR)
	{
		ft_putstr_fd("42minishell", 2);
		ft_putstr_fd(": signal problem. \n", 2);
		exit(1);
	}	
}

int	ft_ctrl_d_handler(char *str, t_data param)
{
	if (str == NULL)
	{
		if (isatty(param.save_in))
		{
			printf("\033[2D");
			printf("\033[1A");
			printf("\033[10C");
			printf("exit\n");
		}
		if (isatty(param.save_in))
			exit(0);
		else
			exit(param.retour);
	}
	else
		return (1);
}
