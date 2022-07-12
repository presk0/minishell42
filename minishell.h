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

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INFILE 0
# define OUTFILE 1

#endif
