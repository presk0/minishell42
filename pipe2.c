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
	int	ret;

	close(end[1]);
	*fd = end[0];
	wait(&ret);
	param->retour = WEXITSTATUS(ret);
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

void rm_heredoc_file(void)
{
	int		fd;
	int		pid;
	char	**rm_cmd;

	rm_cmd = ft_split("/bin/rm heredoc", ' ');
	fd = open(rm_cmd[1], O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		pid = fork();
		if (pid == -1)
		{
			write(2, "rm_heredoc_file error\n", 22);
		}
		else if (pid == 0)
		{
			execve(rm_cmd[0], rm_cmd, NULL);
			exit(1);
		}
		else
			wait(NULL);
	}
	ft_free_split(&rm_cmd);
}

int	check_f_matrix(char **f_matrix)
{
	int	i;

	i = 1;
	if (f_matrix)
	{
		while (f_matrix[i])
		{
			if (!strncmp(f_matrix[i], "", 2))
			{
				write(2, "syntax error near unexpected token `newline'\n", 45);
				return (0);
			}
			if (!f_matrix[++i])
				return (1);
			i++;
		}
	}
	return (1);
}

int	set_f_matrix(t_data *param, int i)
{
	char	**sep;

	sep = ft_split(">>,>,<<,<", ',');
    param->f_matrix = pop_names_from_sep(param, i, sep);
	if (!check_f_matrix(param->f_matrix))
	{
		ft_free_split(&sep);
		return (-1);
	}
	else
	{
		ft_free_split(&sep);
		return (1);
	}
}

void	parser2(t_data *param)
{
	int		i;
	int		j;
	pid_t	pid;
	int		end[2];
	int		fds[2];
	int		fd;
	
	j = set_cmds(param);
	i = 0;
    if( j == 1)
    {
		if (set_f_matrix(param, i) == -1)
			return ;
		execute(param, j);
    }
    else
	{
        while (i < j) {
            pipe(end);
			if (set_f_matrix(param, i) == -1)
				return ;

			if (verif_bultin(param))
				execute(param, i);
			else
			{
				pid = fork();
				if (pid == 0)
				{
					fds[1] = redir_out(param->f_matrix);
					fds[0] = redir_in(param->f_matrix);
					if (fds[0] == 0)
						fds[0] = fd;
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
			}
			rm_heredoc_file();
			i++;
        }
    }
	if (param->cmds)
		ft_free_split(&param->cmds);
	rm_heredoc_file();
}

