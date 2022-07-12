#include "minishell.h"

int    heredoc(t_data *param, int i)
{
    int fd;
    char *input;
    int len;

    fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0666);
    input = readline("heredoc>");
    if(!input)
        return (0);
    len = ft_strlen(param->argv[i + 1]);

    while(1)
    {

        if(!ft_memcmp(input, param->argv[i + 1], len + 1))
           break;
        ft_putstr_fd(input, fd);
        write(fd, "\n", 1);
        input = readline("heredoc>");
    }
    return (fd);
}
