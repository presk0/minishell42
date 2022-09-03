/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/31 16:57:22 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    struct termios  tmp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	tmp.c_lflag &= ~ECHOCTL; 
	tmp.c_lflag |= ECHO;
	tcgetattr(0, &tmp);
	tcsetattr(0, 0, &tmp);
	g_pid = 0;
	param = (t_data *)malloc(sizeof(t_data));
	param->envp = copy_env(envp, 0);
//	param->argv = NULL;
//	param->argc = 0;
	param->retour = 0;
	param->input_cleaned = NULL;
	tcgetattr(0, &param->save);
	return (param);
}
