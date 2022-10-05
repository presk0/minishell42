/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:24:22 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 08:24:28 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_heredoc(int sig)
{
	(void)sig;
	ft_putstr_fd("\b\b  \b\b\n", 1);
	rl_on_new_line();
}

static void	heredoc_process(int sign_num)
{
	if (!kill(g_pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			//rl_on_new_line();
			//rl_redisplay();
		}
		else if (sign_num == SIGINT)
			ft_putchar_fd('\n', 1);
	}
	else if (sign_num == SIGINT)
	{
		ft_putendl_fd("", 1);
		//rl_on_new_line();
		//rl_redisplay();
	}
}

void	heredoc_sigint_handler(int sign_num)
{
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_pid != 0)
		heredoc_process(sign_num);
	if (sign_num == SIGINT)
	{
		ft_putendl_fd("", 1);
		//rl_on_new_line();
		//rl_redisplay();
	}
	else if (sign_num == SIGQUIT)
	{
		ft_putendl_fd("", 1);
		//rl_on_new_line();
		//rl_redisplay();
	}
}

void	heredoc_init_sig(struct termios *tmp, t_data *param)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sigint_handler);
	tcgetattr(0, tmp);
	tmp->c_lflag &= ~ECHOCTL;
	tmp->c_lflag |= ECHO;
	tcgetattr(0, &param->save);
	tcsetattr(0, 0, tmp);
}

