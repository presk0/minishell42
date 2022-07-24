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
# include <readline/readline.h>
# include <readline/history.h>

//# include <sys/_types/_posix_vdisable.h>
# include <errno.h>
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INFILE 0
# define OUTFILE 1

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
}	t_data;

int	get_input(t_data *param);
char	*read_multilines(char *prompt);
char	**ft_append_tab(char **tableau, char *str);
//bchar		**ft_split_mini(char *s, char c);
char	*ft_strldup(const char *s, int len);
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
int	ft_matrixlen(char **matrix);
char	**free_matrix_line(char **matrix, int line_nb);
char	*matrix_to_str(char **matrix);

/* env */
char	*convert_var_in_line(char *line, char *envp[]);
char	*return_env_var(char *var, char *envp[]);
/* bin && initial */ /* format without path */
int			exec_bin_to_fd(int fd, t_data *param); 

/* parser */
void		parser(t_data *param);

/* cmd format */
char	**cmd_format(char *str, char *PATH);

/* get filename */
char **pop_names_from_sep(t_data *param, int i, char **sep);

/* pipe */
void	execute(t_data *param, int i);
void	child_process(t_data *param, int i, int *fd);

#endif
