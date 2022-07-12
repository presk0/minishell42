/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:17:07 by supersko          #+#    #+#             */
/*   Updated: 2022/07/04 14:41:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (++len);
}

static char	*my_loc(int len)
{
	char	*ret;

	ret = (char *) malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	return (ret);
}

static void	make_str(int *n, char *n_str, int i)
{
	while (i--)
	{
		*(n_str + i) = (char)(*n % 10) + '0';
		*n /= 10;
	}
}

static char	*carry_negative(int *n, char *n_strn, int *len)
{
	if (*n < 0)
	{
		*(n_strn++) = '-';
		(*len)--;
		*n *= -1;
	}
	return (n_strn);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ret;
	char	*num;

	len = ft_intlen(n);
	ret = my_loc(len);
	if (!ret)
		return (NULL);
	num = ret;
	if (n == -2147483648)
	{
		ft_strlcpy(ret, "-2147483648", 12);
		return (ret);
	}
	num = carry_negative(&n, num, &len);
	make_str(&n, num, len);
	return (ret);
}

/*
//
#include <stdio.h>
// MAIN
int main(void)
{
	char	*strnb;

	strnb = ft_itoa(-123);
	fprintf(stderr, "%s\n", strnb);
	free(strnb);

	strnb = ft_itoa(-0);
	fprintf(stderr, "%s\n", strnb);
	free(strnb);

	strnb = ft_itoa(1230);
	fprintf(stderr, "%s\n", strnb);
	free(strnb);
}
*/
