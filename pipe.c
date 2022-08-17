/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/17 12:00:38 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *param, int i, int *fd)
{
	char	**cmd;
	char	*path;
	int		pid;

	(void)i;
	
	i = verif_bultin(param);
	if (!i)
	{
		path = return_env_var("PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		free(path);
		pid = fork();
		if (pid == 0)
		{
			// if (fd[1] != 1)
			// {
			// 	dup2(fd[1], STDOUT_FILENO);
			// }
			// if (fd[0] != 0)
			// {
			// 	dup2(fd[0], STDIN_FILENO);
			// }
			if (execve(cmd[0], cmd, param->envp) <= -1)
			{
				param->retour = 126;
				ft_putstr_fd("pas commande bin valide", 2);
			}	
			if (cmd)
			{
				ft_free_split(cmd);
				cmd = NULL;
				//exit(0);
			}	
			exit(param->retour);
		}
		else
		{

			if (cmd)
				ft_free_split(cmd);
			cmd = NULL;
			waitpid(pid, NULL, 0);
		}
	}
	else
	{
		cmd_split_sw(param);
		check_built(fd[1], param);
	}
}

void	execute_pipe(t_data *param, int i, int *fd)
{
	char	**cmd;
	char	*path;
	(void)i;

	i = verif_bultin(param);
	if (!i)
	{
		path = return_env_var("PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		free(path);
		if (execve(cmd[0], cmd, param->envp) <= -1)
			exit(1);
		if (cmd)
		{
			ft_free_split(cmd);
			cmd = NULL;
		}
	}
	else
	{

		cmd_split_sw(param);
		check_built(fd[1], param);
	}
}

void	child_process(t_data *param, int i, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
		return ;

	if (pid == 0)
	{
		if (dup2(fd[1], 1) == -1)
			fprintf(stderr, "redir file decr erreor \n");
		close(fd[0]);
		close (fd[1]);
		//dup2(fd[1], STDOUT_FILENO);
		//print_tab(param->f_matrix);
		execute_pipe(param, i, fd);
	}
	else
	{
		if (dup2(fd[0], 0) == -1)
			printf("redir file decr erreor \n");
		close(fd[0]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		//execute(param, i, fd);
	}
}


