#include "minishell.h"

//export
//argv[1]  arguments export
//
//test=test
//
char    **check_export(t_data *param)
{
    int i = 0;
    int len = 0;
    int j = 0;
    int k = 0;
    char **export;
    len = ft_strlen(param->argv[0]);
    export = ft_calloc(sizeof(char *), len + 1);
    if(param->export != NULL) {
        while (param->export[k])
            k++;
    }
    if(param->argv[0][len - 1] == '=')
    {



        while(param->argv[j]) {


            export[k] = ft_strdup(param->argv[j]);
            j++;
            k++;
        }
    }
    else
        //printf("pas trouve\n");

    return(export);



}

//void    run_export(t_data *param)
char    **new_env_export(char *str, char **envp) // new env apres unset
{
    char **new;
    int j;
    int len = 0;
    int k = 0;
    char *export;
    export = str;
    //printf(" export arg = %s\n", export);
    while(envp[len])
    {
        len++;

    }

    new = ft_calloc(sizeof(char *),(len) + 1);
    //printf("len = %d\n", len);
    j = 0;
    while(j <= len)
    {
        new[j] = ft_strdup(envp[j]);
        j++;
    }
    new[j + 1] = ft_strdup(export);

    while(new[k])
    {
        //printf("new[%d] = %s\n", k, new[k]);
        k++;
    }


    free(envp);
    return (new);
}

