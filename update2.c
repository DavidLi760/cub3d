/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:51:20 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 18:51:29 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_view(t_var *var)
{
	if ((var->pitch2 <= -1 || var->up_pressed == 1) && var->pitch >= -1500)
		var->pitch += -50;
	if (var->left_pressed == 1)
	{
		var->angle += -0.15;
	}
	if ((var->pitch2 >= 1 || var->down_pressed == 1) && var->pitch <= 1500)
	{
		var->pitch += 50;
	}
	if (var->right_pressed == 1)
	{
		var->angle += 0.15;
	}
	if (var->angle > 2 * PI)
		var->angle = 0;
	else if (var->angle < 0)
		var->angle = 2 * PI;
	if (var->pitch >= 1500)
		var->pitch = 1500;
	if (var->pitch <= -1500)
		var->pitch = -1500;
	var->directx = cos(var->angle);
	var->directy = sin(var->angle);
}

void	update_pos(t_var *var)
{
	if (var->posx >= var->position2.x + 1)
		var->position2.x += 1;
	if (var->posx <= var->position2.x - 1)
		var->position2.x -= 1;
	if (var->posy >= var->position2.y + 1)
		var->position2.y += 1;
	if (var->posy <= var->position2.y - 1)
		var->position2.y -= 1;
}

void	death_update(t_var *var)
{
	if (var->iscp < 10 && var->closet2 < 3)
		var->died++;
	if (var->iru < 50 && var->closet2 < 3)
		var->died++;
	if (var->idavli < 10 && var->final == 5)
		var->died++;
	if (var->died == 1)
	{
		var->deathx = var->posx;
		var->deathy = var->posy;
	}
	if (var->died && var->iscp < 15)
	{
		var->angle = var->anglescp;
		var->pitch = -500;
		var->posx = var->deathx;
		var->posy = var->deathy;
	}
}

void	death_animation(t_var *var)
{
	if (var->died && var->iru < 60)
	{
		if (var->died > 20)
			my_put_image_to_image2(var, 0, -500, 2000);
		else
			my_put_image_to_image(var, 0, -600, 2000);
	}
	if (var->died && var->idavli < 20)
	{
		my_put_image_to_image2(var, 0, -500, 2000);
		my_put_image_to_image8(var, 0, -600, 2000);
	}
}

void	init_screech(t_var *var)
{
	var->xech = var->posx + 25;
	var->yech = var->posy + 25;
	if (var->shift_pressed && var->energy < 220)
		var->energy += 1;
	else if (var->shift_pressed == 0 && var->energy > 0)
		var->energy -= 2;
	if (var->screech == 0)
	{
		var->xangleech = var->directx;
		var->yangleech = var->directy;
	}
	var->xech = var->posx - var->xangleech * 25;
	var->yech = var->posy - var->yangleech * 25;
	if (fmod(var->posy, 2.0) > 1.0 && var->highech == 0)
		var->highech = 1;
	if (fmod(var->posy, 2.0) <= 1.0 && var->highech == 0)
		var->highech = 2;
}
