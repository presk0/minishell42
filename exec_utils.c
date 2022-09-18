#include "minishell.h"

void	command_failed(t_data *param, char ***cmd)
{
	param->retour = 126;
	ft_putstr_fd("command not found\n", 2);
	ft_free_split(cmd);
	exit(param->retour);
}
