/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:30:27 by swalter           #+#    #+#             */
/*   Updated: 2022/09/19 09:31:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, fd);
	free(pwd);
	ft_putchar_fd('\n', fd);
}

void	run_cd(t_data *param, int fd)
{
	char	cwd[4097];
	char	*path;

	if (!param->argv[1])
		path = ft_strdup("~");
	else
		path = ft_strdup(param->argv[1]);
	cd_command(param);
	if (path && !ft_strncmp(path, "-", 2))
		ft_putstr_fd(getcwd(cwd, 4096), fd);
	free(path);
}

void	change_dir(char *path, t_data *param)
{
	char	cwd[4097];
	char	oldpwd[4097];

	getcwd(oldpwd, 4096);
	if (chdir(path) == 0)
	{
		param->argc = 4;
		ft_free_split(&param->argv);
		param->argv = (char **)ft_calloc(sizeof(char *), 4);
		param->argv[0] = ft_strdup("export");
		param->argv[1] = ft_strdup("OLDPWD=");
		param->argv[2] = ft_strdup(oldpwd);
		param->envp = export_command(param, 1);
		ft_free_split(&param->argv);
		param->argv = (char **)ft_calloc(sizeof(char *), 4);
		param->argv[0] = ft_strdup("export");
		param->argv[1] = ft_strdup("PWD=");
		param->argv[2] = ft_strdup(getcwd(cwd, 4096));
		param->envp = export_command(param, 1);
	}
	else
		ft_putstr_fd("minishell: cd: error", 2);
}

void	cd_command(t_data *param)
{
	char	*path;

	errno = 0;
	if (param->argc <= 2)
	{
		if (!param->argv[1] || !ft_strncmp(param->argv[1], "--", 3) || \
			!ft_strncmp(param->argv[1], "~", 2))
			path = get_env(param->envp, "HOME");
		else if (!ft_strncmp(param->argv[1], "-", 2))
			path = get_env(param->envp, "OLDPWD");
		else
			path = param->argv[1];
		change_dir(path, param);
		if (errno > 0)
		{
			ft_putstr_fd(strerror(errno), 2);
			param->retour = 1;
		}
	}
	else
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		param->retour = 1;
	}
}

char	**run_unset(t_data *param)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	if (param->argc < 2)
		return (param->envp);
	env = param->argv[1];
	j = ft_strlen(env);
	while (param->envp)
	{
		if (!ft_memcmp(env, param->envp[i], j))
		{
			param->envp = new_env(param->envp, i);
			break ;
		}
		else
			i++;
	}
	return (param->envp);
}
