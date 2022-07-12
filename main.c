#include "minishell.h"
//
//static void	sig_handler(int sig)
//{
//	(void)sig;
//	printf("\n");
//	rl_on_new_line();
//	//rl_replace_line("", 0);
//	rl_redisplay();
//}

static int	ft_is_quoted(char *c, int i)
{
	static int	squote;
	static int	dquote;

	if (!c)
	{
		squote = 0;
		dquote = 0;
	}
	else
	{
		if (c[i] == '\'' && !dquote) // not_escaped(c, i) && 
			squote = !squote;
		else if (c[i] == '\"' && !squote) // not_escaped(c, i) && 
			dquote = !dquote;
		if (dquote)
			return (2);
		if (squote)
			return (1);
	}
    return (0);
}

static int	check_error(t_data *param)
{
	int i;
	int is_quoted;

	ft_is_quoted(NULL, 0);	
	i = 0;
    while(param->input[i] != '\0')
	{
		is_quoted = ft_is_quoted(param->input, i);
		if(!is_quoted && (param->input[i] == ';' || (param->input[i] == '|' && param->input[i + 1] == '|') || (param->input[i] == '&' && param->input[i + 1] == '&'  )))
		{
			printf("-minishell; error arg ; || &&\n");
			param->retour = 2;
			free(param->input);
			//free_param
			param->input = 0;
			return (1);
		}	
		i++;
	}
	return (0);
}

static char	*ft_strldup(const char *s, int len)
{
	char	*ptr;
	int		size;
	int		i;

	size = 0;
	while (s[size])
		size++;
	size = (len < size) ? len : size;
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

static int	number_input(char *s, char c)
{
	int		n[2];
	char	quote;

	n[0] = -1;
	n[1] = 1;
	while (s[++n[0]])
	{
		if (s[n[0]] == '\\' && (s[n[0] + 1] == '\'' || s[n[0] + 1] == '"' ||
								s[n[0] + 1] == '\\' || s[n[0] + 1] == c))
			n[0]++;
		else if (s[n[0]] == c)
			n[1]++;
		else if (s[n[0]] && (s[n[0]] == '"' || s[n[0]] == '\''))
		{
			quote = s[n[0]++];
			while (s[n[0]] && s[n[0]] != quote)
			{
				if (s[n[0]] == '\\' &&
				(s[n[0] + 1] == quote || s[n[0] + 1] == '\\') && quote == '"')
					n[0]++;
				n[0]++;
			}
		}
	}
	return (n[1]);
}

static int	set_str_len(char *s, char c)
{
	char	quote;
	int		len;

	len = -1;
	while (s[++len] && s[len] != c)
	{
		if (s[len] == '\\' && (s[len + 1] == '\'' || s[len + 1] == '"' ||
		s[len + 1] == '\\' || s[len + 1] == c))
			len++;
		else if (s[len] == '"' || s[len] == '\'')
		{
			quote = s[len++];
			while (s[len] && s[len] != quote)
			{
				if (s[len] == '\\' &&
				(s[len + 1] == quote || s[len + 1] == '\\') && quote == '"')
					len++;
				len++;
			}
		}
	}
	return (len);
}

static void	set_mat(char **mat, char *s, char c, int n)
{
	int i;
	int len;

	i = 0;
	while (i < n)
	{
		len = set_str_len(s, c);
		mat[i] = ft_strldup(s, len);
		s += len + 1;
		i++;
	}
}

char		**ft_split_mini(char *s, char c)
{
	int		n;
	char	**mat;

	if (!s)
		return (NULL);
	n = number_input(s, c);
	if (!(mat = (char **)ft_calloc(sizeof(char *), n + 1)))
		return (NULL);
	set_mat(mat, s, c, n);
	return (mat);
}


int	get_input(t_data *param)
{
	char	*input;
	int		ret;

	ret = 1;
	input = read_multilines("\e[033m42mminishell $ \e[39m");
	if (!input)
		return (0);
	param->input = input;
	return (ret);
}

char	**copy_env(char **envp, int add)
{
	int		len;
	int		i;
	char	**cpy;

	len = 0;
	while (envp[len])
		len++;
	cpy = (char **)ft_calloc(sizeof(char *), (len + add + 1));
	if (!cpy)
		return (0);
	i = -1;
	while (++i < len)
		cpy[i] = ft_strdup(envp[i]);
	return (cpy);
}

t_data	*init_param(char **envp)
{
	t_data	*param;

	param  = (t_data *)malloc(sizeof(t_data));
	param->envp = copy_env(envp, 0);
	param->argv = 0;
	param->argc = 0;
	param->retour = 0;
	//param->var = 0;
	return (param);
}

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

void	parser(t_data *param)
{
	param->cmds = ft_split_mini(param->input, '|');
}

void	print_tab(char **tableau)
{
	int	i = 0;
	printf("------------------------\n");
	while (tableau[i])
	{
		printf("%s*\n", tableau[i++]);
	}
	printf("------------------------\n");
}

int main(int argc, char **argv, char **envp)
{
    t_data  *param;
    (void)argc;
    (void)argv;

	param = init_param(envp);
    while(42)
	{
		get_input(param);
		if(check_error(param))
			return (-1);
		printf("%s\n", param->input);
		//print_tab(ft_split_mini(param->input, '|'));
		free(param->input);
	}
	return (0);
}