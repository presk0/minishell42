#include "minishell.h"

char    **new_env(char **envp, int i) // new env apres unset
{
    char **new;
    int j;
    int len = 0;
    int k = 0;
    //printf("debut new env\n");

    while(envp[len])
    {
        len++;

    }

    //printf(" len = %d", len);
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
    {
        //printf("new[%d] = %s\n", k, new[k]);
        k++;
    }
    free(envp);
    return (new);
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	if (!(cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1))))
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
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