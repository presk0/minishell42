#include "minishell.h"

int verif_bultin(t_data *param)
{
    if (!ft_memcmp("echo", param->input_cleaned, 4))
        return(1);
    else if (!ft_memcmp(param->input_cleaned,"pwd", 4))
        return(1);
    else if (!ft_memcmp(param->input_cleaned,"export", 6))      
        return(1);
    else if (!ft_memcmp(param->input_cleaned,"env", 4))
        return(1);
    else if (!ft_memcmp(param->input_cleaned,"unset", 5))
        return (1);
    else if (!ft_strncmp("cd", param->input_cleaned, 2))
        return (1);
    else
        return (0);
}
