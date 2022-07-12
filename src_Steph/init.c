#include "minishell.h"

// void	init_param(t_data **param, char **argv)		//, char **envp, int *ret_len)
// {
// 	(*param) = (t_data *)malloc(sizeof(t_data));
// 	//(*param)->envp = copy_env(envp, 0);
// 	(*param)->export = (char **)ft_calloc(sizeof(char *), 1);
// 	(*param)->argv = argv;
// 	(*param)->retour = 0;
// 	(*param)->str = 0;
// 	(*param)->pipe_child = 0;
// 	//ret_len[0] = 1;
// 	//print_msg();

// }

// static void print_minishell(void)
// {
// 	ft_putstr(" welcome to mini-hell\n", 2);
// }

static void	free_param(t_data *param)
{
	free(param->str);
	free_matrix(param->envp);
	free_matrix(param->export);
	free_matrix(param->argv);
	free_matrix(param->cmds);
	free(param);
}
