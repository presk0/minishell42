/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_atoi(const char *str0)
{
	int			sign;
	long int	nbr;
	char		*str;

	if (!str0)
		return (0);
	sign = 1;
	str = (char *)str0;
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
	}
	return (sign * nbr);
}

/*
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// MAIN
int	main(void)
{
	char *nb;

	nb = malloc(50);
	strcpy(nb, "2147483647");
	if (atoi(nb) != ft_atoi(nb))
	{
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi(%s) = %d\n", nb, ft_atoi(nb));
		free(nb);
	}
	strcpy(nb, " 	-2147483648");
	if (atoi(nb) != ft_atoi(nb))
	{
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi(%s) = %d\n", nb, ft_atoi(nb));
		free(nb);
	}
	strcpy(nb, " 	-0aa");
	if (atoi(nb) != ft_atoi(nb))
	{
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi(%s) = %d\n", nb, ft_atoi(nb));
		free(nb);
	}
	strcpy(nb, "");
	if (atoi(nb) != ft_atoi(nb))
	{
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi(%s) = %d\n", nb, ft_atoi(nb));
		free(nb);
	}
	strcpy(nb, "   -0002365s654");
	if (atoi(nb) != ft_atoi(nb))
	{
		fprintf(stderr, "atoi(%s) = %d\n", nb, atoi(nb));
		fprintf(stderr, "ft_atoi(%s) = %d\n", nb, ft_atoi(nb));
		free(nb);
	}
	fprintf(stderr, "All tested\n");
	fprintf(stderr, "All tested\n");
	free(nb);
	return (0);
}
*/
