#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
# include <sys/_types/_posix_vdisable.h>
# include <errno.h>

typedef struct		s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	char	**export;
	int		retour;
	char	*str;
	char	**cmds;
	int		*ret_len;
}					t_data;

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INFILE 0
# define OUTFILE 1

char		**copy_args(t_data *param);
int			count_args(char *str);
void		set_args(char **argv, char *str, int argc);
char		**ft_split_mini(char *s, char c);
void		init_param(t_data **param, char **argv);//, char **envp, int *ret_len);
void		parser2(t_data *param);
char		**copy_env(char **envp, int add);
char		*get_env(char **envp, char *env);

int			check_built(int fd, t_data *param);
char        **new_env(char **envp, int i);

// utils
int			check_error(t_data *param);
int			check_semicolon(t_data *param);    					// check " ; " si oui retour 
void		rm_char(char **str, int j);							// enleve un char dans str	
void		rm_token(char **arg);								// enleve ' et '' et \ et les \\ et \'	
void		skip_spaces(char **str);
int			ft_isspace(int c);
int			ft_strlen_pipe(char *str);
int			ft_strlen_arg_token(char *str, char c);
int			ft_strlen_char(char *str, char c);
int			ft_strlen_token(char *str);
int			ft_strlen_env(char *str);
void		free_matrix(char **matrix);
char		*ft_strldup(const char *s, int len);
int			is_token(char c);									// est " ou 
void		free_param(t_data *param);
void		check_doll(char *str);
//bultins
int			check_quotes(char *str, int i);
int			check_dquotes(char *str, int i);
void			run_echo(int fd, t_data *param);
void		run_env(t_data *param, int fd);
// bin
int			check_bin(int fd, t_data *param);
void		error(t_data *param);
//pipes
int			check_redir(t_data *param, int i, int fd);
void			pipe2 (t_data *param);
void		check_command(t_data *param);
void		copy_args1(t_data *param);
void		check_arg(t_data *param);
int			set_fd(t_data *param);



char        **check_export(t_data *param);
char        **new_env_export(char *str, char **envp);

//typedef enum type
//{
//    WORD = 1,
//    PIPE = 2,
//    BULTIN = 3,
//    BIN = 4,
//    HEREDOC = 5,
//    REDIR = 6,
//    VAR_ENV = 7,
//
//}; type;


int    heredoc(t_data *param, int i);
int check_heredoc(t_data *param, int i, int fd);
#endif




