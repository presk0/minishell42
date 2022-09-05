
#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/wait.h>
# include <libft.h>
# include <libftprintf.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
//# include <readline/readline.h"
//# include "readline/history.h"
#include <readline/readline.h>
#include <readline/history.h>
//# include <sys/_types/_posix_vdisable.h>
# include <errno.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INFILE 0
# define OUTFILE 1

pid_t g_pid;

typedef struct		s_data
{
	int		argc;
	char	**argv;
	char	**f_matrix;
	char	**envp;
	char	*path; // PATH/cmd;
	char	*args; // args passed to execve;
	char	**i_fname;
	char	**o_fname;
//	char	**var;
	int		retour;
	char	*input;
	char	*input_cleaned;
	char	**cmds;
	int		pid;
	int		pipe;
	struct termios save;
}	t_data;

int		get_input(t_data *param);
char	*read_multilines(char *prompt);
char	**ft_append_tab(char **tableau, char *str);
//bchar		**ft_split_mini(char *s, char c);
//char	*ft_strldup(const char *s, int len);
char	**ft_append_tab(char **tableau, char *str);
int		ft_is_quoted(char *c, int i);
int		check_error(t_data *param);

/* split */
char	**ft_split_multistrsep(char *str, char **sep, int keep_sep);
char	**ft_split_strsep(char *str, char *sep, int is_char);

/* init */
t_data	*init_param(char **envp);
char	**copy_env(char **envp, int add);

/* debug */
void	print_tab(char **tableau);

/* strings */
void	del_first_word(char **str);
char    *return_first_word(char *str);
char    *pop_first_wd(char **cmd);

/* matrix */
int		ft_matrixlen(char **matrix);
char	**free_matrix_line(char **matrix, int line_nb);
char	*matrix_to_str(char **matrix);

/* env */
char	*convert_var_in_line(char *line, char *envp[]);
char	*return_env_var(char *var, char *envp[]);
/* bin && initial */ /* format without path */
int			exec_bin_to_fd(int fd, t_data *param); 

/* parser */
void		parser2(t_data *param);

/* cmd format */
char	**cmd_format(char *str, char *PATH, int is_builtin);
int	redir_out(char **f_matrix);
int	redir_in(char **f_matrix);

/* get filename */
char **pop_names_from_sep(t_data *param, int i, char **sep);

/* pipe */
void	execute(t_data *param, int i);
void	execute_pipe(t_data *param, int i);



/*bultins*/

char	**cmd_format2(char **str, char **envp);
char    **cmd_split_sw(t_data *param);
void	run_echo(int fd, t_data *param);
void	run_exit(t_data *param);
char	**quotes_spaces_split(char *line);
void	cd_command(t_data *param);
char    **run_unset(t_data *param);
void	run_env(t_data *param, int fd);
void	error(t_data *param);
char    **run_export(t_data *param);
void	set_in(char **argv);
void	cde_bash(t_data *param);

/* env*/
char	**new_env(char **envp, int i);
char	**copy_env(char **envp, int add);
char	*get_env(char **envp, char *env);
char	**export_command(t_data *param, int j);
int 	verif_bultin(t_data *param);
void    print_env_tri(t_data *param);
char	**export_command2(t_data *param, int j);


/* signaux */
void	ctrlbacksl(int sig);
void	ctrlc(int sig);
void	ft_child_process(t_data *param, int i, int *end);
void	ft_parent_process(t_data *param, int *end, int *fd);
void		sigint_handler(int sign_num);
int check_built(t_data *param, int fd);
void	easy_redir(t_data *param);
int	ft_pipe_split(t_data *param);

#endif
