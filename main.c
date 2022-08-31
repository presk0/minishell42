/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/31 12:26:56 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int	main(int argc, char **argv, char **envp)
{
    g_pid = 0;
	t_data  *param;
	char	**matrix;
	char	**sep;
	char	*str;
	
	(void)str;
	(void)matrix;
	(void)sep;
    (void)argc;
    (void)argv;
    struct termios  tmp;
	(void)tmp;
	param = init_param(envp);
	matrix = NULL;
 	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	
	
	tcgetattr(0, &tmp);
    tmp.c_lflag &= ~ECHOCTL; 
    tmp.c_lflag |= ECHO;
    tcgetattr(0, &param->save);
    tcsetattr(0, 0, &tmp);
    
	while (42)
	{
		//signal(SIGINT, sigint_handler);
		//signal(SIGQUIT, SIG_IGN);
		
		if (!get_input(param))
			break ;
		if (!strcmp(param->input, ""))
			continue ;
		// if (fgets (param->input, 4096, 0 ) == NULL) { // gestion du ctrl+D
		// 		write(1, "\n", 1); 
		// 		//freeMemory(0);
		// 		exit(0); 
		// } 	
		add_history(param->input);
		if (check_error(param))
			return (-1);
		parser2(param);
	}
	rl_clear_history();
	//freall();
	exit(param->retour);
}
