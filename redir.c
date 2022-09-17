#include "minishell.h"

/*
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
*/

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
    while(param->argv[i] != NULL)
	{
        if (!ft_memcmp(param->argv[i], "<<", 3))
            heredoc(param,  i );
        i++;
    }
    return (fd);
}

/*
int    heredoc(t_data *param, int i)
{
    int fd;
    char *input;
    int len;

    fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
    input = readline("heredoc>");
    if(!input)
        return (0);
    len = ft_strlen(param->argv[i + 1]);

    while(1)
    {

        if(!ft_memcmp(input, param->argv[i + 1], len + 1))
           break;
        ft_putstr_fd(input, fd);
        write(fd, "\n", 1);
        input = readline("heredoc>");
    }
    return (fd);
}
*/
