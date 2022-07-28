/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/28 18:03:01 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	split with pipes 		=> matrix
	split with << or <    	=> consider only the last one
	split with > >> 		=> make all files and write (or append) only the last

char	*clean_join(t_data param, char **cmd_matrix)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd_matrix)
	{
		str = ft_strdup(cmd_matrix[0]);
		while (cmd_matrix[++i])
		{
			tmp = str;
			str = ft_strjoin(str, cmd_matrix[i]);
			free(tmp);
		}
		ft_free_split(cmd_matrix);
	}
	return (str);
}
*/

void init_fd(t_data *param, int **fd, int **io_fd)
{
	int		i;
	int		len;
	(void)io_fd;
	if (!fd)
		return ;
	i = 0;
	(void)io_fd;
	if (!*fd)
		return ;
	(*fd)[0] = 0;
	(*fd)[1] = 1;
	(*io_fd)[0] = 0;
	(*io_fd)[1] = 1;
	if (param->f_matrix)
	{
		fprintf(stderr, "[init_fd]\n");
		print_tab(param->f_matrix);
		len = ft_matrixlen(param->f_matrix);
		while (i < len)
		{
			if (!ft_memcmp(param->f_matrix[i], ">", 2) && param->f_matrix[i + 1])
			{
				(*io_fd)[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
				fprintf(stderr, "[init_fd] file opened: fd[1]= %d\n", (*fd)[1]);
			}
			else if(!ft_memcmp(param->f_matrix[i], ">>", 3) && param->f_matrix[i + 1])
			{
				(*io_fd)[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
				fprintf(stderr, "[init_fd] file opened: fd[1]= %d\n", (*fd)[1]);
			}
			else if (!ft_memcmp(param->f_matrix[i], "<", 2) && param->f_matrix[i + 1])
			{
				(*io_fd)[0] = open(param->f_matrix[i + 1], O_RDONLY, 0666);
				fprintf(stderr, "[init_fd] file opened: fd[0]= %d\n", (*fd)[0]);
			}
			i++;
		}
		fprintf(stderr, "[init_fd] before_check: fd[0]= %d, fd[1]=%d\n", (*fd)[0], (*fd)[1]);
	}
	dup2((*io_fd)[0], (*fd)[0]);
	dup2((*io_fd)[1], (*fd)[1]);
}

void	reinit_after_pipe(t_data *param, int **io_fd)
{

	if (param->f_matrix)
		ft_free_split(param->f_matrix);
	param->f_matrix = NULL;
	if ((*io_fd)[0] != 0)
	{
		close((*io_fd)[0]);
		(*io_fd)[0] = 0;
	}
	if ((*io_fd)[1] != 1)
	{
		close((*io_fd)[1]);
		(*io_fd)[1] = 1;
	}
}
void		parser(t_data *param)
{
	int		i;
	char	**sep;
	int		*fd;
	int		*io_fd;

	fd = malloc(sizeof(int) * 2);
	io_fd = malloc(sizeof(int) * 2);
	//if (!fd)
		//error
	fd[0] = 0;
	fd[1] = 1;
	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	//fprintf(stderr, "[pipe_split]\n");
	//print_tab(param->cmds);
	free(sep);
	sep = NULL;
	i = 0;
	sep = ft_split(">>,>,<<,<", ',');
	while (param->cmds[i + 1])
	{
		param->f_matrix = pop_names_from_sep(param, i, sep);
		//fprintf(stderr, "[input_cleaned] %s\n", param->input_cleaned);
		init_fd(param, &fd, &io_fd);
	//fprintf(stderr, "[parser] %s\n", param->input_cleaned);
	//fprintf(stderr, "[parser] fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
		if (pipe(fd) == -1)
			return ;
		//	error();
		child_process(param, i, fd);
		reinit_after_pipe(param, &io_fd);
		i++;
	}
	param->f_matrix = pop_names_from_sep(param, i, sep);
	init_fd(param, &fd, &io_fd);
	fprintf(stderr, "[parser] %s\n", param->input_cleaned);
	fprintf(stderr, "[parser] fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
	//dup2(fd[0], STDIN_FILENO);
	//dup2(fd[1], STDOUT_FILENO);
	execute(param, i);
	reinit_after_pipe(param, &io_fd);
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
	free(fd);
	free(io_fd);
}

/*
int	*check_redir(t_data *param, int *fd)
{
	int	i;
	int		io_cpy[2];
	
	io_cpy[0] = fd[0];
	io_cpy[1] = fd[1];
	i = 0;
	if (param && param->f_matrix)
	{
		while(param->f_matrix[i] != NULL)
		{
			if (!ft_memcmp(param->f_matrix[i], ">", 2))
				fd[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			else if(!ft_memcmp(param->f_matrix[i], ">>", 3))
				fd[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			else if (!ft_memcmp(param->f_matrix[i], "<", 2))
				fd[0] = open(param->f_matrix[i + 1], O_RDONLY, 0666);
			i++;
		}
	}
	//if (fd[0] == io_cpy[0])
	//	fd[0] = STDIN_FILENO;
	//if (fd[1] == io_cpy[1])
	//	fd[1] = STDOUT_FILENO;
	return(fd);
}
*/

/*
char	**extract_ope_inplace(t_data param, char **sep)
{
	char	**matrix_out;
	char	str;

	str = param->input;
	
}
*/
