#include "minishell.h"

int	set_fd(t_data *param)
{
	int		i;
	int		fd;
    int     j;
    j = 0;
	i = 0;
	fd = 1;
	while (param->argv[i] && ft_memcmp(param->argv[i], ">", 2)
		   && ft_memcmp(param->argv[i], ">>", 3))
		i++;
    //while (param->argv[j] && ft_memcmp(param->argv[j], "<<", 3))
    //    j++;
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