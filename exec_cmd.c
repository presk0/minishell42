/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/17 12:09:20 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// getenv output cannot be free (not malloc)
// return NULL if path doesn't exist

int ft_file_exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

/*
int	format_relative_path(t_data *param, char **str)
{
	char	*pwd;
	char	**pwd_split;
	int		pwd_level;
	int		path_ind;
	char	*new_path;
	int i;

	path_ind = 0;
	pwd_level = 0;
	pwd = get_env("PWD", param->envp);
	pwd_split = ft_split(pwd, '/');
	pwd_level = ft_matrixlen(pwd_split) - 1;
	while (pwd_level >= 0 && pwd_split[pwd_level])
	{
		if (!ft_strncmp(&str[path_ind], "../", 3))
			path_ind += 3;
		else
			break ;
		pwd_level--;
	}
	new_path = "/";
	i = 0;
	while (pwd_level--)
	{
		new_path = ft_strjoin(new_path, pwd_split[i++];
	}
	free(pwd);
	ft_free_split(&pwd_split);
}
*/
//int			exec_bin_to_fd
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

int	quote_empty(char *first_quote)
{
	if (first_quote)
	{
		if (first_quote[0] == first_quote[1])
			return (1);
		else if (first_quote[0] && first_quote[1])
			return (0);
	}
	return (-1);
}

/* spaces num if not quoted */
int	line_presplit(char *cmd)
{
	int	quote;
	int	i;
	int	tab_len;
	int	last_quote;

	ft_is_quoted(NULL, 0);
	last_quote = 0;
	quote = 0;
	i = 0;
	tab_len = 1;
	while (cmd[i])
	{
		if ((quote = ft_is_quoted(cmd, i)) != last_quote)
		{
			cmd[i] = '\0';
			tab_len++;
			last_quote = quote;
		}
		if (cmd[i] == ' ' && !quote && tab_len++)
			cmd[i] = '\0';
		i++;
	}
	return (tab_len);
}

char	**quotes_spaces_split(char *line)
{
	int		i;
	int		nb_split;
	int		next;
	char	**matrix;

	nb_split = line_presplit(line);
	matrix = malloc(sizeof(char *) * (nb_split + 1));
	i = 0;
	next = 0;
	while (i < nb_split)
	{
		matrix[i] = ft_strdup(&line[next]);
		next += ft_strlen(&line[next]) + 1;
		i++;
	}
	matrix[i] = NULL;
	//free(line);
	return (matrix);
}

int	rm_null_lines(char ***cmd_split)
{
	int	new_i;
	int	i;

	new_i = 0;
	i = 0;
	while ((*cmd_split)[i])
	{
		if (*(*cmd_split)[i] != '\0')
		{
			if (i != new_i)
				(*cmd_split)[new_i] = (*cmd_split)[i];
			new_i++;
		}
		else
			free((*cmd_split)[i]);
		i++;
	}
	return (new_i);
}

char	**cmd_format(char *str, char *PATH, int is_builtin)
{
	int 	last_i;
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
		free(cmd_split[0]);
		cmd_split[0] = cmd_path;
	}
	return (cmd_split);
}

