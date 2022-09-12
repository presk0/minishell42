/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:13:11 by supersko          #+#    #+#             */
/*   Updated: 2022/07/24 12:19:09 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char ***tab)
{
	int	i;

	if (*tab)
	{
		i = 0;
		while ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i++] = NULL;
		}
		free(*tab);
		*tab = NULL;
	}
}
