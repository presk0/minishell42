#ifndef MINISHELL_H
# define MINISHELL_H
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
# include <sys/_types/_posix_vdisable.h>
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
	char	**envp;
//	char	**var;
	int		retour;
	char	*input;
	char	**cmds;
}					t_data;

int	get_input(t_data *param);
char	*read_multilines(char *prompt);
char	**ft_append_tab(char **tableau, char *str);
char		**ft_split_mini(char *s, char c);
char	*ft_strldup(const char *s, int len);
char	**ft_append_tab(char **tableau, char *str);
int	ft_is_quoted(char *c, int i);
int	check_error(t_data *param);

/* init */
t_data	*init_param(char **envp);
char	**copy_env(char **envp, int add);

/* debug */
void	print_tab(char **tableau);

#endif
