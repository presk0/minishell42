/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 16:21:46 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h> 

#include <stdio.h> 

#include <unistd.h> 

/* Write COUNT copies of MESSAGE to STREAM, pausing for a second 
void writer (const char* message, int count, FILE* stream) 
{
    for (; count > 0; --count) {
       fprintf (stream, "%s\n", message); 
       fflush (stream); 
       sleep (1); 
    } 
} 

void reader (FILE* stream) 
{
    char buffer[1024]; 
    while (!feof (stream) 
           && !ferror (stream) 
           && fgets (buffer, sizeof (buffer), stream) != NULL) 
       fputs (buffer, stdout); 
} 
//https://www.makelinux.net/alp/
int school_pipe() 
{
    int fds[2]; 
    pid_t pid; 
    pipe (fds); 
    pid = fork (); 
    if (pid == (pid_t) 0) {
      FILE* stream; 
      close (fds[1]); 
      stream = fdopen (fds[0], "r"); 
      reader (stream); 
        close (fds[0]); 
      } 
      else {
        FILE* stream; 
        close (fds[0]); 
        stream = fdopen (fds[1], "w"); 
        writer ("Hello, world.", 5, stream); 
        close (fds[1]); 
      } 
      return 0; 
*/
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
	printf("execute i = %d\n", i);
	if (!i)
	{
		//fprintf(stderr, "[execute] go to exec\n");
		path = return_env_var("PATH", param->envp);
		cmd = cmd_format(param->input_cleaned, path, 0);
		free(path);
		pid = fork();
		//fprintf(stderr, "[execute] forked \n");
		if (pid == 0)
		{
			//fprintf(stderr, "[execute pid = %d`] forked \n", pid);
			if (fd[1] != 1)
			{
				dup2(fd[1], STDOUT_FILENO);
			//fprintf(stderr, "[execute pid = %d`] dup to fd[1] \n", pid);
			}
			if (fd[0] != 0)
			{
				dup2(fd[0], STDIN_FILENO);
			//(stderr, "[execute pid = %d`] dup to fd[0] \n", pid);
			}
			//fprintf(stderr, "[execute pid = %d`] exec fd[0] \n", pid);
			if (execve(cmd[0], cmd, param->envp) <= -1)
				exit(1);
			if (cmd)
				ft_free_split(cmd);
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
			if (cmd)
				ft_free_split(cmd);
			cmd = NULL;
			waitpid(pid, NULL, 0);
			//fprintf(stderr, "[execute pid = %d] after wait\n", pid);
		}
	}
	else
	{
		//fprintf(stderr, "[execute] go to builtin\n");
		cmd_split_sw(param);
		check_built(fd[1], param);
	} 
		//fprintf(stderr, "[execute] finished\n");
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
	//fprintf(stderr, "[child process]\n");
	if (pipe(fd) == -1)
		return ;
//		error();
	pid = fork();
	if (pid == -1)
		return ;
//		error();
	if (pid == 0)
	{
		//fprintf(stderr, "[child process] pid =	%d\n", pid);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(param, i, fd);
	}
	else
	{
		
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
		
		//fprintf(stderr, "[child process] pid =	%d\n", pid);
		//wait(NULL);
	}
	//return (fd[1]);
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
