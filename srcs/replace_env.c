#include "minishell.h"

//void	replace_env(char **str, )



void	check_doll(char *str)
{
	int i;
	int quote;
	int dollar;
	i = 0;
	quote = 0;
	dollar = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			quote = 1;
		if (str[i] == '$')
				dollar = 1;
		i++;
	}
	if (dollar == 1 && quote == 0)
		printf("remplace dollar");
}