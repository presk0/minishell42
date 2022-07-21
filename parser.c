/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/20 18:52:37 by supersko         ###   ########.fr       */
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

int	is_input(char **matrix, int i)
{
	return (!strncmp("<", matrix[i - 1], 1));
}

int	is_output(char **matrix, int i)
{
	return (!strncmp(">", matrix[i - 1], 1));
}

int	*init_fd(char **fmatrix, int *in_out_redir)
{
	int		i_matrix;
	int		*io_cpy;

	if (!in_out_redir)
		return (NULL);
	io_cpy = in_out_redir;
	if (fmatrix)
	{
		i_matrix = ft_matrixlen(fmatrix);
		while (--i_matrix > 2)
		{
			if (is_input(fmatrix, i_matrix) && in_out_redir[0] == io_cpy[0])
				in_out_redir[0] = open(fmatrix[i_matrix], O_RDONLY);
			if (is_output(fmatrix, i_matrix) && in_out_redir[1] == io_cpy[1])
				in_out_redir[1] = open(fmatrix[i_matrix], O_WRONLY);
		}
	}
	if (in_out_redir[0] == io_cpy[0])
		in_out_redir[0] = 0;
	if (in_out_redir[1] == io_cpy[1])
		in_out_redir[1] = 1;
	return (in_out_redir);
}

void		parser(t_data *param)
{
	int		i;
	char	**files_matrix;
	char	**sep;
	int		*fd;

	//sep = ft_split(">>,>,<<,<", ',');
	fd = malloc(sizeof(int) * 2);
	//if (!fd)
		//error
	fd[0] = 0;
	fd[1] = 1;
	sep = ft_split("|", ' ');
	param->cmds =ft_split_multistrsep(param->input, sep, 0);
	printf("[pipe_split]\n");
	print_tab(param->cmds);
	free(sep);
	sep = NULL;
	i = 0;
	sep = ft_split(">>,>,<<,<", ',');
	while (param->cmds[i + 1])
	{
		files_matrix = pop_names_from_sep(param, i, sep);
		printf("[input_cleaned] %s\n", param->input_cleaned);
		fd = init_fd(files_matrix, fd);
		if (pipe(fd) == -1)
			return ;
//			error();
		child_process(param, i, fd);
		if (files_matrix)
			ft_free_split(files_matrix);
		files_matrix = NULL;
		i++;
	}
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	files_matrix = pop_names_from_sep(param, i, sep);
	execute(param, i);
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
	free(fd);
}

/*
int	check_redir(t_data *param)
{
	int	i;

	i = 0;
	while(param->i_fname[i] != NULL)
	{
		if (!ft_memcmp(param->i_fname[i], ">", 2))
		{
			fd = open(param->i_fname[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);

		}
		else if(!ft_memcmp(param->i_fname[i], ">>", 3))
			fd = open(param->i_fname[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
		if (param->i_fname[i + 1])
			close(fd);
		i++;
	}
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
