/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:44:16 by davli             #+#    #+#             */
/*   Updated: 2024/10/29 11:49:38 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_put_image_to_image6(t_var *var, int x, int y, int size)
{
	int	color;
	int	i;
	int	j;

	var->scale_factor = 400.0 / size;
	i = -1;
	while (++i < size && i < 2000)
	{
		j = -1;
		while (++j < size && j < 1920)
		{
			var->srcx = (int)(j * var->scale_factor);
			var->srcy = (int)(i * var->scale_factor);
			if (var->srcx < 1796 && var->srcy < 1010)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 'D');
				if (x + j < 1920 && y + i < 1010 && x + j > 0
					&& y + i > 0 && color != 0xFFFFFF)
					if (var->i[(x + j)] > var->idavli)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}

void	my_put_image_to_image7(t_var *var, int x, int y, int size)
{
	int	color;
	int	i;
	int	j;

	var->scale_factor = 400.0 / size;
	i = -1;
	while (++i < size && i < 2000)
	{
		j = -1;
		while (++j < size && j < 1920)
		{
			var->srcx = (int)(j * var->scale_factor);
			var->srcy = (int)(i * var->scale_factor);
			if (var->srcx < 1796 && var->srcy < 1010)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 'U');
				if (x + j < 1920 && y + i < 1010 && x + j > 0
					&& y + i > 0 && color != 0xFFFFFF)
					if (var->i[(x + j)] > var->iuser)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}

void	my_put_image_to_image8(t_var *var, int x, int y, int size)
{
	int	color;
	int	i;
	int	j;

	var->scale_factor = 400.0 / size;
	i = -1;
	while (++i < size && i < 2000)
	{
		j = -1;
		while (++j < size && j < 1920)
		{
			var->srcx = (int)(j * var->scale_factor);
			var->srcy = (int)(i * var->scale_factor);
			if (var->srcx < 1796 && var->srcy < 1010)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 'A');
				if (x + j < 1920 && y + i < 1010 && x + j > 0
					&& y + i > 0 && color != 0xFFFFFF)
					if (var->i[(x + j)] > var->idavli)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}
