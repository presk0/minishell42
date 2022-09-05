/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/17 12:41:20 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//from https://harm-smits.github.io/42docs/projects/minishell

void	clean_and_set_f_matrix(t_data *param)
{
	char	**sep;

	sep = ft_split(">>,>,<<,<", ',');
	param->f_matrix = pop_names_from_sep(param, 0, sep);
	free(sep);
	sep = NULL;
}

void	easy_redir(t_data *param)
{ //save in/out
	int tmpin=dup(0);
	int tmpout=dup(1);
	int ret;
	int fdin;
	int fdout;
	int	nb_cmd;
	int	i;

	nb_cmd = ft_pipe_split(param);
	i = 0;
	while (i++ < nb_cmd) {
		//redirect input
		clean_and_set_f_matrix(param);
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == nb_cmd)
		{
		// Last simple command
			if(outfile){
				fdout = outfile;
			}
			else {
			// Use default output
			fdout=dup(tmpout);
			}
		}
		else
		{
		// Not last
		//simple command
		//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}// if/else
		// Redirect output
		dup2(fdout,1);
		close(fdout);
	// Create child process
		ret=fork();
		if(ret==0) {
			execute_pipe(param, i);
			_exit(1);
		}
	} // for
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
//	if (!background) {
//		// Wait for last command
//		waitpid(ret, NULL, 0);
//	}
} // execute

void	ft_child_process(t_data *param, int i, int *end)
{
	close(end[0]);
	execute_pipe(param, i);
}

void	ft_parent_process(t_data *param, int *end, int *fd)
{
	close(end[1]);
	*fd = end[0];
	wait(&param->retour);
	param->retour /= 256;
}

/* returns cmds number */
int	ft_pipe_split(t_data *param)
{
	char	**sep;
	int	nb_cmd;

	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	ft_free_split(sep);
	sep = NULL;
	nb_cmd = 0;
	while (param->cmds[nb_cmd])
		nb_cmd++;
	return (nb_cmd);
}

/*
void	parser2(t_data *param)
{
	int		i;
	int		nb_cmd;
	char	**sep;
	pid_t	parent;
	int		*end;
	int		*fds;
	int		fd;

	sep = ft_split(">>,>,<<,<", ',');
	//fd = redir_in(param->f_matrix);    //redir
	i = 0;
	end = malloc(sizeof(int) * 2);
	fds = malloc(sizeof(int) * 2);
	nb_cmd = ft_pipe_split(param);
	while (i < nb_cmd)
	{
        pipe(end);
		param->f_matrix = pop_names_from_sep(param, i, sep);
		parent = fork();
		if (parent)
		{
			init_fd(param, &fds, &end);
			ft_parent_process(param, end, &fd);
		//fd = end[0] after executtion of ft_parent_process
		//without fd, the pipe does not finish
		}
		else
	    {
			fd = end[0];
			dup2(fd, STDIN_FILENO);
			init_fd(param, &fds, &end);
			if (i < nb_cmd - 1)
			{
				dup2(end[1], STDOUT_FILENO);
			}
			ft_child_process(param, i, end);
		}
//	    reinit_after_pipe(param, &fds);
		i++;
	}
	//fd[0] = redir_in(param->f_matrix);
	//fd[1] = redir_out(param->f_matrix);
	// free(param->input);
	// free(param->f_matrix);	
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
	free(fds);
	free(end);
}
*/

/*
void		parser(t_data *param)
{
	int		i;
	char	**sep;
	int		*fd;
	
	fd = malloc(sizeof(int) * 2);
	// if (!fd)
	// 	error;
	fd[0] = 0;
	fd[1] = 1;

	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);

	ft_free_split(sep);
	sep = NULL;
	i = 0;
	sep = ft_split(">>,>,<<,<", ',');
	//fd[0] = redir_in(param->f_matrix);    //redir
	
	while (param->cmds[i])
		i++;
	if (i == 1)
	{
		param->f_matrix = pop_names_from_sep(param, 0, sep);
		execute(param, 0);
	}	
	else
	{	
		int j = i;
		i = 0;
		while (i < j - 1)
		{
			//fd[1] = redir_out(param->f_matrix);                   //redir
			//fd[0] = redir_in(param->f_matrix);
			param->f_matrix = pop_names_from_sep(param, i, sep);
			ft_child_process(param, i, fd);
			i++;
		}
		//fd[0] = redir_in(param->f_matrix);
		//fd[1] = redir_out(param->f_matrix);
		param->f_matrix = pop_names_from_sep(param, i, sep);
		execute(param, j);
		//close(fd[0]);
		close(fd[1]);		       
		//si execute -> prompt et sortie si excecute_pipe -> sortie
	}
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
						//si on ferme -> sortie du programme
							
	free(fd);
}
*/
