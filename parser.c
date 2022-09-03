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

void init_fd(t_data *param, int **fd, int **io_fd)
{
	int		i;
	int		len;
	(void)io_fd;
	if (!fd)
		return ;
	i = 0;
	if (!*fd)
		return ;
	(*fd)[0] = 0;
	(*fd)[1] = 1;
	(*io_fd)[0] = 0;
	(*io_fd)[1] = 1;
	if (param->f_matrix)
	{
		//printf(stderr, "[init_fd]\n");
		//print_tab(param->f_matrix);
		len = ft_matrixlen(param->f_matrix);
		while (i < len)
		{
			if (!ft_memcmp(param->f_matrix[i], ">", 2) && param->f_matrix[i + 1])
			{
				(*io_fd)[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
				//printf(stderr, "[init_fd] file opened: fd[1]= %d\n", (*io_fd)[1]);
			}
			else if(!ft_memcmp(param->f_matrix[i], ">>", 3) && param->f_matrix[i + 1])
			{
				(*io_fd)[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
				//printf(stderr, "[init_fd] file opened: fd[1]= %d\n", (*io_fd)[1]);
			}
			else if (!ft_memcmp(param->f_matrix[i], "<", 2) && param->f_matrix[i + 1])
			{
				(*io_fd)[0] = open(param->f_matrix[i + 1], O_RDONLY, 0666);
				//printf(stderr, "[init_fd] file opened: fd[0]= %d\n", (*io_fd)[0]);
			}
			i++;
		}
		//printf(stderr, "[init_fd] before_check: fd[0]= %d, fd[1]=%d\n", (*fd)[0], (*fd)[1]);
	}
	dup2((*io_fd)[0], (*fd)[0]);
	dup2((*io_fd)[1], (*fd)[1]);
}

void	reinit_after_pipe(t_data *param, int **io_fd)
{
	if (param->f_matrix)
		ft_free_split(param->f_matrix);
	param->f_matrix = NULL;
	if ((*io_fd)[0] != STDIN_FILENO)
	{
		close((*io_fd)[0]);
		(*io_fd)[0] = STDIN_FILENO;
	}
	if ((*io_fd)[1] != STDOUT_FILENO)
	{
		close((*io_fd)[1]);
		(*io_fd)[1] = STDOUT_FILENO;
	}
}

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

void	parser2(t_data *param)
{
	int		i;
	int	nb_cmd;
	char	**sep;
	pid_t	parent;
	int		end[2];
	int		fd;

	sep = ft_split(">>,>,<<,<", ',');
	//fd = redir_in(param->f_matrix);    //redir
	i = 0;
	nb_cmd = ft_pipe_split(param);
    if(nb_cmd == 1)
    {
        param->f_matrix = pop_names_from_sep(param, i, sep);
		execute(param, nb_cmd);
    }
    else {
        while (i < nb_cmd) {

            pipe(end);
            parent = fork();
            if (!parent) {
                dup2(fd, STDIN_FILENO);
                if (i < nb_cmd - 1)
                    dup2(end[1], STDOUT_FILENO);
                param->f_matrix = pop_names_from_sep(param, i, sep);
				
				ft_child_process(param, i, end);

            } else
                ft_parent_process(param, end, &fd);
            i++;
        }
    }
	//fd[0] = redir_in(param->f_matrix);
	//fd[1] = redir_out(param->f_matrix);
	// free(param->input);
	// free(param->f_matrix);	
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
}

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
