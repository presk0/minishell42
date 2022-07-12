/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 16:31:37 by supersko          #+#    #+#             */
/*   Updated: 2022/06/18 17:15:59 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Function: int rl_redisplay ()
//Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
//
//Function: int rl_on_new_line ()
//Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 

void	store_and_free(char *line_read)
{
	if (line_read && *line_read)
	add_history (line_read);

  	if (line_read)
	{
		free (line_read);
		line_read = (char *)NULL;
    }
}
