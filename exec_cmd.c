/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/09/19 08:19:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_file_exists(const char *fname)
{
	FILE	*file;

	file = fopen(fname, "r");
	if (file)
	{
		fclose(file);
		return (1);
	}
	return (0);
}

char	*get_path(char *cmd, char *PATH)
{
	char	*str;
	char	**env_tab;
	int		i;

	if (!cmd)
		return (NULL);
	if (!ft_memcmp(cmd, "/", 1) && ft_file_exists(cmd))
		return (ft_strdup(cmd));
	if (!ft_memcmp(cmd, "./", 2))
		return (ft_strdup(&cmd[2]));
	env_tab = ft_split(PATH, ':');
	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (env_tab[i])
	{
		str = ft_strjoin(env_tab[i++], cmd);
		if (ft_file_exists(str))
			break ;
		free(str);
		str = NULL;
	}
	ft_free_split(&env_tab);
	free(cmd);
	return (str);
}

char	**cmd_format(char *str, char *PATH, int is_builtin)
{
	int		last_i;
	char	*cmd_path;
	char	**cmd_split;

	cmd_split = quotes_spaces_split(str);
	if (!cmd_split)
		return (NULL);
	last_i = rm_null_lines(&cmd_split);
	cmd_split[last_i] = NULL;
	if (!is_builtin)
	{
		cmd_path = get_path(cmd_split[0], PATH);
		if (cmd_path)
		{
			free(cmd_split[0]);
			cmd_split[0] = cmd_path;
		}
	}
	return (cmd_split);
}
