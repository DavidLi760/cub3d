/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:21:51 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 18:21:56 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_facing(t_var *var, double angle, double *i)
{
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - \
	0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '0')
		var->no = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + \
	5)][(int)(var->posx + cos(angle) * *i + 5 - 0.01)] == '0')
		var->we = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + \
	5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '0')
		var->ea = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5 + \
	0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '0')
		var->so = 1;
}

void	set_door(t_var *var, double angle, double *i)
{
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + \
	5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '2' ||
			var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - \
		0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '2'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + \
		5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '2')
			var->door = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + \
	5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '3' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - \
		0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '3'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + \
		5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '3')
			var->door = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + \
	5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '6' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - \
		0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '6'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + \
		5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '6')
			var->door = 1;
	else
		var->door = 0;
}

void	set_other(t_var *var, double angle, double *i, int no)
{
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx \
	+ cos(angle) * *i + 5 + 0.01)] == 'p' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - \
		0.01)][(int)(var->posx + cos(angle) * *i + 5)] == 'p'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + \
		5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == 'p')
			var->closet = 1;
	var->wall_x = var->posx + cos(angle) * *i + 5;
	var->wall_y = var->posy + sin(angle) * *i + 5;
	var->plusx = var->posx + cos(angle) * *i + 5;
	var->plusy = var->posy + sin(angle) * *i + 5;
	var->dist = sqrt(pow(var->posx - var->plusx, 2) + pow(var->posy - \
	var->plusy, 2));
	if (var->door == 1 && var->door2 == 0 && var->dist < 30 && no == 465)
	{
		var->door2 = 1;
		var->doorx = var->plusx;
		var->doory = var->plusy;
	}
	if (var->closet == 1 && var->closet2 == 0 && var->dist < 30 && no == 465)
	{
		var->closet2 = 1;
		var->closetx = var->plusx;
		var->closety = var->plusy;
	}
}

void	ray_pixel(t_var *var, double angle, double *i)
{
	if (100 + cos(angle) * *i < 150 && 100 + cos(angle) * *i > 0)
		if (100 + sin(angle) * *i < 150 && 100 + sin(angle) * *i > 0)
			my_pixel_put(var, 100 + cos(angle) * *i, 100 + sin(angle) \
			* *i, 0x00FFFFFF);
	if (var->forbidden[(int)(var->posy + sin(angle) * ((*i) + 1) + \
		5)][(int)(var->posx + cos(angle) * ((*i) + 1) + 5)] == '0'
		|| var->forbidden[(int)(var->posy + sin(angle) * ((*i) + 1) + \
		5)][(int)(var->posx + cos(angle) * ((*i) + 1) + 5)] == 'r')
			*i += 1;
	else
		*i += 0.01;
}

void	trace_ray(t_var *var, double angle, double *i, int no)
{
	if (var->forbidden[(int)(var->posy + sin(angle) * 0 + 5)][(int)(var->posx \
	+ cos(angle) * 0 + 5)] == '1')
		return ;
	while (var->forbidden[(int)(var->posy + sin(angle) * *i \
	+ 5)][(int)(var->posx + cos(angle) * *i + 5)] == '0' && *i < var->distance)
		ray_pixel(var, angle, i);
	var->i[no * 2] = *i;
	var->i[no * 2 + 1] = *i;
	set_facing(var, angle, i);
	set_door(var, angle, i);
	var->closet = 0;
	set_other(var, angle, i, no);
	get_wall_xy(var);
	get_text_x(var);
	door_text(var);
	if (*i >= var->distance && var->forbidden[(int)(var->posy + sin(angle) * \
	*i + 5)][(int)(var->posx + cos(angle) * *i) + 5] == '0')
		var->vide = 1;
}
