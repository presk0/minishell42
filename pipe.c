/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/10/05 17:10:40 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bultins(t_data *param)
{
	int	stdin_cpy;
	int	stdout_cpy;

	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
	redir_bultin(param);
	cmd_split_sw(param);
	check_built(param, 1);
	dup2(stdin_cpy, 0);
	dup2(stdout_cpy, 1);
}

void	exec_bultins_pipes(t_data *param, int fd)
{
	//redir_bultin(param);
	cmd_split_sw(param);
	check_built(param, fd);
}

void	exec_pipes(t_data *param, int (*end)[2], int (*fds)[2], int i, int j)
{
	pid_t	pid;
	int		fd;

	dup2(fd, (*end)[0]);
	//fd = dup((*end)[0]);
	pipe(*end);
	if (set_f_matrix(param, i) == -1)
		return ;
	if (verif_bultin(param) == 1)
		exec_bultins_pipes(param, 1);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			init_fd_child(param, fds, fd);
			redir_fd_child((*fds), (*end), i, j);
			ft_child_process(param, i, (*end));
		}
		else
			ft_parent_process(param, pid, fds, end, &fd);
	}
	rm_heredoc_file();
	ft_free_split(&param->argv);
}

void	execute_pipe(t_data *param, int i)
{
	char	**cmd;
	char	*path;
	int		j;

	(void)i;
	j = verif_bultin(param);
	if (!j)
	{
		path = return_env_var(param, "PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		free(path);
		if (execve(cmd[0], cmd, param->envp) <= -1)
			command_failed(param, &cmd);
	}	
	else
	{
		exec_bultins_pipes(param, 1);
		exit(0);
	}
}

void	ft_child_process(t_data *param, int i, int *end)
{
	close(end[0]);
	execute_pipe(param, i);
}

void	ft_parent_process(t_data *param, int pid, int (*fds)[2], \
	int (*end)[2], int *fd)
{
	int	ret;

	if ((*fds)[0])
	{
		dup2((*fds)[0], (*end)[0]);
	}
	close((*end)[1]);
	*fd = (*end)[0];
	waitpid(pid, &ret, 0);
	param->retour = WEXITSTATUS(ret);
	ft_free_split(&param->f_matrix);
}
