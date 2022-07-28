#include "minishell.h"

int verif_bultin(t_data *param)
{
    if (!ft_memcmp("echo", param->input_cleaned, 4))
        return(1);
    else if (!ft_memcmp(param->input_cleaned,"pwd", 4))
        return(1);






    else
        return (0);

}
