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

int	*init_fd(t_data *param, int fd[2])
{
	int		i;
	int		io_fd[2];

	(void)io_fd;
	if (!fd)
		return (NULL);
	fd[0] = 0;
	fd[1] = 1;
	io_fd[0] = 0;
	io_fd[1] = 1;
	if (param->f_matrix)
	{
		fprintf(stderr, "[init_fd]\n");
		print_tab(param->f_matrix);
		i = ft_matrixlen(param->f_matrix);
		while (--i >= 0)
		{
			if (!ft_memcmp(param->f_matrix[i], ">", 2) && param->f_matrix[i + 1])
			{
				io_fd[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
				fprintf(stderr, "[init_fd] file opened: fd[1]= %d\n", fd[1]);
			}
			else if(!ft_memcmp(param->f_matrix[i], ">>", 3) && param->f_matrix[i + 1])
			{
				io_fd[1] = open(param->f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
				fprintf(stderr, "[init_fd] file opened: fd[1]= %d\n", fd[1]);
			}
			else if (!ft_memcmp(param->f_matrix[i], "<", 2) && param->f_matrix[i + 1])
			{
				io_fd[0] = open(param->f_matrix[i + 1], O_RDONLY, 0666);
				fprintf(stderr, "[init_fd] file opened: fd[0]= %d\n", fd[0]);
			}
		}
		fprintf(stderr, "[init_fd] before_check: fd[0]= %d, fd[1]=%d\n", fd[0], fd[1]);
		dup2(io_fd[0], fd[0]);
		dup2(io_fd[1], fd[1]);
	}
	return (fd);
}

void	close_all_fds()
{
	int	i;

	i = 2;
	while (i++ < 255)
	{
		close(i);
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

/* return command number */
int	split_cmds(t_data *param)
{
	int	i;
	char	**sep;

	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	ft_free_split(sep);
	sep = NULL;
	i = 0;
	while (param->cmds[i])
		i++;
	return (i);
}

void	parser2(t_data *param)
{
	int	i;
	char	**sep;
	pid_t	parent;
	int	end[2];
	int	*fd_io;
	
	int j = split_cmds(param);
	sep = ft_split(">>,>,<<,<", ',');
	fd_io = malloc(sizeof(int) * 2);
	i = 0;
    if( j == 1)
    {
        param->f_matrix = pop_names_from_sep(param, i, sep);
	    init_fd(param, fd_io);
		execute(param, j);
    }
    else {
        while (i < j) {
            pipe(end);
            param->f_matrix = pop_names_from_sep(param, i, sep);
	    init_fd(param, fd_io);
            parent = fork();
            if (!parent)
	    {
                if (i < j - 1)
		//close end[0]
		ft_child_process(param, i, end);
            } else
	    {
                ft_parent_process(param, end, fd_io);
	    }
	    close_all_fds();
            i++;
        }
    }
	// free(param->input);
	// free(param->f_matrix);	
	if (param->cmds)
		ft_free_split(param->cmds);
	if (sep)
		ft_free_split(sep);
}

