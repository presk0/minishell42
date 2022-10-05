/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:41:51 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 09:32:01 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_format2(t_data *param, char **str, char **envp)
{
	int		i;
	int		new_i;
	char	**cmd_split;

	*str = convert_var_in_line(param, str, envp);
	cmd_split = quotes_spaces_split(*str);
	new_i = 0;
	i = 0;
	while (cmd_split && cmd_split[i])
	{
		if (*cmd_split[i] != '\0')
		{
			if (i != new_i)
				cmd_split[new_i] = cmd_split[i];
			new_i++;
		}
		else
			free(cmd_split[i]);
		i++;
	}
	if (cmd_split)
		cmd_split[new_i] = NULL;
	return (cmd_split);
}

char	**cmd_split_sw(t_data *param)
{
	int		i;
	char	**argv;

	i = 0;
	argv = cmd_format2(param, &param->input_cleaned, param->envp);
	param->argv = argv;
	while (param->argv[i])
		i++;
	param->argc = i;
	return (param->argv);
}

int	check_built(t_data *param, int fd)
{
	if (!ft_memcmp(param->argv[0], "echo", 5))
		run_echo(fd, param);
	else if (!ft_memcmp(param->argv[0], "cd", 3))
		run_cd(param, fd);
	else if (!ft_memcmp(param->argv[0], "unset", 6))
		run_unset(param);
	else if (!ft_memcmp(param->argv[0], "export", 7))
		run_export(param);
	else if (!ft_memcmp(param->argv[0], "exit", 5))
		run_exit(param);
	else if (!ft_memcmp(param->argv[0], "pwd", 4))
		run_pwd(fd);
	else if (!ft_memcmp(param->argv[0], "env", 4))
		run_env(param, fd);
	else if (!ft_memcmp(param->argv[0], "$?", 3))
		error(param);
	else
		return (0);
	return (1);
}

void	run_echo(int fd, t_data *param)
{
	int	i;

	i = 0;
	//fd = 1;
	if (param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3))
		i = 1;
	while (i++ < param->argc)
	{
		ft_putstr_fd(param->argv[i], fd);
		if (i < param->argc - 1 && ft_strlen(param->argv[i + 1]))
			write(fd, " ", 1);
	}
	if (!(param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3)))
		write(fd, "\n", 1);
}

void	run_exit(t_data *param)
{
	int	i;

	if (param->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		param->retour = 1;
	}
	else
	{
		i = 0;
		while (param->argc > 1 && ft_isdigit(param->argv[1][i]))
			i++;
		if (param->argc > 1 && param->argv[1][i])
		{
			ft_putstr_fd("minishell: exit: : numeric argument required\n", 2);
			param->retour = 2;
		}
		if (param->argc > 1 && param->retour != 2)
			i = ft_atoi(param->argv[1]);
		else
			i = param->retour;
		exit(i);
	}
}
