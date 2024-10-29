/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:00:01 by davli             #+#    #+#             */
/*   Updated: 2024/10/29 11:47:14 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_put_image_to_image(t_var *var, int x, int y, int size)
{
	int	color;
	int	i;
	int	j;

	var->scale_factor = 400.0 / size;
	i = -1;
	while (++i < size && i < 2010)
	{
		j = -1;
		while (++j < size && j < 1920)
		{
			var->srcx = (int)(j * var->scale_factor);
			var->srcy = (int)(i * var->scale_factor);
			if (var->srcx < 400 && var->srcy < 400)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 'r');
				if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0)
					if (var->i[(x + j)] > var->iru || var->died > 0)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}

void	my_put_image_to_image2(t_var *var, int x, int y, int size)
{
	int	color;
	int	i;
	int	j;

	var->scale_factor = 400.0 / size;
	i = -1;
	while (++i < size && i < 2010)
	{
		j = -1;
		while (++j < size && j < 1920)
		{
			var->srcx = (int)(j * var->scale_factor);
			var->srcy = (int)(i * var->scale_factor);
			if (var->srcx < 400 && var->srcy < 400)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 'u');
				if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0)
					if (var->i[(x + j)] > var->iru || var->died > 20)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}

void	my_put_image_to_image3(t_var *var, int x, int y, int size)
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
			if (var->srcx < 400 && var->srcy < 400)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 's');
				if (x + j < 1920 && y + i < 1010 && x + j > 0
					&& y + i > 0 && color != 0xFFFFFF)
					if (var->i[(x + j)] > var->iscp)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}

void	my_put_image_to_image4(t_var *var, int x, int y, int size)
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
			if (var->srcx < 400 && var->srcy < 400)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 'c');
				if (x + j < 1920 && y + i < 1010
					&& x + j > 0 && y + i > 0 && color != 0xFFFFFF)
					if (var->i[(x + j)] > var->iscp || var->iscp < 15)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}

void	my_put_image_to_image5(t_var *var, int x, int y, int size)
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
			if (var->srcx < 400 && var->srcy < 400)
			{
				color = my_pixel_from_texture(var, var->srcx, var->srcy, 'E');
				if (x + j < 1920 && y + i < 1010 && x + j > 0
					&& y + i > 0 && color != 0xFFFFFF)
					if (var->i[(x + j)] * 5 > var->iech && color != 0x0000FF)
						my_pixel_put2(var, x + j, y + i, color);
			}
		}
	}
}
