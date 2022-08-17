/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cde_bash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:40:10 by swalter           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/16 16:12:56 by swalter          ###   ########.fr       */
=======
/*   Updated: 2022/08/16 10:54:44 by swalter          ###   ########.fr       */
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

<<<<<<< HEAD
static char	*ft_strldup(const char *s, int len)
{
	char	*ptr;
	int		size;
	int		i;

	size = 0;
	while (s[size])
		size++;
	size = (len < size) ? len : size;
	if (!(ptr = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

=======
>>>>>>> d99f63367bfec85cd0167a65469c2abadbea92e0
static void	set_filename(int len, char **new, char *str)
{
    int		i;
    char	*filename;
    char	*aux;

    i = 0;
    while (!ft_memcmp(str + i, "../", 3))
        i += 3;
    filename = ft_strdup(str + i);
    i /= 3;
    while (i-- > 0)
    {
        while ((*new)[len] != '/')
            len--;
        len--;
    }
    aux = ft_strldup(*new, len);
    free(*new);
    *new = ft_strjoin(aux, "/");
    free(aux);
    aux = ft_strjoin(*new, filename);
    free(*new);
    *new = aux;
    free(filename);
}

static void	set_path(char *str, char **path)
{
    int		len;
    char	*new;

    new = ft_strdup(*path);
    len = ft_strlen(*path);
    if (!ft_memcmp(str, "/", 1))
        *path = ft_strdup(str);
    else
    {
        set_filename(len, &new, str);
        *path = new;
        return ;
    }
    free(new);
}    

void	cde_bash(t_data *param)
{
        char	buff[4097];
        char	*path;
        char	*start;

        start = param->argv[0];
        if (ft_memcmp(param->argv[0], "/", 1))
            param->argv[0] += (!ft_memcmp(param->argv[0], "./", 2)) ? 2 : 0;
        path = getcwd(buff, 4096);
        set_path(param->argv[0], &path);
        if (!fork())
        {
            //signal(SIGINT, child_sig_handler_bash);
            if (execve(path, param->argv, param->envp))
            {
                param->retour = 126;
                ft_putstr_fd("pas commande bash valide", 2);
            }
            exit(param->retour);
        }
        else
            wait(&param->retour);
        param->retour /= 256;
        free(path);
        param->argv[0] = start;
}
