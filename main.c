/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/13 17:43:36 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	sig_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
*/

/*
char	*ft_strldup(const char *s, int len)
{
	char	*ptr;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	if (len < size)
		size = len;
	if (!(ptr = (char *)malloc(sizeof(char) * (size + 1)))	)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
*/

/*
void	ft_qsplit(char *input, char *sep)
{
	int			i;
	char		is_quoted;
	char		*split_left;
	char		*split_right;

	if(!input)
		return ;

	// if no sep
	i = 0;
	ft_is_quoted(NULL, 0);
	while (input[i])
	{
		is_quoted = ft_is_quoted(input, i);
		if (!is_quoted && !ft_inputncmp(&input[i], sep, ft_strlen(sep)))
		{
			split_left = ft_substr(input, 0, i);
			split_right = ft_substr(input, i + ft_strlen(sep), ft_strlen(input));
			//free(input);
			//input = NULL;
			//break;
		}
		i++;
	}
}
*/

/*
void	parser(t_data *param)
{
	param->cmds = ft_split_mini(param->input, '|');
}
*/

int main(int argc, char **argv, char **envp)
{
    t_data  *param;
	char	**matrix;
    (void)argc;
    (void)argv;

	param = init_param(envp);
	matrix = NULL;
    while(42)
	{
		get_input(param);
		if(check_error(param))
			return (-1);
		print_tab(ft_split_strsep(param->input, "|", 1));
	}
	return (0);
}