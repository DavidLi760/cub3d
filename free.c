/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:57:17 by davli             #+#    #+#             */
/*   Updated: 2024/09/04 17:57:29 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_list(t_var *var)
{
    int i;

    i = 0;
    while (var->split[i])
        free(var->split[i++]);
    free(var->split);
    i = 0;
    free(var->file);
    free(var->map);
    free(var->element);
    mlx_destroy_image(var->mlx, var->img);
    mlx_destroy_display(var->mlx);
    free(var->mlx);

}
