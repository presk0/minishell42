void	ft_child_process(char *argv, char **env, int *end)
{
	char	**flag;

	close(end[0]);
	flag = ft_split(argv, ' ');
	execve(ft_cmd(flag[0], env), flag, env);
}

void	ft_parent_process(int *end, int *fd)
{
	close(end[1]);
	*fd = end[0];
	wait(NULL);
}

