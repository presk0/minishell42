/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/31 16:57:13 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_bultin(t_data *param)
{
	int	fd_in;
	int	fd_out;

	fd_in = redir_in(param->f_matrix);
	fd_out = redir_out(param->f_matrix);
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

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

char	**cmd_format_add_path(t_data *param)
{
	char	*path;
	char	**cmd;

 	path = return_env_var(param, "PATH", param->envp);
 	cmd = cmd_format(param->input_cleaned, path, 0);
 	free(path);
	return (cmd);
}

void	redir_execute_single(t_data *param, int (*fds)[2])
{
	(*fds)[0] = dup(redir_in(param->f_matrix));
	(*fds)[1] = dup(redir_out(param->f_matrix));
	dup2((*fds)[0], STDIN_FILENO);
	dup2((*fds)[1], STDOUT_FILENO);
}

void	command_failed(t_data *param, char **cmd)
{
 	param->retour = 126;
 	ft_putstr_fd("command not found\n", 2);
 	if (cmd)
 	{
 		ft_free_split(&cmd);
 		cmd = NULL;
 	}
	exit(param->retour);
}

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
				command_failed(param, cmd);
 		}
 		else
			wait_single_command(param, cmd, pid);
 	}
 }

 int	cmd_bloquante(char **cmd, int i)
 {
	 char	*trimed;
	 char	**path_split;
	 int	matrix_len;

	 if (cmd && cmd[0] && i == 0)
	 {
		 matrix_len = ft_matrixlen(cmd);
		 path_split = ft_split(cmd[0], '/');
		 if (!ft_strncmp(path_split[ft_matrixlen(path_split) -1], "cat", 4))
		 {
			ft_free_split(&path_split);
			trimed = ft_strtrim(cmd[matrix_len - 1], " \t");
			if (matrix_len == 1 || trimed[0] == '-')
			{
				ft_free_split(&cmd);
				free(trimed);
				write(2, "\n", 1);
				return (1);
			}
		 }
	 }
	 return (0);
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
		{
			param->retour = 126;
			ft_putstr_fd("pas commande bin valide", 2);
            write(1, "\n", 1);
			exit(param->retour);
		}	
		if (cmd)
		{
			ft_free_split(&cmd);
			cmd = NULL;
		}
	}	
//	else if (i == 1)
//	{
//		exec_bultins(param);
//		exit(0);
//	}
}
