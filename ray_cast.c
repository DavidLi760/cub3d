/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:26:17 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 19:26:22 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    closet_animation(t_var *var, int x, int i)
{
	while (x < 1920)
	{
		if (var->closet2 > 3)
		{
			i = 0;
			if (x < var->closet2 * 30 || x > 1920 - var->closet2 * 30)
			{
				while (i < 1010)
				{
					my_pixel_put2(var, x, i, 0x351713);
					my_pixel_put2(var, x + 1, i++, 0x351713);
				}
			}
		}
		x += 2;
	}
}

void    ray_manager(t_var *var)
{
		var->pixel += 2;
		var->no = 0;
		var->so = 0;
		var->we = 0;
		var->ea = 0;
		var->vide = 0;
		var->ru2 = 0;
}