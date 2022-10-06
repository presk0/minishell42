/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/10/03 11:24:24 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	init_termios(void)
{
	struct termios	config;

	tcgetattr(STDIN_FILENO, &config);
	config.c_lflag &= ~(ECHOCTL);
	config.c_cc[VMIN] = 1;
	config.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &config);
	return (config);
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!cpy)
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}

t_data	*init_param(char **envp)
{
	t_data	*param;

	param = (t_data *)malloc(sizeof(t_data));
	param->save = init_termios();
	param->envp = copy_env(envp, 0);
	param->argv = NULL;
	param->argc = 0;
	param->retour = 0;
	param->input_cleaned = NULL;
	param->path = NULL;
	param->args = NULL;
	param->f_matrix = NULL;
	param->input = NULL;
	param->cmds = NULL;
	param->save_in = dup(STDIN_FILENO);
	return (param);
}
