#include "minishell.h"

/*
static int	count_redir(t_data *param)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (++i < param->argc)
	{
		if (!ft_memcmp(param->argv[i], ">", 2) || \
			!ft_memcmp(param->argv[i], ">>", 3))
		{
			count++;
			i++;
		}
	}
	return (count);
}
*/

/*
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
		if (!ft_memcmp(param->argv[i], ">", 2) || \
			!ft_memcmp(param->argv[i], ">>", 3))
			i += 2;
		else
			args[j++] = ft_strdup(param->argv[i++]);
	}
	free_matrix(param->argv);
	param->argv = args;
}
*/

/*
int	check_heredoc(t_data *param, int i, int fd)
{
	while (param->argv[i] != NULL)
	{
		if (!ft_memcmp(param->argv[i], "<<", 3))
			heredoc(param, i);
		i++;
	}
	return (fd);
}
*/
