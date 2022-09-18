#include "minishell.h"

int	set_cmds(t_data *param)
{
	char	**sep;
	int		i;

	i = 0;
	sep = ft_split("|", ' ');
	param->cmds = ft_split_multistrsep(param->input, sep, 0);
	ft_free_split(&sep);
	sep = NULL;
	while (param->cmds[i])
		i++;
	return (i);
}

char	**cmd_format_add_path(t_data *param)
{
	char	*path;
	char	**cmd;

	path = return_env_var(param, "PATH", param->envp);
	cmd = cmd_format(param->input_cleaned, path, 0);
	free(path);
	return (cmd);
}
