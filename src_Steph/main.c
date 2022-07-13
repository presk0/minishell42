#include "minishell.h"
int	check_quotes(char *str, int i)
{
	int quotes;
	quotes = 0;
	while ((str)[i] )
	{
		if ((str)[i] == '\'')
			quotes++;
		i++;
	}
	if(quotes % 2 == 0 )
		return(1);
	else

	{
		ft_putstr_fd("Non finished quotes\n", 2);
		return (0);
	}

}
int	check_dquotes(char *str, int i)
{
	int quotes;
	quotes = 0;

	while ((str)[i])
	{
		if ((str)[i] == '"')
			quotes++;
		i++;
	}
	if(quotes % 2 == 0 )
		return(1);
	else
	{
		ft_putstr_fd("Non finished quotes\n", 2);
		return (0);
	}
}
static void	sig_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();


}

int	get_input(t_data *param)
{
	
	
	char	*input;
	int		ret;


	ret = 1;
	
	input = readline("\e[033m42mminishell $ \e[39m");
	if (!input)
		return (0);
	param->str = input;
	return (ret);
	//free(input);
}
int main(int argc, char **argv, char **envp)
{
    t_data  *param;
    (void)argc;
    (void)argv;
    int ret;
    ret = 0;
    param  = (t_data *)malloc(sizeof(t_data));
    param->envp = copy_env(envp, 0);
    param->argv = 0;
    param->argc = 0;
	param->retour = 0;
    param->export = 0;
    while(42)
    {
		if(signal(SIGINT, sig_handler) == SIG_ERR)     //ctrl c
			perror("error");
		if(signal(SIGQUIT, sig_handler) == SIG_ERR)     //ctrl
			perror("error");
		ret = get_input(param);
		if (!strcmp(param->str, ""))
			continue;
		add_history(param->str);
		check_quotes(param->str,0 );
		check_dquotes(param->str, 0);
		//	continue;
		parser2(param);
		//break;
		//parser(param);
        //execute(param);
	}
    //free_param(param);
    //free(param);
    //free(param->str);
    //return (0);
}