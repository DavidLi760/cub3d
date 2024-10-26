/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:12:39 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 16:12:47 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pos(t_var *var)
{
	var->position.x = var->position2.x / 15;
	var->position.y = var->position2.y / 15;
	var->posx = var->position2.x;
	var->posy = var->position2.y;
}
