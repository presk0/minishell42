/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:27:36 by swalter           #+#    #+#             */
/*   Updated: 2022/10/05 16:54:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/resource.h>
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>
#include "readline/readline.h"
#include "readline/history.h"
# include <errno.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INFILE 0
# define OUTFILE 1

pid_t g_pid;

typedef struct s_data
{
	int				argc;
	char			**argv;
	char			**f_matrix;
	char			**envp;
	char			*path;
	char			*args;
	int				retour;
	char			*input;
	char			*input_cleaned;
	char			**cmds;
	int				pid;
	int				pipe;
	struct termios	save;
}	t_data;

char	**cmd_format2(t_data *param, char **str, char **envp);
char	**cmd_format_add_path(t_data *param);
char	**cmd_format(char *str, char *PATH, int is_builtin);
char	**cmd_split_sw(t_data *param);
char	*convert_var(char *line, int i_dollar, char *var_substitution, int var_len);
char	*convert_var_in_line(t_data *param, char **line, char **envp);
char	**copy_env(char **envp, int add);
char	**export_command2(t_data *param, int j);
char	**export_command(t_data *param, int j);
char	**export_command(t_data *param, int j);
char	**free_matrix_line(char **matrix, int line_nb);
char	**ft_append_tab(char **matrix, char *str);
char	**ft_split_mini(char *s, char c);
char	**ft_split_mini(char *s, char c);
char	**ft_split_mini(char *s, char c);
char	**ft_split_multistrsep(char *str, char **sep, int keep_sep);
char	**ft_split_strsep(char *str, char *sep, int is_char);
char	*get_env(char **envp, char *env);
char	*get_new_var(t_data *param, int j);
char	*get_path(char *cmd, char *PATH);
char	*heredoc_loop(int *first_loop, char **line, char **tmp, char **text);
char	*matrix_to_str(char **matrix);
char	**new_env(char **envp, int i);
char	*pop_first_wd(char **cmd);
char	**pop_names_from_sep(t_data *param, int i, char **sep);
char	**quotes_spaces_split(char *line);
char	*read_multilines(char *prompt);
char	*return_env_var(t_data *param, char *var, char *envp[]);
char	*return_first_word(char *str);
char	**run_export(t_data *param);
char	**run_unset(t_data *param);
int		check_built(t_data *param, int fd);
int		check_error(t_data *param);
int		check_f_matrix(char **f_matrix);
int		ft_file_exists(const char *fname);
int		ft_is_bultin(t_data *param);
int		ft_is_quoted(char *c, int i);
int		ft_matrixlen(char **matrix);
int		ft_only_blank(t_data *param);
int		get_input(t_data *param);
int		heredoc_fd(char **text, char **line);
int		heredoc(t_data *param, char *stop_str);
int		is_available_var_name(char *var, int i);
int		is_blank(char c);
int		line_presplit(char *cmd);
int		quote_empty(char *first_quote);
int		redir_in(t_data	*param, char **f_matrix);
int		redir_out(char **f_matrix);
int		rm_heredoc_file(void);
int		rm_null_lines(char ***cmd_split);
int		set_cmds(t_data *param);
int		set_f_matrix(t_data *param, int i);
int		verif_bultin(t_data *param);
size_t	ft_var_len(char *var_start);
t_data	*init_param(char **envp);
void	cd_command(t_data *param);
void	cde_bash(t_data *param);
void	check_exit(t_data *param);
void	clean_exit(t_data *param);
void	command_failed(t_data *param, char ***cmd);
void	del_first_word(char **str);
void	error(t_data *param);
void	exec_bultins(t_data *param);
void	exec_pipes(t_data *param, int (*end)[2], int (*fds)[2], int i, int j);
void	execute_pipe(t_data *param, int i);
void	ft_child_process(t_data *param, int i, int *end);
void	ft_parent_process(t_data *param, int pid, int (*fds)[2], int (*end)[2], int *fd);
void	hard_wait(void);
void	init_fd_child(t_data *param, int (*fds)[2], int fd);
void	init_fd(t_data *param, int **fd, int **io_fd);
void	init_sig(struct termios *tmp, t_data *param);
void	parser(t_data *param);
void	pop_names_from_sep_refresh(t_data *param, char ***cmd_split);
void	print_env_tri(t_data *param);
void	print_tab(char **tableau);
void	redir_bultin(t_data *param);
void	redir_execute_single(t_data *param, int (*fds)[2]);
void	redir_fd_child(int fds[2], int end[2], int i, int j);
void	reinit_after_pipe(t_data *param, int **io_fd);
void	reset_param(t_data *param);
void	run_echo(int fd, t_data *param);
void	run_env(t_data *param, int fd);
void	run_exit(t_data *param);
void	run_exit(t_data *param);
void	sigint_handler(int sign_num);
void	single_cmd(t_data *param);
void	wait_single_command(t_data *param, char **cmd, int pid);
void	run_pwd(int fd);
void	run_cd(t_data *param, int fd);
void	change_dir(char *path, t_data *param);
void	bloody_normi(char **str, char ***matrix_split, int *i);
void	heredoc_init_sig(struct termios *tmp, t_data *param);
void	heredoc_sigint_handler(int sign_num);
void	handler_heredoc(int sig);
#endif
