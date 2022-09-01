static void	pipex(char **argv, char **env, int *i)
{
	pid_t	parent;
	int		end[2];
	int		j;
	int		fd;

	j = 2;
	fd = 0;
	while (j < i[2] - 1)
	{
		pipe(end);
		parent = fork();
		if (!parent)
		{
			dup2(fd, STDIN_FILENO);
			if (j < i[2] - 2)
				dup2(end[1], STDOUT_FILENO);
			ft_child_process(argv[j], env, end);
		}
		else
			ft_parent_process(end, &fd);
		j++;
	}
}