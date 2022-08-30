/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:21:26 by swalter           #+#    #+#             */
/*   Updated: 2022/08/30 14:06:14 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_process(t_data *param, int i, int *end)
{
	
	close(end[0]);
	execute_pipe(param, i);
}

void	ft_parent_process(int *end, int *fd)
{
	
	close(end[1]);
	*fd = end[0];
	wait(NULL);
}

void		parser2(t_data *param)
{
	int		i;
    char **sep;
	
	pid_t	parent;
	int		end[2];
	int		fd;
	
	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);

	ft_free_split(sep);
	sep = NULL;
	i = 0;
	sep = ft_split(">>,>,<<,<", ',');
	//fd = redir_in(param->f_matrix);    //redir
	while (param->cmds[i])
		i++;
	int j = i;
	i = 0;

    if( j == 1)
    {
        param->f_matrix = pop_names_from_sep(param, i, sep);
		execute(param, j);
    }
    else {
        while (i < j) {

            pipe(end);
            parent = fork();
            if (!parent) {
                dup2(fd, STDIN_FILENO);
                if (i < j - 1)
                    dup2(end[1], STDOUT_FILENO);
                param->f_matrix = pop_names_from_sep(param, i, sep);
				
				ft_child_process(param, i, end);

            } else
                ft_parent_process(end, &fd);
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

