/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:13:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return error if the arg is not an int
static int	ft_isspace(const char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

static long int	c_to_i(char c)
{
	return ((long int) c - (long int) '0');
}

int	ft_atoi_err(char *str)
{
	int			sign;
	long int	nbr;

	if (!str)
		return (0);
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	nbr = 0;
	while (ft_isdigit(*str))
	{
		nbr *= 10;
		nbr += (long int) c_to_i(*str++);
		if (nbr > 2147483647)
			error_msg("[ft_atoi_err] not int value");
	}
	return (sign * nbr);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	main(void)
{
	char *nb;

	nb = malloc(50);
	strcpy(nb, "2147483647");
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi_err(%s) = %d\n", nb, ft_atoi_err(nb));
	strcpy(nb, " 	-2147483648");
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi_err(%s) = %d\n", nb, ft_atoi_err(nb));
	strcpy(nb, " 	-0aa");
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi_err(%s) = %d\n", nb, ft_atoi_err(nb));
	strcpy(nb, "");
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi_err(%s) = %d\n", nb, ft_atoi_err(nb));
	strcpy(nb, "   -000999999999999999999999999992365s654");
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi_err(%s) = %d\n", nb, ft_atoi_err(nb));
	fprintf(stderr, "All tested\n");
	free(nb);
	return (0);
}
*/
