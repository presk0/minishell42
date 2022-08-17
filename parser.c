/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/17 11:15:05 by swalter          ###   ########.fr       */
=======
/*   Updated: 2022/08/16 14:35:34 by swalter          ###   ########.fr       */
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
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
<<<<<<< HEAD
		//print_tab(param->f_matrix);
=======
		print_tab(param->f_matrix);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
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

void		parser(t_data *param)
{
	int		i;
	char	**sep;
	int		*fd;
	
	fd = malloc(sizeof(int) * 2);
	//if (!fd)
		//error
	fd[0] = 0;
	fd[1] = 1;
<<<<<<< HEAD

	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);

=======
	//fprintf(stderr, "[parser] start fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	//f//printf(stderr, "[pipe_split]\n");
	//print_tab(param->cmds);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
	ft_free_split(sep);
	sep = NULL;
	i = 0;
	sep = ft_split(">>,>,<<,<", ',');

<<<<<<< HEAD
	//fd[0] = redir_in(param->f_matrix);    //redir

=======
	//fd[0] = redir_in(param->f_matrix);
	//print_tab(param->cmds);
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0

	while(param->cmds[i])
	{
		
		i++;
	}
<<<<<<< HEAD
=======
	////printf("nombre de coomades %d\n", i );
	
	if(i == 1)
	{
		param->f_matrix = pop_names_from_sep(param, 0, sep);
		//print_tab(param->f_matrix);	
		execute(param, 0, fd);
	}	
	else
	{	
		i = 0;
		while (param->cmds[i])
		{
	//f//printf(stderr, "[parser] while loop fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
	//f//printf(stderr, "[parser] pipe fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
		//fd[1] = redir_out(param->f_matrix);
	//f//printf(stderr, "[parser] %s\n", param->input_cleaned);
	//f//printf(stderr, "[parser] fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
			param->f_matrix = pop_names_from_sep(param, i, sep);
			child_process(param, i, fd);
			i++;
		//fd[0] = redir_in(param->f_matrix);
		}
	//param->f_matrix = pop_names_from_sep(param, i, sep);
	//f//printf(stderr, "[parser] %s\n", param->input_cleaned);
	//f//printf(stderr, "[parser] fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
	//fd[0] = redir_in(param->f_matrix);
		//fd[1] = redir_out(param->f_matrix);
		//close(fd[1]);
		close(fd[0]);	
	}
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
	//close(fd[1]);						//si on ferme -> sortie du programme
	//close(fd[0]);						
	free(fd);
}
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0

	
	if(i == 1)
	{
		param->f_matrix = pop_names_from_sep(param, 0, sep);

		execute(param, 0, fd);
	}	
	else
	{	
		int j = i;
		i = 0;
		while (i < j)
		{

			//fd[1] = redir_out(param->f_matrix);                   //redir
			//fd[0] = redir_in(param->f_matrix);
			param->f_matrix = pop_names_from_sep(param, i, sep);

			child_process(param, i, fd);
			i++;
		
		}
		
		//fd[0] = redir_in(param->f_matrix);
		//fd[1] = redir_out(param->f_matrix);
		execute(param, j, fd);

	

	}
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
	//close(fd[1]);						//si on ferme -> sortie du programme
	//close(fd[0]);						
	free(fd);
}

