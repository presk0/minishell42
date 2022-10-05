/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:18:47 by swalter           #+#    #+#             */
/*   Updated: 2022/10/05 16:55:04 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_single_command(t_data *param, char **cmd, int pid)
{
	int	ret;

	signal(SIGQUIT, sigint_handler);
	if (cmd)
		ft_free_split(&cmd);
	cmd = NULL;
	waitpid(pid, &ret, 0);
	param->retour = WEXITSTATUS(ret);
	dup2(dup(0), STDIN_FILENO);
	dup2(dup(1), STDOUT_FILENO);
}

void	execute_single(t_data *param)
{
	char	**cmd;
	int		pid;
	int		fds[2];

	if (verif_bultin(param))
		exec_bultins(param);
	else
	{
		cmd = cmd_format_add_path(param);
		pid = fork();
		g_pid = pid;
		if (pid == 0)
		{
			redir_execute_single(param, &fds);
			if (execve(cmd[0], cmd, param->envp) <= -1)
				command_failed(param, &cmd);
		}
		else
			wait_single_command(param, cmd, pid);
	}
}

void	single_cmd(t_data *param)
{
	if (set_f_matrix(param, 0) == -1)
		return ;
	execute_single(param);
}
