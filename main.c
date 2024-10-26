/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:05:58 by davli             #+#    #+#             */
/*   Updated: 2024/09/14 16:26:57 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
					if (var->map[i][j] == '1')
						draw_wall(var, var->diff_x + 95, var->diff_y + 95, 0x000000FF);
					else if (var->map[i][j] == '2')
						draw_door(var, var->diff_x + 95, var->diff_y + 95, 1);
					else if (var->map[i][j] == '3')
						draw_door(var, var->diff_x + 95, var->diff_y + 95, 0);
					else
						draw_wall(var, var->diff_x + 95, var->diff_y + 95, 0x00000000);
				}
				else
					draw_wall(var, var->diff_x + 95, var->diff_y + 95, 0x00000000);	
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

int	is_a_wall(t_var *var, int i, int j)
{
	int	k;
	int	l;

	k = i + 4;
	l = j + 4;
	while (k <= i + 5)
	{
		l = j + 4;
		while (l <= j + 5)
		{
			if (var->map[k / 15][l / 15] == '1' || var->map[k / 15][l / 15] == '2')
				return (1);
			l++;
		}
		k++;
	}
	return (0);
}

void	draw_cross(t_var *var, int i, int j)
{
	while (i <= 506)
	{
		j = 950;
		while (j <= 970)
			my_pixel_put2(var, j++, i, 0x999999);
		i++;
	}
	j = 959;
	while (j <= 961)
	{
		i = 495;
		while (i < 515)
			my_pixel_put2(var, j, i++, 0x999999);
		j++;
	}
}

void	draw_health_bar(t_var *var, int i, int j)
{
	while (i <= 960)
	{
		j = 50;
		while (j <= 250)
			my_pixel_put2(var, j++, i, 0x999999);
		i++;
	}
	i = 950;
	while (i <= 960)
	{
		j = 50;
		while (j <= 250 - var->health)
			my_pixel_put2(var, j++, i, 0x00FF00);
		i++;
	}
}

void	draw_energy_bar(t_var *var, int i, int j)
{
	while (i <= 980)
	{
		j = 50;
		while (j <= 250)
			my_pixel_put2(var, j++, i, 0x999999);
		i++;
	}
	i = 970;
	while (i <= 980)
	{
		j = 50;
		while (j <= 250 - var->energy)
			my_pixel_put2(var, j++, i, 0x0055FF);
		i++;
	}
}

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

int	mix_f_c(t_var *var, int x, int y, int now)
{
	int		color;
	float	t;
	
	var->maximum = sqrt(pow(960, 2) + pow(505 - var->pitch, 2));
	t = sqrt(pow(x - 960, 2) + pow(y - 505 + var->pitch, 2));
	t = 1.0 - (t / var->maximum);
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

void	get_wall_xy(t_var *var)
{
		var->wall_x = fmod(var->wall_x, 15.00);
		var->wall_y = fmod(var->wall_y, 15.00);
}

void	get_text_x(t_var *var)
{
	if (var->we == 1 || var->ea == 1)
	{
		if (var->we)
			var->text_x = var->widthwe * ((var->wall_y) / 15.00);
		else if (var->ea)
			var->text_x = var->widthea * ((var->wall_y) / 15.00);	
		if (var->door || var->closet)
			var->text_x = 400 * ((var->wall_y) / 15.00);
	}
	else if (var->no == 1 || var->so == 1)
	{
		if (var->no)
			var->text_x = var->widthno * ((var->wall_x) / 15.00);
		else if (var->so)
			var->text_x = var->widthso * ((var->wall_x) / 15.00);
		if (var->door || var->closet)
			var->text_x = 400 * ((var->wall_x) / 15.00);
	}
	if (var->door && (var->map[(int)var->plusy / 15][(int)var->plusx / 15] == '2' || var->map[(int)var->plusy / 15][(int)var->plusx / 15] == '3'))
		var->text_x = var->text_x;
	else if (var->door && var->map[(int)var->plusy / 15][(int)var->plusx / 15] == '6' && var->door3 == 2)
		var->text_x += var->doortime2 * 28;
	else if (var->door && var->map[(int)var->plusy / 15][(int)var->plusx / 15] == '6' && var->doortime2 * 28 - 84 >= 0 && var->doortime2 * 28 - 84 <= 400)
		var->text_x += var->doortime2 * 28 - 84;
	else if (var->door && (var->map[(int)var->plusy / 15][(int)var->plusx / 15] == '4' || var->map[(int)var->plusy / 15][(int)var->plusx / 15] == '5') && var->doortime * 28 - 84 >= 0)
		var->text_x += var->doortime * 28 - 84;
	if (var->text_x < 0)
		var->text_x = 0;
}

void	trace_ray(t_var *var, double angle, double *i, int no)
{
	if (var->forbidden[(int)(var->posy + sin(angle) * 0 + 5)][(int)(var->posx + cos(angle) * 0 + 5)] == '1')
		return ;
	while ((var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5)] == '0'
	|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5)] == 's')
	&& *i < var->distance)
	{
		if (100 + cos(angle) * *i < 150 && 100 + cos(angle) * *i > 0)
			if (100 + sin(angle) * *i < 150 && 100 + sin(angle) * *i > 0)
				my_pixel_put(var, 100 + cos(angle) * *i, 100 + sin(angle) * *i, 0x00FFFFFF);
		if (var->forbidden[(int)(var->posy + sin(angle) * ((*i) + 1) + 5)][(int)(var->posx + cos(angle) * ((*i) + 1) + 5)] == '0'
		|| var->forbidden[(int)(var->posy + sin(angle) * ((*i) + 1) + 5)][(int)(var->posx + cos(angle) * ((*i) + 1) + 5)] == 'r')
			*i += 1;
		else
		*i += 0.01;
	}
	var->i[no * 2] = *i;
	var->i[no * 2 + 1] = *i;
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '0')
		var->no = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 - 0.01)] == '0')
		var->we = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '0')
		var->ea = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5 + 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '0')
		var->so = 1;
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '2' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '2'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '2')
		{
			var->door = 1;
		}
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '3' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '3'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '3')
			var->door = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '6' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '6'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '6')
			var->door = 1;
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == 'r' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == 'r'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == 'r')
			var->door = 1;
	else
		var->door = 0;
	var->closet = 0;
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == 'p' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == 'p'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == 'p')
			var->closet = 1;
	var->wall_x = var->posx + cos(angle) * *i + 5;
	var->wall_y = var->posy + sin(angle) * *i + 5;
	var->plusx = var->posx + cos(angle) * *i + 5;
	var->plusy = var->posy + sin(angle) * *i + 5;
	var->dist = sqrt(pow(var->posx - var->plusx, 2) + pow(var->posy - var->plusy, 2));
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
	get_wall_xy(var);
	get_text_x(var);
	if (*i >= var->distance && var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i) + 5] == '0')
		var->vide = 1;
}

void	ray_casting(t_var *var, int i)
{
	var->left_angle = var->angle - PI / 3 / 2;
	var->pixel = 0;
	while (i < 960)
	{
		var->ray_angle = var->left_angle + i * (PI / 3 / 960);
		var->dst = 0;
	    trace_ray(var, var->ray_angle, &var->dst, i);
		var->wall_height = 1500 / (var->dst * cos(var->ray_angle - var->angle) / 15);
		draw_wall_column(var, var->pixel, var->wall_height);
		ray_manager(var);
		i++;
	}
	var->right_angle = var->ray_angle;
	sprite_order(var);
    if (var->angledavli >= 0)
		print_boss(var);
	if (var->angleuser >= 0)
		print_boss2(var);
	closet_animation(var, 0, 0);
	draw_cross(var, 504, 1920);
	draw_health_bar(var, 950, 50);
	draw_energy_bar(var, 970, 50);
}

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 2)
		return (0);
	init_all(&var, 0);
	if (!check_arg(&var, argv))
		return (0);
	if (!init_var(&var, -1, 0))
		return (0);
	var.mlx = mlx_init();
	if (!var.mlx)
		return (0);
	var.win = mlx_new_window(var.mlx, 1920, 1010, "cub3d");
	if (!var.win)
		return (0);
	if (!init_all(&var, 1))
		return (0);
	mlx_mouse_move(var.mlx, var.win, 1800, 900);
	mlx_hook(var.win, 2, 1L << 0, press_key, &var);
	mlx_hook(var.win, 6, 1L << 6, mouse_move, &var);
	mlx_hook(var.win, 3, 1L << 1, release, &var);
	mlx_hook(var.win, 17, 0, close_win, &var);
	mlx_loop_hook(var.mlx, update, &var);
	mlx_loop(var.mlx);
}
