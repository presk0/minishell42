/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/10/06 11:24:05 by supersko         ###   ########.fr       */
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
	if (param->input)
		free(param->input);
	if (param->input_cleaned)
		free(param->input_cleaned);
	if (param->cmds)
		ft_free_split(&param->cmds);
	param->argc = 0;
	param->pipe = 0;
	param->argv = NULL;
	param->f_matrix = NULL;
	param->path = NULL;
	param->args = NULL;
	param->input = NULL;
	param->input_cleaned = NULL;
	param->cmds = NULL;
}

int	ft_only_blank(t_data *param)
{
	int	i;

	i = 0;
	if (!strcmp(param->input, ""))
		return (1);
	while (param->input[i])
	{
		if (param->input[i] != ' ' && param->input[i] != '\t')
			return (0);
		i++;
	}
	free(param->input);
	param->input = NULL;
	return (1);
}

void	clean_exit(t_data *param)
{
	rl_clear_history();
	reset_param(param);
	rm_heredoc_file();
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*param;

	(void)argc;
	(void)argv;
	param = init_param(envp);
	while (1)
	{
		init_sig();
		if (isatty(param->save_in))
		{
			while (wait(NULL) != -1 || errno != ECHILD)
				;
		}		
		if (!get_input(param))
			break ;
		if (ft_only_blank(param))
			continue ;
		add_history(param->input);
		if (check_error(param))
			continue ;
		if (ft_ctrl_d_handler(param->input, *param) && param->input != 0)
			parser(param);
		rm_heredoc_file();
		reset_param(param);
	}
	clean_exit(param);
}
