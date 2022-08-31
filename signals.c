#include "minishell.h"

static void	process(int sign_num)
{
	if (!kill(g_pid, sign_num))
	{
		if (sign_num == SIGQUIT)      // cttl \ ok
		{
			
            ft_putstr_fd("^\\Quit: 3\n", 1);
           	rl_on_new_line();
			rl_replace_line("", 0);
            rl_redisplay();

		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putendl_fd("", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
	}
}

void		sigint_handler(int sign_num)
{
	
    if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_pid != 0)
		process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			ft_putendl_fd("", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
		}
		else if (sign_num == SIGQUIT)
		{
        	//ft_putstr_fd("\b\b  \b\b", 1);
            ft_putendl_fd("", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
        } 
	}
}