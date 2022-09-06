/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/31 14:45:59 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data  *param;
	
    (void)argc;
    (void)argv;
	param = init_param(envp);
	while (42)
	{
		//signal(SIGINT, sigint_handler);
		//signal(SIGQUIT, SIG_IGN);
		if (!get_input(param))
			break ;
		if (!strcmp(param->input, ""))
			continue ;
		add_history(param->input);
		if (check_error(param))
			return (-1);
		easy_redir(param);
	}
	rl_clear_history();
	//freall();
	exit(param->retour);
}
