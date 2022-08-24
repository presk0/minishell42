/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/24 17:41:17 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *param, int i, int **fd)
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
			close((*fd)[0]);
			dup2((*fd)[1], STDOUT_FILENO);
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
			close((*fd)[1]);
			dup2((*fd)[0], STDIN_FILENO);
			if (cmd)
				ft_free_split(cmd);
			cmd = NULL;
			waitpid(pid, NULL, 0);
			close((*fd)[0]);
		}
	}
	else
	{
		cmd_split_sw(param);
		check_built((*fd)[1], param);
	}
}

void	execute_pipe(t_data *param, char **cmd, int i, int *fd)
{
	(void)i;

	i = verif_bultin(param);
	if (!i)
	{
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

void	child_process(t_data *param, int i, int **fd)
{
	pid_t	pid;
	char	*path;
	char	**cmd;

	if (pipe(*fd) == -1)
		return ;
	pid = fork();
	cmd = NULL;
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		path = return_env_var("PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		free(path);
		if (dup2((*fd)[1], STDOUT_FILENO) == -1)
			printf("redir file decr erreor \n");
		close((*fd)[0]);
		//dup2(fd[1], STDOUT_FILENO);
		//print_tab(param->f_matrix);
		execute_pipe(param, cmd, i, *fd);
	}
	else
	{
		close((*fd)[1]);
		if (dup2((*fd)[0], STDIN_FILENO) == -1)
			fprintf(stderr, "redir file decr erreor \n");
		if (cmd)
			ft_free_split(cmd);
		cmd = NULL;
		waitpid(pid, NULL, 0);
		close((*fd)[0]);
	}
}
