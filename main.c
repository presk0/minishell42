/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 13:04:29 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	sig_handler(int sig)
{
	(void)sig;
	//printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
*/

/*
char	*ft_strldup(const char *s, int len)
{
	char	*ptr;
	int		size;
	int		i;

	if (!s)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	if (len < size)
		size = len;
	if (!(ptr = (char *)malloc(sizeof(char) * (size + 1)))	)
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
*/

/*
void	ft_qsplit(char *input, char *sep)
{
	int			i;
	char		is_quoted;
	char		*split_left;
	char		*split_right;

	if(!input)
		return ;

	// if no sep
	i = 0;
	ft_is_quoted(NULL, 0);
	while (input[i])
	{
		is_quoted = ft_is_quoted(input, i);
		if (!is_quoted && !ft_inputncmp(&input[i], sep, ft_strlen(sep)))
		{
			split_left = ft_substr(input, 0, i);
			split_right = ft_substr(input, i + ft_strlen(sep), ft_strlen(input));
			//free(input);
			//input = NULL;
			//break;
		}
		i++;
	}
}
*/

/*
void	parser(t_data *param)
{
	param->cmds = ft_split_mini(param->input, '|');
}
*/
//extern void	rl_replace_line(const char *text, int clear_undo);

/*
void	    ctrlbacksl(int sig) {

    (void)sig;
    //    int pid = 0;
//
//    pid = get_pid();
//    //printf("pid= %d\n", pid);
//
//    if (kill(pid, SIGKILL) != -1) {
//    //printf("^\\Quit: %d\n", sig);
//
//    }
//    else

    //exit(0);
    ft_putendl_fd("", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
*/

/*
void	ctrlc(int sig)
{
	(void)sig;


    ft_putendl_fd("", 1);
    rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
*/

int main(int argc, char **argv, char **envp)
{
    t_data  *param;
	char	**matrix;
	char	**sep;
	char	*str;
	int		pid;
	(void)pid;
	(void)str;
	(void)matrix;
	(void)sep;
    (void)argc;
    (void)argv;

    struct termios  tmp;
	(void)tmp;


   

	param = init_param(envp);

	matrix = NULL;




/*
 	tcgetattr(0, &tmp);

    tmp.c_lflag &= ~ECHOCTL;
    tmp.c_lflag |= ECHO;
    tcgetattr(0, &param->save);
    tcsetattr(0, 0, &tmp);
	signal(SIGINT, ctrlc);
    signal(SIGQUIT, ctrlbacksl);
	*/
    while(42)
	{

    // Configure readline to auto-complete paths when the tab key is hit.
//    rl_bind_key('\t', rl_complete);

		if (!get_input(param))
			break;
		if (!strcmp(param->input, ""))
			continue;
		else
			add_history(param->input);
		//printf(stderr, "[main] param_input : %s\n", param->input);
		if(check_error(param))
			return (-1);
		
		//pid = fork();
		//if (pid == 0)
		//{
			parser(param);
		//	exit(0);
		//}
		//else
		//	wait(NULL);
		////printf("%s\n", ((return_env_var("PATH", param->envp))));
		//param->envp = ft_append_tab(param->envp, param->input);
		////printf("conv_var_in_line: %s\n", convert_var_in_line(param->input, envp));
		////printf("-------------------------------------------------------------\n");
	}
	//freall();
	exit(param->retour);
}
