/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:21:58 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 20:22:04 by davli            ###   ########.fr       */
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
	int r1 = color >> 16 & 0xFF;
	int	g1 = color >> 8 & 0xFF;
	int	b1 = (color & 0xFF);
	int	r2 = 0x000000 >> 16 & 0xFF;
	int	g2 = 0x000000 >> 8 & 0xFF;
	int	b2 = 0x000000 & 0xFF;
	int	r = (int)((1 - (t)) * r1 + t * r2);
	int	g = (int)((1 - (t)) * g1 + t * g2);
	int	b = (int)((1 - (t)) * b1 + t * b2);

	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	draw_wall_column(t_var *var, int x, int height)
{
	int	i;
	int start_y;
	int	start;
	int end_y;
	int	color;

	i = 0;
	start_y = (HEIGHT - height) / 2 - var->pitch;
	start = start_y;
	end_y = start_y + height;
	while (i < 1010)
	{
		my_pixel_put2(var, x, i, var->ceiling);
		my_pixel_put2(var, x + 1, i++, var->ceiling);
	}
	if (start_y < 0)
		start_y = 0;
	while (var->vide == 1 && start_y < end_y && start_y < 1010)
	{
		my_pixel_put2(var, x, start_y, 0x000000);
		my_pixel_put2(var, x + 1, start_y++, 0x000000);
	}
	while (!var->vide && start_y < end_y && start_y < 1010)
	{
		get_text_y(var, start_y - start, height);
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
		my_pixel_put2(var, x, start_y, color);
		my_pixel_put2(var, x + 1, start_y, color);
		start_y++;
	}
	while (start_y < 1010)
	{
		my_pixel_put2(var, x, start_y, var->floor);
		my_pixel_put2(var, x + 1, start_y++, var->floor);
	}
}
