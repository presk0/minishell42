/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/17 11:24:04 by swalter          ###   ########.fr       */
=======
/*   Updated: 2022/08/16 14:23:01 by swalter          ###   ########.fr       */
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
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
	//printf("execute i = %d\n", i);
	if (!i)
	{
		//fprintf(stderr, "[execute] go to exec\n");
		path = return_env_var("PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		free(path);
		pid = fork();
<<<<<<< HEAD
		//printf("pid execute = %d\n", pid);
		if (pid == 0)
		{
        
			if (fd[1] != 1)
			{
				dup2(fd[1], STDOUT_FILENO);
=======
		//fprintf(stderr, "[execute] forked \n");
		if (pid == 0)
		{
			//fprintf(stderr, "[execute pid = %d`] forked \n", pid);
			if (fd[1] != 1)
			{
				dup2(fd[1], STDOUT_FILENO);
			//fprintf(stderr, "[execute pid = %d`] dup to fd[1] \n", pid);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
			}
			if (fd[0] != 0)
			{
				dup2(fd[0], STDIN_FILENO);
<<<<<<< HEAD
			}
=======
			//(stderr, "[execute pid = %d`] dup to fd[0] \n", pid);
			}
			//fprintf(stderr, "[execute pid = %d`] exec fd[0] \n", pid);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
			if (execve(cmd[0], cmd, param->envp) <= -1)
			{
				param->retour = 126;
				ft_putstr_fd("pas commande bin valide", 2);
			}	
			if (cmd)
			{
				ft_free_split(cmd);
<<<<<<< HEAD
				cmd = NULL;
				//exit(0);
			}	
			exit(param->retour);
			}
		else
		{

=======
			cmd = NULL;
			//fprintf(stderr, "[execute pid = %d`] exec fd[0] \n", pid);
			exit(0);
			// if ((execve(cmd[0], cmd, param->envp)) && errno == EACCES)
			// {
			// param->retour = 126;
			// ft_putstr_fd("pas commande bin valide", 2);
			// }	
			// exit(param->retour);

		}
		else
		{
			//fprintf(stderr, "[execute pid = %d] beforwait\n", pid);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
			if (cmd)
				ft_free_split(cmd);
			cmd = NULL;
			waitpid(pid, NULL, 0);
<<<<<<< HEAD
=======
			//fprintf(stderr, "[execute pid = %d] after wait\n", pid);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
		}
	}
	else
	{
		//fprintf(stderr, "[execute] go to builtin\n");
		cmd_split_sw(param);
		check_built(fd[1], param);
	} 
<<<<<<< HEAD
=======
		//fprintf(stderr, "[execute] finished\n");
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
}

void	execute_pipe(t_data *param, int i, int *fd)
{
	char	**cmd;
	char	*path;
	//int		pid;

	(void)i;
	
	i = verif_bultin(param);
	//printf("execute i = %d\n", i);
	if (!i)
	{
		//fprintf(stderr, "[execute] go to exec\n");
		path = return_env_var("PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		free(path);
			if (execve(cmd[0], cmd, param->envp) <= -1)
				exit(1);
			if (cmd)
				ft_free_split(cmd);
			cmd = NULL;

			if (cmd)
				ft_free_split(cmd);
			cmd = NULL;

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
<<<<<<< HEAD
	
=======
	//fprintf(stderr, "[child process]\n");
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
	if (pipe(fd) == -1)
		return ;

	pid = fork();
	//printf("pid = %d\n", pid);
	if (pid == -1)
		return ;

	if (pid == 0)
	{
<<<<<<< HEAD
						//fprintf(stderr, "child \n");
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
						//fprintf(stderr, "parent wait \n");
		close(fd[0]);
=======
		//fprintf(stderr, "[child process] pid =	%d\n", pid);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(param, i, fd);
	}
	else
	{
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
<<<<<<< HEAD
		//fprintf(stderr, "parent after wait \n");
		//execute(param, i, fd);

	
=======
		//fprintf(stderr, "[child process] pid =	%d\n", pid);
		//wait(NULL);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
	}
	//return (fd[1]);
}


