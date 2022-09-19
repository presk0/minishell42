/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_//printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:54:04 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:42:54 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_is_flag(char c)
{
	char	flags[20];
	int		ii;

	ii = 0;
	ft_strlcpy(flags, "csidupxX%", 20);
	while (flags[ii])
		if (c == flags[ii++])
			return (1);
	return (0);
}

size_t	printing_loop(char *str, va_list *ap)
{
	size_t	len_str;
	size_t	len_str_written;
	int		is_flag;

	len_str_written = 0;
	while (*str)
	{
		is_flag = ft_is_flag(*(str + 1));
		if (*str == '%' && is_flag)
		{
			str++;
			len_str_written += ft_print_arg(ap, str);
			str++;
		}
		else if (*str == '%' && !is_flag)
			str++;
		else
		{
			len_str = ft_strlen_char(str, '%');
			len_str_written += write(1, str, len_str);
			str += len_str;
		}
	}
	return (len_str_written);
}

int	ft_printf(const char *str0, ...)
{
	va_list			ap;
	char			*str;
	size_t			len_str_written;

	str = (char *) str0;
	va_start(ap, str0);
	len_str_written = printing_loop(str, &ap);
	va_end(ap);
	return (len_str_written);
}

/*
//
// MAIN
int main(void)
{
	int strlen;

	strlen = ft_//printf("a%ia\n", 42);
	f//printf(stderr, "strlen: %d\n", strlen);
	ft_//printf("\n");

	f//printf(stderr, "%d\n", f//printf(stderr, "%d, %p0000\n", 10, &strlen));
	f//printf(stderr, "%d\n", ft_//printf("%d, %p0000\n", 10, &strlen));
	f//printf(stderr, "retour de //printf: %d\n", f//printf(stderr, " %i %i %i %i %i %i %i\n",  NULL,
	LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42));
	f//printf(stderr, "retour de //printf: %d\n", ft_//printf(" %i %i %i %i %i %i %i\n", NULL,
	LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42));
	f//printf(stderr, "retour de //printf: %d\n", ft_//printf("%x\n", -42));
	f//printf(stderr, "retour de //printf: %d\n", f//printf(stderr, "%x\n", -42));
	f//printf(stderr, "(//printf    : %d)", f//printf(stderr, "%c", '0'));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", ft_//printf("%c", '0'));
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf(" %c ", '0'));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, " %c ", '0'));
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf(" %c", '0' - 256)); 
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, " %c", '0' - 256)); 
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf("%c ", '0' + 256));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, "%c ", '0' + 256));
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf(" %c %c %c ", '0', 0, '1'));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, " %c %c %c ", '0', 0, '1'));
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf(" %c %c %c ", ' ', ' ', ' '));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, " %c %c %c ", ' ', ' ', ' '));
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf(" %c %c %c ", '1', '2', '3'));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, " %c %c %c ", '1', '2', '3'));
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf(" %c %c %c ", '2', '1', 0));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, " %c %c %c ", '2', '1', 0));
	f//printf(stderr, "\n");
	f//printf(stderr, "\n");
	f//printf(stderr, "(//printf    : %d)", ft_//printf(" %c %c %c ", 0, '1', '2'));
	f//printf(stderr, "\n");
	f//printf(stderr, "(ft_//printf : %d)", f//printf(stderr, " %c %c %c ", 0, '1', '2'));
}
	*/
