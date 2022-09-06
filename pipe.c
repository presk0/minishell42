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

 void	execute(t_data *param, int i)
 {
 	char	**cmd;
 	char	*path;
 	int		pid;
	int fd = 1;

 	(void)i;
 	i = verif_bultin(param);
	fd = redir_out(param->f_matrix);
	dup2(fd, 1);
 	if (!i)
 	{
 		path = return_env_var("PATH", param->envp);
 		cmd = cmd_format(param->input_cleaned, path, 0);
 		free(path);
 		pid = fork();
		g_pid = pid;
 		if (pid == 0)
 		{
			if (execve(cmd[0], cmd, param->envp) <= -1)
 			{
 				param->retour = 126;
 				ft_putstr_fd("pas commande bin valide", 2);
				write(1, "\n", 1);
				exit(param->retour);
			}
 			if (cmd)
 			{
 				ft_free_split(cmd);
 				cmd = NULL;
 			}
 			close (fd);
			exit(param->retour);
 		}
 		else
 		{
 			signal(SIGQUIT, sigint_handler);
			if (cmd)
 				ft_free_split(cmd);
 			cmd = NULL;
 			waitpid(pid, NULL, 0);
		}
 	}
 	else
 	{
 		cmd_split_sw(param);
 		check_built(param, i);
 	}
 }

