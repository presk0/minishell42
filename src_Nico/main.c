/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/11 18:36:24 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e

//Function: int rl_redisplay ()
//Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
//
//Function: int rl_on_new_line ()
//Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 

/*
int apply_line(char *line, char *envp[])
{
	(void)envp;
	char	**pipe_splited;
	add_history(line);
	//pipe_splited = ft_split_minishell(line, '|');
	return (fprintf(stderr, "%s\n", pipe_splited[0]));
}
*/
void	print_tab(char **tab)
{
	fprintf(stderr, "------------------------\n");
	while (*tab)
	{
		fprintf(stderr, "%s\n", *tab);
		tab++;
	}
	fprintf(stderr, "------------------------\n");
}

char	**cpy_tab(char **tab)
{
	int		tab_size;
	int		i;
	char	**tab_cpy;

	tab_size = 0;
	while (tab[tab_size])
		tab_size++;
	tab_cpy = malloc(sizeof(char *) * (tab_size +1));
	i = 0;
	while (tab[i])
	{
		tab_cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int main(int argc, char *argv[], char *envp[])
{
	int					int_mode;
	char				*line;
	char				**envp_malloc;
	struct sigaction	sa;
	t_cmd_tree			*cmd_tree;

	(void)argc;
	(void)cmd_tree;
	(void)argv;
	envp_malloc = cpy_tab(envp);
	sa.sa_handler = &sig_func;
	sigaction(SIGINT, &sa, NULL);
	int_mode = isatty(STDIN_FILENO);
	while (int_mode)
	{
		if (int_mode == 1)
		{
			line = read_multilines("~$ ");
			rl_redisplay();
			cmd_tree = line_to_tree(line, envp_malloc);
			tree_parsing(cmd_tree);
			printf("------------------------\n");
			print_tree(cmd_tree, 5);
			free_tree(cmd_tree);
			//tab = quotes_spaces_split(line);
			//print_tab(tab);
		}
		int_mode = isatty(STDIN_FILENO);
	}
    return (0);
}

