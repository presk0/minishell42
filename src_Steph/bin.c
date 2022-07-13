#include "minishell.h"

static void	set_in(char **argv)
{
	int		fd;
	int		i;

	i = 0;
	while (argv[i] && ft_memcmp(argv[i], "<", 2))
		i++;
	if (argv[i])
	{
		fd = open(argv[i + 1], O_RDONLY, 0666);
		if (fd < 0)
		{
			ft_putstr_fd("Couldn't read from file.\n", 2);
			return ;
		}
		dup2(fd, 0);
		close(fd);
	}
}

static void	exec_bin(int fd, char *path, t_data *param)
{
	char	**args;
	int		pid;
	args = copy_args(param);
	//signal(SIGINT, child_sig_handler);
	pid = fork();
	if (pid < 0)
		exit(param->retour);
	if (pid == 0)
	{
		set_in(param->argv);
		if (fd > 1)
			dup2(fd, 1);
		if ((execve(path, args, param->envp)) && errno == EACCES)
		{
			param->retour = 126;
			ft_putstr_fd("pas commande bin valide", 2);
		}
		exit(param->retour);
	}
	waitpid(pid, NULL, 0);
	param->retour /= 256;
	free(path);
	//free_matrix(args);
}

static char	**split_path(t_data *param)
{
	char *path;
	char **paths;

	path = get_env(param->envp, "PATH");
	if (path)
		paths = ft_split_strsep(path, ":", 1);
	else
	{
		//ft_putstrs_fd("bash: ", str, ": No such file or directory\n", 2);
		param->retour = 127;
		return (NULL);
	}
	return (paths);
}

static char	*search_bin(char *str, DIR **dir, struct dirent **d, t_data *param)
{
	char		**paths;
	char		*path;
	int			i;

	if (!(paths = split_path(param)))
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		*dir = opendir(paths[i]);
		while ((*dir) && errno != EACCES && (*d = readdir(*dir)))
		{
			if (!ft_memcmp(str, (*d)->d_name, ft_strlen(str) + 1))
			{
				path = ft_strjoin(paths[i], "/");
				free_matrix(paths);
				return (path);
			}
		}
		closedir(*dir);
	}
	free_matrix(paths);
	return (NULL);
}

int			check_bin(int fd, t_data *param)
{
	DIR				*dir;
	struct dirent	*d;
	char			*pre_path;
	char			*path;

	param->retour = 127;
	pre_path = search_bin(param->argv[0], &dir, &d, param);
	if (pre_path)
	{
		path = ft_strjoin(pre_path, d->d_name);
		exec_bin(fd, path, param);
		closedir(dir);
	}
	free(pre_path);
	return (param->retour);
}
