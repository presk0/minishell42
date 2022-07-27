#include "minishell.h"


void	execute2(t_data *param, int i)
{


    (void)i;
    fprintf(stderr, "enrtree execute2\n");
    cmd_spilt_sw(param);
    printf(" param->argc = %d\n", param->argc);
    printf(" param->argv[0] = %s\n", param->argv[0]);
    printf(" param->argv[1] = %s\n", param->argv[1]);
    //printf(" param->argv[2] = %s\n", param->argv[2]);
    //printf(" param->argv[3] = %s\n", param->argv[3]);
    //check_built(1, param);
    if(check_built(1, param))
        check_bin(1, param);
    ft_free_split(param->argv);
    //exit (0);



}


char	**cmd_format2(char *str, char **envp)
{
    int 	i;
    int 	new_i;
    char	**cmd_split;

    str = convert_var_in_line(str, envp );
    cmd_split = quotes_spaces_split(str);
    if (!cmd_split)
        return (NULL);
    new_i = 0;
    i = 0;
    while (cmd_split[i])
    {
        if (*cmd_split[i] != '\0')
        {
            if (i != new_i)
                cmd_split[new_i] = cmd_split[i];
            new_i++;
        }
        else
            free(cmd_split[i]);
        i++;
    }
    cmd_split[new_i] = NULL;
    print_matrix("cmd split", cmd_split);
    //free(cmd_split[0]);
    return (cmd_split);
}



char **cmd_spilt_sw(t_data *param)
{
    int i;
    char **argv;

    i = 0;
    argv = cmd_format2(param->input_cleaned, param->envp);
    param->argv = argv;

    while (param->argv[i])
    {
        i++;
    }
    param->argc = i;

    return(param->argv);


}

int check_built(int fd, t_data *param)
{
    char	*pwd;
    char 	*path;
    char 	cwd[4097];
    printf("check bultin\n");

    if (!ft_memcmp(param->argv[0], "echo", 5))
    {
        printf(" test echo ok \n");
        run_echo(fd, param);
    }
    else if (!ft_memcmp(param->argv[0], "cd", 3))
    {

        if(!param->argv[1] )
            path = ft_strdup("~");
        else
            path = ft_strdup(param->argv[1]);
        cd_command(param);
        if (path && !ft_strncmp(path, "-", 2))

            ft_putstr_fd(getcwd(cwd, 4096), fd);
        //write(1, "\n", 1);
        free(path);
    }
////return (run_cd(args));
    else if (!ft_memcmp(param->argv[0], "unset", 6))
        run_unset(param);
//    else if (!ft_memcmp(param->argv[0], "export", 7)) {
//
//        run_export(param);
//    }
//        return (run_export(args));
    else if (!ft_memcmp(param->argv[0], "exit", 5))
        run_exit(param);
    else if (!ft_memcmp(param->argv[0], "pwd", 4))
    {
        pwd = getcwd(NULL, 0);
        ft_putstr_fd(pwd, fd);
        free(pwd);
        ft_putchar_fd('\n', fd);
        return (1);
    }
    else if (!ft_memcmp(param->argv[0], "env", 4))
        run_env(param, fd);

    else if (!ft_memcmp(param->argv[0], "$?", 3))
        error(param);
//    else if (!ft_memcmp(param->argv[0], "<<", 3))
//        heredoc(param);
    else
        return (1);
        //printf("non connu\n");

    return (0);
}

void	run_echo(int fd, t_data *param)
{	int i = 0;
    printf("run echo ok\n");
    printf("argc = %d\n", param->argc);
    if (param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3))
        i = 1;
    while(i++ < param->argc)
    {
        ft_putstr_fd(param->argv[i], fd);
        if (i < param->argc - 1 && ft_strlen(param->argv[i + 1]))
            write(fd, " ", 1);
    }
    //write(fd, "\n", 1);


    if(!(param->argc > 1 && !ft_memcmp(param->argv[1], "-n", 3)))
        write(fd, "\n", 1);

}


void		run_exit(t_data *param)
{

    printf("lancement exit\n");
    int i;

    if (param->argc > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        param->retour = 1;
    }
    else
    {
        i = 0;
        while (param->argc > 1 && ft_isdigit(param->argv[1][i]))
            i++;
        if (param->argc > 1 && param->argv[1][i])
        {
            ft_putstr_fd("minishell: exit: : numeric argument required\n", 2);
            param->retour = 2;
        }
        if( param->argc > 1 && param->retour != 2)
            i = ft_atoi(param->argv[1]);
        else
            i = param->retour;
        //free_param(param);
        exit(i);
    }
}
static void	change_dir(char *path, t_data *param)
{
    char		cwd[4097];
    char		oldpwd[4097];

    getcwd(oldpwd, 4096);
    if (chdir(path) == 0)
    {
        param->argc = 4;
        ft_free_split(param->argv);
        param->argv = (char **)ft_calloc(sizeof(char *), 4);
        param->argv[0] = ft_strdup("export");
        param->argv[1] = ft_strdup("OLDPWD=");
        param->argv[2] = ft_strdup(oldpwd);
        param->envp = export_command(param, 1);
        ft_free_split(param->argv);
        param->argv = (char **)ft_calloc(sizeof(char *), 4);
        param->argv[0] = ft_strdup("export");
        param->argv[1] = ft_strdup("PWD=");
        param->argv[2] = ft_strdup(getcwd(cwd, 4096));
        param->envp = export_command(param, 1);
    }
    else
        ft_putstr_fd("minishell: cd: error", 2);
}

void		cd_command(t_data *param)
{
    char *path;

    errno = 0;
    if (param->argc <= 2)
    {
        if (!param->argv[1] || !ft_strncmp(param->argv[1], "--", 3) ||
            !ft_strncmp(param->argv[1], "~", 2))
            path = get_env(param->envp, "HOME");
        else if (!ft_strncmp(param->argv[1], "-", 2))
            path = get_env(param->envp, "OLDPWD");
        else
            path = param->argv[1];
        change_dir(path, param);
        if (errno > 0)
        {
            ft_putstr_fd(strerror(errno), 2);
            param->retour = 1;
        }
    }
    else
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        param->retour= 1;
    }
    errno = 0;
}
char     **run_unset(t_data *param) {


    int i = 0;
    int j;
    char *env;
    if(param->argc < 2 )
        return(param->envp);
    env = param->argv[1];
    j = ft_strlen(env);
    while (param->envp) {
        if (!ft_memcmp(env, param->envp[i], j)) {
            param->envp = new_env(param->envp, i);
            break;
        } else

            i++;
    }
    return(param->envp);
}
char		**export_command(t_data *param, int j)
{
    int		i;
    char	**cpy;

    i = 0;
    while (param->envp[i] && ft_memcmp(param->envp[i],
                                       param->argv[j], ft_strlen(param->argv[j])))
        i++;
    if (!param->envp[i])
    {
        cpy = copy_env(param->envp, 1);
        cpy[i] = ft_strjoin(param->argv[j], param->argv[j + 1]);
        ft_free_split(param->envp);
    }
    else
    {
        cpy = param->envp;
        free(param->envp[i]);
        param->envp[i] = ft_strjoin(param->argv[j], param->argv[j + 1]);
    }
    return (cpy);
}

void	run_env(t_data *param, int fd)
{
    int i;
    i = 0;
    if (param->argc != 1) {
        ft_putstr_fd(" env : permission denied\n", 2);
        param->retour = 126;
        return;
    }
    while (param->envp[i]) {
        ft_putstr_fd(param->envp[i], fd);
        write(1, "\n", fd);
        i++;
    }
}

//char    **run_export(t_data *param)
//{
//    char **env;
//    env = param->envp;
//    if (param->argv[1] == NULL)
//        print_env_tri(param);
//
//    else {
//        printf("param->argv[1] = %s\n", param->argv[1]);
//        printf("param->export[0] = %s\n", param->export[0]);
//        if (!(ft_memcmp(param->argv[1], param->export[0], 2)))
//            printf("test export ok\n");
//    }
//    return(env);
//
//
//}
void	error(t_data *param) {

    if (param->argc > 0 && !ft_memcmp(param->argv[0], "$?", 3))
        printf("%d\n", param->retour);

}