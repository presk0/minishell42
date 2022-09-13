/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:22:40 by marvin            #+#    #+#             */
/*   Updated: 2022/08/30 18:12:28 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in(char **argv)
{
	int		fd;
	int		i;

	i = 0;
	while (argv[i] && ft_memcmp(argv[i], "<", 2))
		i++;
	if (argv[i])
	{
		fd = open(argv[i + 1], O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("Couldn't read from file.\n", 2);
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}

int	redir_out(char **f_matrix)
{
	int		ret;
	int 	len;
	int	fd;
	int	last_fd;
	int	i;

(void) ret;
	len = ft_matrixlen(f_matrix);
	i = 0;
	fd = 1;
	last_fd = 0;
	while (i < len)
	{
		if (!ft_memcmp(f_matrix[i], ">", 2))
		{
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (last_fd > 1)
				close(last_fd);
			last_fd = fd;
		}
		else if (!ft_memcmp(f_matrix[i], ">>", 3))
		{
			fd = open(f_matrix[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			if (last_fd > 1)
				close(last_fd);
			last_fd = fd;
		}
		i++;
	}
	return (fd);
}

int	heredoc(char *stop_str)
{
	int		fd;
	int		first_loop;
	char	*line;
	char	*text;
	char	*tmp;

	first_loop = 1;
	text = NULL;
	while (first_loop || ft_strncmp(line, stop_str, ft_strlen(stop_str)))
	{
		if (!first_loop)
		{
			tmp = line;
			line = ft_strjoin(line, "\n");
			free(tmp);
			tmp = text;
			if (text)
			{
				text = ft_strjoin(text, line);
				free(tmp);
			}
			else
				text = line;
		}
		line = readline("> ");
		first_loop = 0;
	}
	fd = open("heredoc", O_WRONLY | O_CREAT, 00666);
	write(fd, text, ft_strlen(text));
	close(fd);
	free(text);
	free(line);
	fd = open("heredoc", O_RDONLY);
	return (fd);
}

int	redir_in(char **f_matrix)
{
	int		ret;
	int 	len;
	int 	fd;
	int	i;
	int last_fd;

(void)ret;
	len = ft_matrixlen(f_matrix);
	i = 0;
	last_fd = 0;
	fd = 0;
	while (i < len && f_matrix[i + 1] && f_matrix[i])
	{
		if (!ft_memcmp(f_matrix[i], "<", 2))
		{
			fd = open(f_matrix[i + 1], O_RDONLY, 0666);
			if (last_fd)
				close(last_fd);
			last_fd = fd;
		}
		else if (!ft_memcmp(f_matrix[i], "<<", 3))
		{
			fd = heredoc(f_matrix[i + 1]);
			if (last_fd)
				close(last_fd);
			last_fd = fd;
		}
		i++;
	}
	return (fd);
}

/*
char		**check_command(char *str, t_data *param)
{
	int		fd;
}}

	if (param->argv[0] && *(param->argv[0]))
	{
		fd = set_fd(param);
		copy_args1(param);
		param->ret = check_builtins(fd, param);
		if (param->ret == 127 && (param->ret = check_bin(fd, param)) == 127)
		{
			ft_putstrs_fd(0, str, ": command not found.\n", 2);
			param->ret = 127;
		}
		if (fd != 1)
			close(fd);
	}
	return (param->envp);
}
*/
