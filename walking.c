/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:19:29 by davli             #+#    #+#             */
/*   Updated: 2024/10/10 18:19:30 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	walking_w(t_var *var)
{
	if (var->w_pressed == 1)
	{
		if (var->w_pressed == 1 && \
		var->forbidden[(int)(var->posy + var->directy) \
		+ 5][(int)var->posx + 5] != '0' &&
		(var->forbidden[(int)var->posy \
		+ 5][(int)(var->posx + var->directx) + 5] == '0'))
			var->posx += var->directx * \
			(0.5 + (var->shift_pressed && var->energy < 190) * 0.5);
		else if (var->w_pressed == 1 && \
		(var->forbidden[(int)var->posy \
		+ 5][(int)(var->posx + var->directx) + 5] != '0')
		&& (var->forbidden[(int)(var->posy + var->directy) \
		+ 5][(int)var->posx + 5] == '0'))
			var->posy += var->directy * (0.5 \
			+ (var->shift_pressed && var->energy < 190) * 0.5);
		else if (var->forbidden[(int)(var->posy + var->directy) \
		+ 5][(int)(var->posx + var->directx) + 5] == '0')
		{
			var->posx += var->directx * (0.5 \
			+ (var->shift_pressed && var->energy < 190) * 0.5);
			var->posy += var->directy * (0.5 \
			+ (var->shift_pressed && var->energy < 190) * 0.5);
		}
	}
}

void	walking_s(t_var *var)
{
	if (var->s_pressed == 1)
	{
		if (var->forbidden[(int)(var->posy - var->directy) \
		+ 5][(int)var->posx + 5] != '0' && var->forbidden[(int)var->posy \
		+ 5][(int)(var->posx - var->directx) + 5] == '0')
			var->posx -= var->directx * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		else if (var->forbidden[(int)var->posy + 5][(int)(var->posx \
		- var->directx) + 5] != '0' && var->forbidden[(int)(var->posy \
		- var->directy) + 5][(int)var->posx + 5] == '0')
			var->posy -= var->directy * (0.5 + (var->shift_pressed && \
			var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		else if (var->forbidden[(int)(var->posy - var->directy) \
		+ 5][(int)(var->posx - var->directx) + 5] == '0')
		{
			var->posx -= var->directx * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			var->posy -= var->directy * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		}
	}
}

void	walking_a(t_var *var)
{
	if (var->a_pressed == 1)
	{
		if (var->forbidden[(int)(var->posy - var->directx) + 5][(int)var->posx \
		+ 5] != '0' && var->forbidden[(int)var->posy + 5][(int)(var->posx \
		+ var->directy) + 5] == '0')
			var->posx += var->directy * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		else if (var->forbidden[(int)var->posy + 5][(int)(var->posx \
		+ var->directy) + 5] != '0' && var->forbidden[(int)(var->posy \
		- var->directx) + 5][(int)var->posx + 5] == '0')
			var->posy -= var->directx * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		else if (var->forbidden[(int)(var->posy - var->directx) \
		+ 5][(int)(var->posx + var->directy) + 5] == '0')
		{
			var->posx += var->directy * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			var->posy -= var->directx * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		}
	}
}

void	walking_d(t_var *var)
{
	if (var->d_pressed == 1)
	{
		if (var->forbidden[(int)(var->posy + var->directx) + 5][(int)var->posx \
		+ 5] != '0' && var->forbidden[(int)var->posy \
		+ 5][(int)(var->posx - var->directy) + 5] == '0')
			var->posx -= var->directy * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		else if (var->forbidden[(int)var->posy + 5][(int)(var->posx \
		- var->directy) + 5] != '0' && var->forbidden[(int)(var->posy \
		+ var->directx) + 5][(int)var->posx + 5] == '0')
			var->posy += var->directx * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		else if (var->forbidden[(int)(var->posy + var->directx) \
		+ 5][(int)(var->posx - var->directy) + 5] == '0')
		{
			var->posx -= var->directy * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			var->posy += var->directx * (0.5 + (var->shift_pressed \
			&& var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
		}
	}
}
