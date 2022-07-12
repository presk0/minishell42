/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/07/11 17:14:22 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <libftprintf.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>

typedef struct	s_cmd_tree
{
	char				*data;
	char				***envp;
	int					fds[2];
	int 				ret;
	int					fds_err[2];
	int					ignore_node;
	pid_t				pid;
	struct s_cmd_tree	*oparend;
	struct s_cmd_tree	*right;
	struct s_cmd_tree	*left;
}	t_cmd_tree;

enum e_my_builtins {e_exit, NB_BUILTINS};

typedef struct	my_builtins
{
	int (*func)(void);
}	t_my_builtins;

t_my_builtins g_my_builtins[NB_BUILTINS];

char    	*convert_var(char *line, int i_dollar, char *var_substitution, int var_len);
char    	*convert_var_in_line(char *line, char *envp[]);
char    	*find_path(char *cmd, char **envp);
char    	*read_multilines(char *prompt);
char    	*return_env_var(char *var, size_t var_len, char *envp[]);
int 		apply_line(char *line, char *envp[]);
int     	ft_exit(void);
int     	ft_is_last_ope(t_cmd_tree *node);
int     	ft_is_leave(t_cmd_tree *node);
int     	ft_is_left_child(t_cmd_tree *node);
int     	ft_is_operand(char *data);
int     	ft_is_quoted(char *c, int i);
int     	line_not_finished(char *line);
int     	not_escaped(char *str, int i);
pid_t	 	child_process(t_cmd_tree *node);
size_t		ft_var_len(char *var_start);
t_cmd_tree	*line_to_tree(char *cmd_line, char *envp[]);
t_cmd_tree	*new_node(char *data, t_cmd_tree *parent);
void		convert_var_in_node(t_cmd_tree **node, char **envp);
void		execute(char *argv, char **envp);
void		free_node(t_cmd_tree *node);
void		free_tree(t_cmd_tree *node);
void		init_builtins(void);
void		node_exe(t_cmd_tree *node);
void		node_pipex(t_cmd_tree *node);
void		node_split_multisep(t_cmd_tree **root, char **sep);
void		print_tree(t_cmd_tree *root, int level);
void		sig_func(int sig);
void		tree_parse_split(t_cmd_tree **node, char **sep, void (*f)(t_cmd_tree **, char **));
void		tree_parsing(t_cmd_tree *node);
char		*get_path(char *cmd);
void		node_cmd(t_cmd_tree *node);
void		rec_tree_parsing(t_cmd_tree *node);
//int			quote_nb_split(char *cmd);
int cmd_split(char *cmd);
char	**quotes_spaces_split(char *line);
void	print_tab(char **tab);

#endif
