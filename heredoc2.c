/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:25:12 by swalter           #+#    #+#             */
/*   Updated: 2022/10/05 11:46:02 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *c)
{
	int		fd;
	char	*input;
	int		len;

	if (signal(SIGINT, &sig_heredoc) == SIG_ERR
		|| signal(SIGQUIT, &sig_heredoc) == SIG_ERR)
		return (-1);
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
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
