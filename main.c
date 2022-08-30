/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/30 12:11:14 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static void	sig_handler(int sig)
// {
// 	(void)sig;
// 	//printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

void	    ctrlbacksl(int sig)
{

    (void)sig;
    int pid = 0;

    pid = getpid();
    if (kill(pid, SIGKILL) != -1)
	{
		printf("^\\Quit: %d\n", sig);
		//exit(1);
    }
    else

	exit(0);
    ft_putendl_fd("", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}



void	ctrlc(int sig)
{
	(void)sig;


    ft_putendl_fd("", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int g_pid = 0;

int main(int argc, char **argv, char **envp)
{
    
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
 	tcgetattr(0, &tmp);
    tmp.c_lflag &= ~ECHOCTL; 
    tmp.c_lflag |= ECHO;
    tcgetattr(0, &param->save);

    tcsetattr(0, 0, &tmp);
	signal(SIGINT, ctrlc);
    signal(SIGQUIT, ctrlbacksl);
    while(42)
	{
    // Configure readline to auto-complete paths when the tab key is hit.
	   // rl_bind_key('\t', rl_complete);
		
		
		if (!get_input(param))
		  	break;

		if (!strcmp(param->input, ""))
			continue ;
		add_history(param->input);
		if(check_error(param))
					return (-1);
		parser2(param);
		
	}
	//freall();
	exit(param->retour);
}
