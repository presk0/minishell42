#include "minishell.h"

/*
 

int main () 
{
    int fds[2]; 

    pid_t pid; 
 
//    /* Create a pipe. File descriptors for the two ends of the pipe are 
 //      placed in fds. 
    pipe (fds); 
  //  /* Fork a child process. 
    pid = fork (); 
    if (pid == (pid_t) 0) {
 //      /* This is the child process. Close our copy of the write end of 
//
 //         the file descriptor. 
       close (fds[1]); 
//       /* Connect the read end of the pipe to standard input. 
       dup2 (fds[0], STDIN_FILENO); 
//       /* Replace the child process with the "sort" program. 
       execlp ("sort", "sort", 0); 
    } 
    else {
 //      /* This is the parent process. 
       FILE* stream; 
       /* Close our copy of the read end of the file descriptor. 
       close (fds[0]); 
 //      /* Convert the write file descriptor to a FILE object, and write 
//
          to it. 
       stream = fdopen (fds[1], "w"); 
       fprintf (stream, "This is a test.\n"); 
       fprintf (stream, "Hello, world.\n"); 
       fprintf (stream, "My dog has fleas.\n"); 
       fprintf (stream, "This program is great.\n"); 
       fprintf (stream, "One fish, two fish.\n"); 
       fflush (stream); 
       close (fds[1]); 
//       /* Wait for the child process to finish. 
       waitpid (pid, NULL, 0); 
    } 
    return 0; 
}
*/

int	set_fd(t_data *param)
{
	int		i;
	int		fd;
    int     j;
    j = 0;
	i = 0;
	fd = 1;
	while (param->f_matrix[i] && ft_memcmp(param->f_matrix[i], ">", 2)
		   && ft_memcmp(param->f_matrix[i], ">>", 3))
		i++;
    if (i == 1)
        return (check_redir(param, i, fd));
    else if(j == 1)
//        return (check_heredoc(param, j, fd));
    else
        return (1);
}

static int	count_redir(t_data *param)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < param->argc)
	{
		if (!ft_memcmp(param->argv[i], ">", 2) ||
			!ft_memcmp(param->argv[i], ">>", 3))
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	copy_args1(t_data *param)
{
	int		i;
	int		j;
	char	**args;

	param->argc -= count_redir(param) * 2;
	args = (char **)ft_calloc(sizeof(char *), param->argc + 1);
	i = 0;
	j = 0;
	while (j < param->argc)
	{
		if (!ft_memcmp(param->argv[i], ">", 2) ||
			!ft_memcmp(param->argv[i], ">>", 3))
			i += 2;
		else
			args[j++] = ft_strdup(param->argv[i++]);
	}
	free_matrix(param->argv);
	param->argv = args;
}



int check_heredoc(t_data *param, int i, int fd)
{
    while(param->argv[i] != NULL) {
        if (!ft_memcmp(param->argv[i], "<<", 3))
            heredoc(param,  i );
        i++;
    }
    return (fd);
}