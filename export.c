/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swalter <swalter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:03:16 by swalter           #+#    #+#             */
/*   Updated: 2022/08/16 12:48:19 by swalter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  #include "minishell.h"
  
  static char **tri_env(t_data *param)
{
    char **tableau;
    int i;
    char *temp;
    tableau = param->envp;
    i = 0;
    while(tableau[i] && tableau[i + 1]) {


        if (strcmp(tableau[i], tableau[i + 1]) > 0) {
            temp = tableau[i];
            tableau[i] = tableau[i + 1];
            tableau[i + 1] = temp;
            i = -1;
        }
        i++;
    }

    return(tableau);
}

void    print_env_tri(t_data *param)
{
    int i;
    i = 0;
    char **tabl;

    tabl = tri_env(param);


    while(tabl[i] != NULL)
    {
        //printf("declare -x ");
        //printf("%s\n", tabl[i]);
        i++;

    }

}