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

void	parser2(t_data *param)
{
	int		i;
	char	**sep;
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
            param->f_matrix = pop_names_from_sep(param, i, sep);
	    fprintf(stderr, "[nb_redir_in] %d\n", redir_in(param));
	    fprintf(stderr, "[nb_redir_out] %d\n", redir_out(param));
            parent = fork();
            if (!parent) {
                if (i < j - 1)
                    dup2(end[1], STDOUT_FILENO);
				
				ft_child_process(param, i, end);

            } else
                ft_parent_process(param, end, &fd);
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

