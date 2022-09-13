/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:21:26 by swalter           #+#    #+#             */
/*   Updated: 2022/08/31 16:17:56 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	set_cmds(t_data *param)
{
	char	**sep;
	int		i;

	i = 0;
	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	ft_free_split(&sep);
	sep = NULL;
	while (param->cmds[i])
		i++;
	return (i);
}

void	parser2(t_data *param)
{
	int		i;
	int		j;
	char	**sep;
	pid_t	parent;
	int		end[2];
	int		fds[2];
	int		fd;
	
	j = set_cmds(param);
	sep = ft_split(">>,>,<<,<", ',');
	i = 0;
    if( j == 1)
    {
        param->f_matrix = pop_names_from_sep(param, i, sep);
		execute(param, j);
    }
    else
	{
        while (i < j) {
            pipe(end);
			param->f_matrix = pop_names_from_sep(param, i, sep);
			fds[1] = redir_out(param->f_matrix);
			fds[0] = redir_in(param->f_matrix);
			parent = fork();
			if (!parent)
			{
				if (!fds[0])
					dup2(fd, STDIN_FILENO);
				else
					dup2(fds[0], STDIN_FILENO);
				if (fds[1] != 1)
					dup2(fds[1], STDOUT_FILENO);
				else if (i < j - 1)
                    dup2(end[1], STDOUT_FILENO);
				ft_child_process(param, i, end);
            }
			else
			{
				if (fds[0])
					dup2(fds[0], end[0]);
				ft_parent_process(param, end, &fd);
				ft_free_split(&param->f_matrix);
			}
			i++;
        }
    }
	// free(param->input);
	// free(param->f_matrix);	
	if (param->cmds)
		ft_free_split(&param->cmds);
	if (sep)
		ft_free_split(&sep);
}

