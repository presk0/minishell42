#include <minishell.h>

void	redir_execute_single(t_data *param, int (*fds)[2])
{
	(*fds)[0] = dup(redir_in(param, param->f_matrix));
	(*fds)[1] = dup(redir_out(param->f_matrix));
	dup2((*fds)[0], STDIN_FILENO);
	dup2((*fds)[1], STDOUT_FILENO);
}

void	command_failed(t_data *param, char ***cmd)
{
	param->retour = 126;
	ft_putstr_fd("command not found\n", 2);
	ft_free_split(cmd);
	exit(param->retour);
}

void	wait_single_command(t_data *param, char **cmd, int pid)
{
	int	ret;

	signal(SIGQUIT, sigint_handler);
	if (cmd)
		ft_free_split(&cmd);
	cmd = NULL;
	waitpid(pid, &ret, 0);
	param->retour = WEXITSTATUS(ret);
	dup2(dup(0), STDIN_FILENO);
	dup2(dup(1), STDOUT_FILENO);
}

 void	execute_single(t_data *param)
 {
 	char	**cmd;
 	int		pid;
	int		fds[2];
 	
 	if (verif_bultin(param))
		exec_bultins(param);
	else
 	{
		cmd = cmd_format_add_path(param);
 		pid = fork();
		g_pid = pid;
 		if (pid == 0)
 		{
			redir_execute_single(param, &fds);
			if (execve(cmd[0], cmd, param->envp) <= -1)
				command_failed(param, &cmd);
 		}
 		else
			wait_single_command(param, cmd, pid);
 	}
 }

void	single_cmd(t_data *param)
{
	if (set_f_matrix(param, 0) == -1)
		return ;
	execute_single(param);
}
