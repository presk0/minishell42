#include "minishell.h"







void		parser(t_data *param)
{
	int i;

	if (check_semicolon(param))
		return ;
	param->cmds = ft_split_mini(param->str, ';');
	i = 0;
	
	
	
	while (param->cmds[i])
	{
		//check_env(&(param->cmds[i]), param);
		param->argc = count_args(param->cmds[i]);
		param->argv = (char **)ft_calloc(sizeof(char *), (param->argc + 1));
		set_args(param->argv, param->cmds[i], param->argc);
		//command_or_pipe(param, i);
		check_built(param);
		printf("param cmds %s\n", param->cmds[i]);
		check_built(fd, param);
		// while(*param->argv)
		// {
		// 	printf("param argv %s\n", *param->argv);
		// 	param->argv++;
		// 	//printf("param argv %s\n", param->export[0]);
			
		// }	
		i++;

		//printf("param export %s/n", param->export[0]);
		//free_matrix(param->argv);
	}
	
	//free(param->str);
	param->str = 0;
	//free_matrix(param->cmds);




}


