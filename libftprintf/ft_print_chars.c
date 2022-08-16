/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:23:22 by supersko          #+#    #+#             */
/*   Updated: 2022/08/16 13:02:01 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_print_str(char *str)
{
	size_t	len_str;

	if (!str)
		return (write(1, "(null)", 6));
	len_str = ft_strlen_char(str, '\0');
	if (!len_str)
		return (0);
	write(1, str, len_str);
	return (len_str);
}

size_t	ft_print_char(char c)
{
	return (write(1, &c, 1));
}
