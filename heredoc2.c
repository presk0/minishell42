/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:25:12 by swalter           #+#    #+#             */
/*   Updated: 2022/10/06 12:15:05 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	test(void)
{
	int	fd;

	if (isatty(0))
	{
		while (wait(NULL) != -1 || errno != ECHILD)
			;
	}
	if (signal(SIGINT, &sig_heredoc) == SIG_ERR
		|| signal(SIGQUIT, &sig_heredoc) == SIG_ERR)
		return (-1);
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

int	heredoc(char *c)
{
	int		fd;
	char	*input;
	int		len;

	fd = test();
	if (fd == -1)
		return (fd);
	input = readline("heredoc>");
	if (!input)
		return (0);
	len = ft_strlen(c);
	while (1)
	{
		if (!ft_memcmp(input, c, len + 1))
		{
			break ;
			close (fd);
		}
		ft_putstr_fd(input, fd);
		write(fd, "\n", 1);
		input = readline("heredoc>");
	}
	fd = open("heredoc", O_RDWR);
	return (fd);
}

int	rm_heredoc_file(void)
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
			write(2, "rm_heredoc_file error\n", 22);
		else if (pid == 0)
		{
			execve(rm_cmd[0], rm_cmd, NULL);
			exit(1);
		}
		else
			wait(NULL);
	}
	ft_free_split(&rm_cmd);
	return (1);
}
