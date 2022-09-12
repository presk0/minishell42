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

#include "minishell.h"

void	reset_param(t_data *param)
{
	if (param->argv)
		ft_free_split(&param->argv);
	if (param->f_matrix)
		ft_free_split(&param->f_matrix);
	if (param->path)
		free(param->path);
	if (param->args)
		free(param->args);
//	if (param->i_fname)
//		ft_free_split(&param->i_fname);
//	if (param->o_fname)
//		ft_free_split(&param->o_fname);
	if (param->input)
		free(param->input);
	if (param->input_cleaned)
		free(param->input_cleaned);
	if (param->cmds)
		ft_free_split(&param->cmds);
	param->argc = 0;
	param->pipe = 0;
	param->pid = 0;
	param->argv = NULL;
	param->f_matrix = NULL;
	param->path = NULL;
	param->args = NULL;
//	param->i_fname = NULL;
//	param->o_fname = NULL;
	param->input = NULL;
	param->input_cleaned = NULL;
	param->cmds = NULL;
}

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
		add_history(param->input);
		if (check_error(param))
			return (-1);
		parser2(param);
		reset_param(param);
	}
	rl_clear_history();
	reset_param(param);
	//freall();
	exit(param->retour);
}
