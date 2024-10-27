/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:21:58 by davli             #+#    #+#             */
/*   Updated: 2024/10/27 18:52:18 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_text_y(t_var *var, int i, int max)
{
	if (var->no)
		var->text_y = var->heightno * i / max;
	else if (var->so)
		var->text_y = var->heightso * i / max;
	else if (var->we)
		var->text_y = var->heightwe * i / max;
	else if (var->ea)
		var->text_y = var->heightea * i / max;
	if (var->door || var->closet)
		var->text_y = 400 * i / max;
}

int	mix_color(t_var *var, int now)
{
	int		color;
	float	t;

	t = fmin(var->dist / var->distance, 1.0);
	color = now;
	var->r1 = color >> 16 & 0xFF;
	var->g1 = color >> 8 & 0xFF;
	var->b1 = (color & 0xFF);
	var->r2 = 0x000000 >> 16 & 0xFF;
	var->g2 = 0x000000 >> 8 & 0xFF;
	var->b2 = 0x000000 & 0xFF;
	var->r = (int)((1 - (t)) * var->r1 + t * var->r2);
	var->g = (int)((1 - (t)) * var->g1 + t * var->g2);
	var->b = (int)((1 - (t)) * var->b1 + t * var->b2);
	color = (var->r << 16) | (var->g << 8) | var->b;
	return (color);
}

void	draw_things(t_var *var, int *start_y, int x)
{
	int	color;

	get_text_y(var, *start_y - var->tmpstart, var->wall_height);
	if (var->no)
		color = my_pixel_from_texture(var, var->text_x, var->text_y, 'n');
	else if (var->so)
		color = my_pixel_from_texture(var, var->text_x, var->text_y, 'S');
	else if (var->we)
		color = my_pixel_from_texture(var, var->text_x, var->text_y, 'w');
	else if (var->ea)
		color = my_pixel_from_texture(var, var->text_x, var->text_y, 'e');
	if (var->dist < 0)
		var->dist *= -1;
	if (var->door == 1)
		color = my_pixel_from_texture(var, var->text_x, var->text_y, 'd');
	if (var->closet == 1)
		color = my_pixel_from_texture(var, var->text_x, var->text_y, 'p');
	color = mix_color(var, color);
	my_pixel_put2(var, x, *start_y, color);
	my_pixel_put2(var, x + 1, *start_y, color);
	*start_y += 1;
}

void	draw_norm(t_var *var, int x, int *start_y, int *i)
{
	while (*i < 1010)
	{
		my_pixel_put2(var, x, *i, var->ceiling);
		my_pixel_put2(var, x + 1, (*i)++, var->ceiling);
	}
	if (*start_y < 0)
		*start_y = 0;
}

void	draw_wall_column(t_var *var, int x, int height)
{
	int	i;
	int	start_y;
	int	end_y;

	i = 0;
	start_y = (HEIGHT - height) / 2 - var->pitch;
	var->tmpstart = start_y;
	end_y = start_y + height;
	draw_norm(var, x, &start_y, &i);
	while (var->vide == 1 && start_y < end_y && start_y < 1010)
	{
		my_pixel_put2(var, x, start_y, 0x000000);
		my_pixel_put2(var, x + 1, start_y++, 0x000000);
	}
	while (!var->vide && start_y < end_y && start_y < 1010)
	{
		draw_things(var, &start_y, x);
	}
	while (start_y < 1010)
	{
		my_pixel_put2(var, x, start_y, var->floor);
		my_pixel_put2(var, x + 1, start_y++, var->floor);
	}
}
