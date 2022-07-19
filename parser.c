/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/19 12:59:51 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	split with pipes 		=> matrix
	split with << or <    	=> consider only the last one
	split with > >> 		=> make all files and write (or append) only the last

char	*clean_join(t_data param, char **cmd_matrix)
{
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd_matrix)
	{
		str = ft_strdup(cmd_matrix[0]);
		while (cmd_matrix[++i])
		{
			tmp = str;
			str = ft_strjoin(str, cmd_matrix[i]);
			free(tmp);
		}
		ft_free_split(cmd_matrix);
	}
	return (str);
}
*/

void		parser(t_data *param)
{
	int		i;
	char	**cmd_matrix;
	char	**sep;

	//sep = ft_split(">>,>,<<,<", ',');
	sep = ft_split("|", ' ');
	param->cmds =ft_split_multistrsep(param->input, sep, 0);
	free(sep);
	i = 0;
	// fork 
	while (param->cmds[i])
	{
		// pipe
		sep = ft_split("<<,<", ',');
		cmd_matrix = ft_split_multistrsep(param->cmds[i], sep, 1);
		printf("%s\n", param->cmds[i]);
		// check input file
		// clean input line
		// make (all) output files
		i++;
	}
	//free_matrix(sep);
	//free_matrix(param->cmds);
}

/*
int	check_redir(t_data *param)
{
	int	i;

	i = 0;
	while(param->i_fname[i] != NULL)
	{
		if (!ft_memcmp(param->i_fname[i], ">", 2))
		{
			fd = open(param->i_fname[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0666);

		}
		else if(!ft_memcmp(param->i_fname[i], ">>", 3))
			fd = open(param->i_fname[i + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
		if (param->i_fname[i + 1])
			close(fd);
		i++;
	}
	return(fd);
}
*/

/*
char	**extract_ope_inplace(t_data param, char **sep)
{
	char	**matrix_out;
	char	str;

	str = param->input;
	
}
*/
