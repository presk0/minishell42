#include "minishell.h"

char    **new_env(char **envp, int i)
{
    char **new;
    int j;
    int len = 0;
    int k = 0;

    while(envp[len])
        len++;
    new = ft_calloc(sizeof(char *),(len));
    j = 0;
    while(j < i)
    {
        new[j] = ft_strdup(envp[j]);
        j++;
    }
    i++;
    while(envp[i])
    {
        new[j] = ft_strdup(envp[i]);
        i++;
        j++;
    }
    while(new[k])
        k++;
    free(envp);
    return (new);
}

char	*get_env(char **envp, char *env)
{
	int		i;
	int		len;
	char	*tmp;

	env = ft_strjoin(env, "=");
	len = ft_strlen(env);
	i = 0;
	while (envp[i] && ft_memcmp(env, envp[i], len))
		i++;
	if (envp[i])
		tmp = envp[i] + len;
	else
		tmp = 0;
	free(env);
	return (tmp);
}