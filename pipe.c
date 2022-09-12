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

void	exec_bultins(t_data *param)
{
	int	fd_in;
	int	fd_out;
	int	stdin_cpy;
	int	stdout_cpy;

	stdin_cpy = dup(0);
	stdout_cpy = dup(1);
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
	cmd_split_sw(param);
	check_built(param, 1);
	dup2(stdin_cpy, 0);
	dup2(stdout_cpy, 1);
}

 void	execute(t_data *param, int i)
 {
 	char	**cmd;
 	char	*path;
 	int		pid;
	int fd = 1;

 	(void)i;
 	i = verif_bultin(param);
 	if (!i)
 	{
 		path = return_env_var("PATH", param->envp);
 		cmd = cmd_format(param->input_cleaned, path, 0);
 		free(path);
 		pid = fork();
		g_pid = pid;
 		if (pid == 0)
 		{
			dup2(redir_out(param->f_matrix), STDOUT_FILENO);
			dup2(redir_in(param->f_matrix), STDIN_FILENO);
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
 			close (fd);
			exit(param->retour);
 		}
 		else
 		{
 			signal(SIGQUIT, sigint_handler);
			if (cmd)
 				ft_free_split(&cmd);
 			cmd = NULL;
 			waitpid(pid, NULL, 0);
		}
 	}
 	else
 	{
		exec_bultins(param);
 	}
 }

void	execute_pipe(t_data *param, int i)
{
	char	**cmd;
	char	*path;
	(void)i;
	//int fd = 1;
	
	i = verif_bultin(param);
	if (!i)
	{
		path = return_env_var("PATH", param->envp);
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
	else
	{
		exec_bultins(param);
		exit(0);
	}
}
