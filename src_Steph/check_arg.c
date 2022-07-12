#include "minishell.h"

void	check_arg(t_data *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(param->cmds[i])
	{
		while(param->argv[j]) {
			printf(" argc %d, %s\n", j, param->argv[j]);
			j++;
		}
		i++;
	}

}

