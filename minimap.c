/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:55:33 by davli             #+#    #+#             */
/*   Updated: 2024/10/27 19:04:14 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	obstacle_helper(t_var *var, int i, int j)
{
    if (var->map[i][j] == '1')
		draw_wall(var, var->diff_x + 95, var->diff_y \
        + 95, 0x000000FF);
	else if (var->map[i][j] == '2')
		draw_door(var, var->diff_x + 95, var->diff_y + 95, 1);
	else if (var->map[i][j] == '3')
		draw_door(var, var->diff_x + 95, var->diff_y + 95, 0);
	else
		draw_wall(var, var->diff_x + 95, var->diff_y \
        + 95, 0x00000000);
}

void	draw_obstacle(t_var *var, int i, int j)
{
	while (i <= var->position.y + 3)
	{
		var->diff_y = i * 15 - var->position2.y;
		j = var->position.x - 3;
		while (j <= var->position.x + 3)
		{
			var->diff_x = j * 15 - var->position2.x;
			if (j < 0 || i < 0)
				draw_wall(var, var->diff_x + 95, var->diff_y + 95, 0x00000000);
			else
			{
				if (i < var->max && j < var->maxj)
				{
                    obstacle_helper(var, x, i);
				}
				else
					draw_wall(var, var->diff_x + 95, var->diff_y \
                    + 95, 0x00000000);	
			}
			j++;
		}
		i++;
	}
}

void	minimap(t_var *var, int i, int j)
{
	(void)i;
	(void)j;
	var->position.x = var->position2.x / 15;
	var->position.y = var->position2.y / 15;
	draw_obstacle(var, var->position.y - 3, var->position.x - 3);
	while (++i < 7)
	{
		j = -1;
		if (i == 0 || i == 6)
		{
			while (++j < 7)
				draw_block(var, i, j, 0x00FFFFFF);
		}
		else
		{
			while (++j < 7)
			{
				if (j == 0)
					draw_block(var, i, j, 0x00FFFFFF);
				if (j == 6)
					draw_block(var, i, j, 0x00FFFFFF);
			}
		}
	}
}
