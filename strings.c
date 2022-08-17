/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2022/08/17 09:29:22 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_blank(char c)
{
    if (c == ' ' || c == '\n' || c == '\t')
        return (1);
    else
        return (0);
}

void    del_first_word(char **str)
{
    int     i;
    char    *new_str;
    int     is_quoted;

    new_str = NULL;
    i = 0;
    ft_is_quoted(NULL, 0);
    if (str && (*str))
    {
        while (is_blank((*str)[i]) && (*str)[i])
            i++;
        is_quoted = ft_is_quoted((*str), i);
        while ((!is_blank((*str)[i]) || is_quoted) && (*str)[i])
        {
            i++;
            is_quoted = ft_is_quoted((*str), i);
        }
        while (is_blank((*str)[i]) && (*str)[i])
            i++;
        new_str = ft_substr((*str), i, ft_strlen(*str));
    }
    free(*str);
    *str = new_str;
}

char    *return_first_word(char *str)
{
    int     start;
    int     end;
    char    *new_str;
    int     is_quoted;

    new_str = NULL;
    start = 0;
    if (str)
    {
        while (str[start] && is_blank(str[start]))
            start++;
        end = start;
        is_quoted = ft_is_quoted(str, end);
        while ((!is_blank(str[end]) || is_quoted) && str[end])
        {
            //fprintf(stderr, "[return_first_wd] is_quoted:%d\n", is_quoted);
            end++;
            is_quoted = ft_is_quoted(str, end);
        }
        new_str = ft_substr(str, start, end - start);
    }
    return (new_str);
}

char    *pop_first_wd(char **cmd)
{
    char *first_word;

    first_word = NULL;
    if (cmd)
    {
        first_word = return_first_word(*cmd);
        del_first_word(cmd);
    }
    return (first_word);
}

/* modify cmd in_place 
char **pop_item(char **cmd, char *operand)
{
    char    *str;
    int     ope_len;
    int     found;
    int     i;

    i = ft_strlen(*cmd);
    ope_len = ft_strlen(operand);
    found = 0;
    while (--i)
    {
        if (!ft_strncmp(*cmd[i], operand, ope_len) && !(found++))
        {
            str = pop(cmd, i, )
        }
    }
}
*/