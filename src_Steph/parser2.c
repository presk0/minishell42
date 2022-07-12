#include "minishell.h"
static int	change_env(int i, char **str, t_data *param)
{
	int		len;
	char	*bef;
	char	*aft;
	char	*env;
	char	*aux;


	len = (ft_strlen_char(*str + i + 1, ':') < ft_strlen_env(*str + i + 1)) ?
		  ft_strlen_char(*str + i + 1, ':') + 1 :
		  ft_strlen_env(*str + i + 1) + 1 ;
	bef = ft_strldup(*str, i);
	aux = ft_strldup(*str + i + 1 , len - 1);
	env = (!ft_memcmp(aux, "?", 2)) ? ft_itoa(param->retour) : 0;
	aft = ft_strdup(*str + i + len);
	env = (!env) ? ft_strdup(get_env(param->envp, aux)) : env;
	free(aux);
	len = ft_strlen(env);
	aux = ft_strjoin(bef, env);
	free(bef);
	free(env);
	free(*str);
	*str = ft_strjoin(aux, aft);
	free(aux);
	free(aft);
	return (len);
}

int	check_error(t_data *param)
{
	int i;
	i = 0;
    while(param->str[i] != '\0')
	{
		if(param->str[i] == ';' || (param->str[i] == '|' && param->str[i + 1] == '|') || (param->str[i] == '&' && param->str[i + 1] == '&'  ))
		{
			ft_putstr_fd("-minishell; error arg ; || &&\n", 2);
			param->retour = 2;
			free(param->str);
			param->str = 0;
			return (1);
		}	
		i++;
	}
	return (0);
}


static int	check_env(char **str, t_data *param)
{
	int i;
	//int braces;

	i = 0;

	while ((*str) && (*str)[i])
	{
		if ((*str)[i] == '\''  && check_quotes(*str, i))
			return (1);
		if ((*str)[i] && (*str)[i] == '\\')
		{
			if ((*str)[i + 1] == '$')
				rm_char(str, i);
			if ((*str)[i + 1])
				i++;
		}
		else if ((*str)[i] == '$' && !(!(*str)[i + 1] ||
									   ft_isspace((*str)[i + 1]) || (*str)[i + 1] == '\'' ||
									   (*str)[i + 1] == '"' || (*str)[i + 1] == '/'))
			i += change_env(i, str, param) - 1;

		i++;
	}
	return (0);
}

void	check_command(t_data *param)
{
	int fd;
	fd = set_fd(param);
	copy_args1(param);
	if(check_built(fd, param))
		check_bin(fd, param);
}



void		parser2(t_data *param)
{
	int i;
    int j = 0;

	if (check_error(param))
		return ;
	param->cmds = ft_split_mini(param->str, '|');
	i = 0;
	while (param->cmds[i])
	{

		check_env(&(param->cmds[i]), param);
		param->argc = count_args(param->cmds[i]);
		param->argv = (char **)ft_calloc(sizeof(char *), (param->argc + 1));
		set_args(param->argv, param->cmds[i], param->argc);
        printf("argv = %s\n", param->argv[0]);
        param->export = check_export(param);
        check_command(param);
		free_matrix(param->argv);
		i++;
	}
	free(param->str);
	param->str = 0;
	free_matrix(param->cmds);
}


