/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/12 16:14:24 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* helped with https://github.com/gabcollet/pipex */

/* A simple error displaying function.
void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}
*/

/* Function that take the command and send it to find_path
 before executing it. 
*/
void	execute(t_data *param, int i, int *fd)
{
	char	**cmd;
	char	*path;
	int		pid;

	(void)i;
	
	i = verif_bultin(param);
	
	if (!i)
	{
		fprintf(stderr, "[execute] go to exec\n");
		path = return_env_var("PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		pid = fork();
		if (pid == 0)
		{
			if (fd[1] >= 1)
				dup2(fd[1], STDOUT_FILENO);
			if (fd[0] >= 0)
				dup2(fd[0], STDIN_FILENO);
			if (execve(cmd[0], cmd, param->envp) == -1)
				exit(-1);
		}
		else
			wait(NULL);
	}
	else
	{
		fprintf(stderr, "[execute] go to builtin\n");
		cmd_split_sw(param);
		check_built(fd[1], param);
	} 
		fprintf(stderr, "[execute] finished\n");
		
	
}


/* Function to open the files with the right flags 
int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}
*/

void	child_process(t_data *param, int i, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
//		error();
	pid = fork();
	if (pid == -1)
		return ;
//		error();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execute(param, i, fd);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
}

/* Parent process that take the data from the pipe, change the output for the
 fileout and also close with the exec function 
void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}
*/
