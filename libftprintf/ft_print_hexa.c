/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:23:22 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 12:58:51 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_recursive_print_hexa(long long unsigned int num,
		size_t *len, char CASE)
{
	if (num < 10)
	{
		num += '0';
		*len += write(1, &num, 1);
	}
	else if (num < 16 && CASE == 'M')
	{
		num += 'A' - 10;
		*len += write(1, &num, 1);
	}
	else if (num < 16 && CASE == 'm')
	{
		num += 'a' - 10;
		*len += write(1, &num, 1);
	}
	else
	{
		ft_recursive_print_hexa(num / 16, len, CASE);
		ft_recursive_print_hexa(num % 16, len, CASE);
	}
}

size_t	ft_print_hexa(long long unsigned int num, char CASE)
{
	size_t	len;

	len = 0;
	ft_recursive_print_hexa((long long unsigned int) num, &len, CASE);
	return (len);
}

void	ft_recursive_print_addr(long long unsigned int num, size_t *len)
{
	if (num < 10)
	{
		num += '0';
		*len += write(1, &num, 1);
	}
	else if (num < 16)
	{
		num += 'a' - 10;
		*len += write(1, &num, 1);
	}
	else
	{
		ft_recursive_print_addr(num / 16, len);
		ft_recursive_print_addr(num % 16, len);
	}
}

size_t	ft_print_addr(void *num)
{
	size_t	len;

	len = 0;
	len += write(1, "0x", 2);
	ft_recursive_print_addr((long long unsigned int) num, &len);
	return (len);
}
