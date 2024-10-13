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

int	close_win(t_var *var)
{
	if (var->win)
	{
		mlx_destroy_window(var->mlx, var->win);
		free_list(var);
	}
	exit(0);
	return (0);
}

void	move(int keycode, t_var *var)
{
	if (keycode == W)
		var->w_pressed = 1;
	if (keycode == S)
		var->s_pressed = 1;
	if (keycode == A)
		var->a_pressed = 1;
	if (keycode == D)
		var->d_pressed = 1;
	if (keycode == E)
		var->e_pressed = 1;
	if (keycode == SHIFT)
		var->shift_pressed = 1;
	if (keycode == LEFT)
		var->left_pressed = 1;
	if (keycode == UP)
		var->up_pressed = 1;
	if (keycode == RIGHT)
		var->right_pressed = 1;
	if (keycode == DOWN)
		var->down_pressed = 1;
}

int	mouse_move(int x, int y, t_var *var)
{
	int		d_x = x - (1800);
	int		d_y = y - (900);

	var->pitch2 = 0;
	var->angle += d_x * 0.001;
	var->pitch += d_y * 1;
	if (var->pitch <= -1500)
		var->pitch = -1500;
	if (var->pitch >= 1500)
		var->pitch = 1500;
	return (0);
}

int	escape(int keycode, t_var *var)
{
	if (keycode == 65307)
		close_win(var);
	else if (keycode >= 0 && keycode <= 65508)
		move(keycode, var);
	return (0);
}

int	release(int keycode, t_var *var)
{
	if (keycode == W)
		var->w_pressed = 0;
	if (keycode == S)
		var->s_pressed = 0;
	if (keycode == A)
		var->a_pressed = 0;
	if (keycode == D)
		var->d_pressed = 0;
	if (keycode == E)
		var->e_pressed = 0;
	if (keycode == SHIFT)
		var->shift_pressed = 0;
	if (keycode == LEFT)
		var->left_pressed = 0;
	if (keycode == UP)
		var->up_pressed = 0;
	if (keycode == RIGHT)
		var->right_pressed = 0;
	if (keycode == DOWN)
		var->down_pressed = 0;
	return (0);
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
			my_pixel_put2(var, j++, i, 0);
		i++;
	}
	j = 959;
	while (j <= 961)
	{
		i = 495;
		while (i < 515)
			my_pixel_put2(var, j, i++, 0);
		j++;
	}
}

void	draw_health_bar(t_var *var, int i, int j)
{
	while (i <= 980)
	{
		j = 50;
		while (j <= 250 - var->health)
			my_pixel_put2(var, j++, i, 0x00FF00);
		i++;
	}
}

void	get_text_y(t_var *var, int i, int max)
{
	if (var->no)
		var->text_y = var->heightno * i / max;
	if (var->so)
		var->text_y = var->heightso * i / max;
	if (var->we)
		var->text_y = var->heightwe * i / max;
	if (var->ea)
		var->text_y = var->heightea * i / max;
}

int	mix_color(t_var *var, int now)
{
	int		color;
	float	t;

	t = fmin(var->dist / DIST, 1.0);
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
	// if (var->vide == 1)
	// 	start_y = -1;
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
		if (var->so)
			color = my_pixel_from_texture(var, var->text_x, var->text_y, 's');
		if (var->we)
			color = my_pixel_from_texture(var, var->text_x, var->text_y, 'w');
		if (var->ea)
			color = my_pixel_from_texture(var, var->text_x, var->text_y, 'e');
		if (var->dist < 0)
			var->dist *= -1;
		if (var->door == 1)
			color = my_pixel_from_texture(var, var->text_x, var->text_y, 'd');
		color = mix_color(var, color);
		my_pixel_put2(var, x, start_y, color);
		my_pixel_put2(var, x + 1, start_y, color);
		if (var->ru2 == 1)
		{
			color = my_pixel_from_texture(var, var->ru * 400, var->text_y, 'r');
			perror("color rush\n");
		}
		my_pixel_put2(var, x, start_y, color);
		my_pixel_put2(var, x + 1, start_y, color);
		start_y++;
	}
	while (start_y < 1010)
	{
		my_pixel_put2(var, x, start_y, var->floor);
		my_pixel_put2(var, x + 1, start_y++, var->floor);
	}
	if (var->sprite == 1)
		var->sprite = 2;
	draw_cross(var, 504, 1920);
	draw_health_bar(var, 970, 50);
}

void	get_wall_xy(t_var *var)
{
		var->wall_x = fmod(var->wall_x, 15.00);
		var->wall_y = fmod(var->wall_y, 15.00);
}

void	get_text_x(t_var *var)
{
	if (var->we == 1|| var->ea == 1)
	{
		if (var->we)
			var->text_x = var->widthwe * ((var->wall_y) / 15.00);
		else if (var->ea)
			var->text_x = var->widthea * ((var->wall_y) / 15.00);	
	}
	else if (var->no == 1|| var->so == 1)
	{
		if (var->no)
			var->text_x = var->widthno * ((var->wall_x) / 15.00);
		else if (var->so)
			var->text_x = var->widthso * ((var->wall_x) / 15.00);
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
	else if (var->text_x > 399)
		var->text_x = var->widthno - 2;
	// printf("wallx:%f\n", var->wall_x);
	// printf("wally%f\n", var->wall_y);
	// printf("width:%d\n", var->widthno);
	// printf("text:%f\n", var->text_x);
}

void	trace_ray(t_var *var, double angle, double *i, int no)
{
	if (var->forbidden[(int)(var->posy + sin(angle) * 0 + 5)][(int)(var->posx + cos(angle) * 0 + 5)] == '1')
		return ;
	while ((var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5)] == '0'
	|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5)] == 's')
	&& *i < DIST)
	{
		if (no == 465)
			if (100 + cos(angle) * *i < 150 && 100 + cos(angle) * *i > 0)
				if (100 + sin(angle) * *i < 150 && 100 + sin(angle) * *i > 0)
					my_pixel_put(var, 100 + cos(angle) * *i, 100 + sin(angle) * *i, 0x00FFFFFF);
		if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5)] == 'r')
			var->sprite = 1;
		if (var->forbidden[(int)(var->posy + sin(angle) * ((*i) + 1) + 5)][(int)(var->posx + cos(angle) * ((*i) + 1) + 5)] == '0'
		|| var->forbidden[(int)(var->posy + sin(angle) * ((*i) + 1) + 5)][(int)(var->posx + cos(angle) * ((*i) + 1) + 5)] == 'r')
			*i += 1;
		else
		*i += 0.01;
	}
	if (*i > var->iru && var->ru != 0)
		var->ru2 = 1;
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
	else
		var->door = 0;
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == 's' ||
		var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == 's'
		|| var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == 's')
			var->sprite = 1;
	// if (no == 465)
	// 	printf("%c\n", var->map[(int)var->doory / 15][(int)var->doorx / 15]);
	// printf(" %c\n", var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)]);
	// printf("%c", var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 - 0.01)]);
	// printf(" %c\n", var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)]);
	// printf(" %c\n", var->forbidden[(int)(var->posy + sin(angle) * *i + 5 + 0.01)][(int)(var->posx + cos(angle) * *i + 5)]);
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
	// if (var->door == 1 && var->door2 && var->dist < 30)
	// {
	// 	var->doorx = (var->doorx + var->plusx) / 2;
	// 	var->doory = (var->doory + var->plusy) / 2;
	// }
	// printf("%f\n", (fabs(var->posx - var->plusx) + fabs(var->posy - var->plusy)));
	// printf("door :%f\n", var->door);
	// printf("door2 :%f\n", var->door2);
	// printf("x:%f, ", var->wall_x);
	// printf("y:%f\n", var->wall_y);
	get_wall_xy(var);
	get_text_x(var);
	if (*i >= DIST && var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i) + 5] == '0')
		var->vide = 1;
}

void	ray_casting(t_var *var, int i)
{
	double		start_angle;
	double		distance;
	long long	start;
	int			wall_height;
	int			pixel;

	start = get_time();
	distance = 0;
	pixel = 0;
	start_angle = var->angle - PI / 3 / 2;
	var->rusize = 1000 / var->iru;
	while (i < 960)
	{
		var->ray_angle = start_angle + i * (PI / 3 / 960);
		var->ru = 0;
		var->angledru = (var->angleru + var->iru * 0.001) - (var->angleru - var->iru * 0.001);
		if (var->ray_angle > var->angleru - var->iru * 0.001 && var->ray_angle < var->angleru + var->iru * 0.001)
			var->ru = (var->ray_angle - (var->angleru - var->iru * 0.001)) / var->angledru;
		distance = 0;
		trace_ray(var, var->ray_angle, &distance, i);
		wall_height = 1500 / (distance * cos(var->ray_angle - var->angle) / 15);
		draw_wall_column(var, pixel, wall_height);
		i++;
		pixel += 2;
		var->no = 0;
		var->so = 0;
		var->we = 0;
		var->ea = 0;
		var->vide = 0;
		var->ru2 = 0;
		if (var->sprite == 1)
			var->sprite = 0;
	}
		printf("%f\n", var->iru);
	while (get_time() < start + MS)
		usleep(5);
}

int	update(t_var *var)
{
	var->imag2 = mlx_new_image(var->mlx, 1920, 1920);
	var->addr2 = mlx_get_data_addr(var->imag2, &var->bit2, &var->len2, &var->endian2);
	if (var->w_pressed == 1)
		walking_w(var);
	if (var->s_pressed == 1)
	{
		if (var->forbidden[(int)(var->posy - var->directy) + 5][(int)var->posx + 5] != '0' && var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directx) + 5] == '0')
			var->posx -= var->directx * (var->shift_pressed * 0.5 + 0.25);
		else if (var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directx) + 5] != '0' && var->forbidden[(int)(var->posy - var->directy) + 5][(int)var->posx + 5] == '0')
			var->posy -= var->directy * (var->shift_pressed * 0.5 + 0.25);
		else if (var->forbidden[(int)(var->posy - var->directy) + 5][(int)(var->posx - var->directx) + 5] == '0')
		{
			var->posx -= var->directx * (var->shift_pressed * 0.5 + 0.25);
			var->posy -= var->directy * (var->shift_pressed * 0.5 + 0.25);
		}
	}
	if (var->a_pressed == 1)
	{
		if (var->forbidden[(int)(var->posy - var->directx) + 5][(int)var->posx + 5] != '0' && var->forbidden[(int)var->posy + 5][(int)(var->posx + var->directy) + 5] == '0')
			var->posx += var->directy * (var->shift_pressed * 0.5 + 0.25);
		else if (var->forbidden[(int)var->posy + 5][(int)(var->posx + var->directy) + 5] != '0' && var->forbidden[(int)(var->posy - var->directx) + 5][(int)var->posx + 5] == '0')
			var->posy -= var->directx * (var->shift_pressed * 0.5 + 0.25);
		else if (var->forbidden[(int)(var->posy - var->directx) + 5][(int)(var->posx + var->directy) + 5] == '0')
		{
			var->posx += var->directy * (var->shift_pressed * 0.5 + 0.25);
			var->posy -= var->directx * (var->shift_pressed * 0.5 + 0.25);
		}
	}
	if (var->d_pressed == 1)
	{
		if (var->forbidden[(int)(var->posy + var->directx) + 5][(int)var->posx + 5] != '0' && var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directy) + 5] == '0')
			var->posx -= var->directy * (var->shift_pressed * 0.5 + 0.25);
		else if (var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directy) + 5] != '0' && var->forbidden[(int)(var->posy + var->directx) + 5][(int)var->posx + 5] == '0')
			var->posy += var->directx * (var->shift_pressed * 0.5 + 0.25);
		else if (var->forbidden[(int)(var->posy + var->directx) + 5][(int)(var->posx - var->directy) + 5] == '0')
		{
			var->posx -= var->directy * (var->shift_pressed * 0.5 + 0.25);
			var->posy += var->directx * (var->shift_pressed * 0.5 + 0.25);
		}
	}
	if ((var->pitch2 <= -1 || var->up_pressed == 1) && var->pitch >= -1500)
	{
		var->pitch += -50;
	}
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
	var->delay = 0;
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
	if (var->posx >= var->position2.x + 1)
		var->position2.x += 1;
	if (var->posx <= var->position2.x - 1)
		var->position2.x -= 1;
	if (var->posy >= var->position2.y + 1)
		var->position2.y += 1;
	if (var->posy <= var->position2.y - 1)
		var->position2.y -= 1;
	minimap(var, -1, 0);
	if (var->iru < DIST)
	{
		var->angleru = atan2((var->yru - var->posy) / var->iru, (var->xru - var->posx) / var->iru);
	}
	ray_casting(var, 0);
	var->no = 0;
	var->so = 0;
	var->we = 0;
	var->ea = 0;
	var->vide = 0;
	var->iru = (fabs(var->xru - var->posx) + fabs(var->yru - var->posy));
	mlx_mouse_move(var->mlx, var->win, 1800, 900);
	init_forbidden(var, 0, 0);
	mlx_put_image_to_window(var->mlx, var->win, var->imag2, 0, 0);
	mlx_put_image_to_window(var->mlx, var->win, var->imag, -50, -50);
	mlx_destroy_image(var->mlx, var->imag2);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 49, 49);
	if (var->door2 == 1 && (var->map[(int)var->doory / 15][(int)var->doorx / 15] == '2' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '3' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '6'))
		mlx_string_put(var->mlx, var->win, 940, 750, 0x00FF0000, "Press E !");
	if (var->door2 == 1 && var->e_pressed == 1 && (var->map[(int)var->doory / 15][(int)var->doorx / 15] == '2' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '3'))
		var->door2 = 2;
	if (var->door2 == 1 && var->e_pressed == 1 && (var->map[(int)var->doory / 15][(int)var->doorx / 15] == '6') && var->doortime2 < 17)
	{
		var->door3 = 1;
		var->door2 = 0;
	}
	if (var->door2 == 2)
		var->doortime += 1;
	if (var->door3 == 1)
		var->doortime2 += 1;
	if (var->doortime > 16 && var->door2 == 2)
	{
		var->door2 = 0;
		var->doortime = 0;
	}
	if (var->doortime2 > 16 && var->door3 == 1)
		var->door3 = 0;
	if (var->door3 == 0 && var->e_pressed == 1 && var->map[(int)var->doory / 15][(int)var->doorx / 15] == '6' && var->doortime2 == 17)
	{
		var->door3 = 2;
		var->door2 = 0;
	}
	if (var->door3 == 2 && var->doortime2 > 0)
		var->doortime2 -= 1;
	if (var->doortime2 == 0 && var->door3 == 2)
		var->door3 = 0;
	if (var->door2 == 2 && var->doortime == 1 && var->map[(int)var->doory / 15][(int)var->doorx / 15] == '2')
		var->map[(int)var->doory / 15][(int)var->doorx / 15] = '4';
	else if (var->door2 == 2 && var->doortime == 1 && var->map[(int)var->doory / 15][(int)var->doorx / 15] == '3')
		var->map[(int)var->doory / 15][(int)var->doorx / 15] = '5';
	if (var->door2 == 1)
		var->door2 = 0;
	return (0);
}

void	forbidden_helper5(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	if (c == 'r')
	{
		k = 0;
		while (++k < 16)
		{
			l = 0;
			while (++l < 16)
			{
				if (l == 8 && k == 8)
					var->xru = j + l;
				if (l == 8 && k == 8)
					var->yru = i + k;
				var->forbidden[i + k][j + l] = '0';
			}
		}
	}
}

void	forbidden_helper4(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	if (c == '6')
	{
		k = 8;
		while (++k < 10)
		{
			l = 1;
			while (l < 16 - var->doortime2)
				var->forbidden[i + k][j + l++] = '2';
			while (++l < 16)
				var->forbidden[i + k][j + l] = '0';
		}
	}
}

void	forbidden_helper3(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	if (c == '4')
	{
		k = 8;
		while (++k < 10)
		{
			l = 0;
			while (l < 16 - var->doortime)
				l++;
			while (++l < 16)
				var->forbidden[i + k][j + l] = '0';
		}
	}
	else if (c == '5')
	{
		k = 0;
		while (k < 15 - var->doortime)
			k++;
		while (++k < 16)
		{
			l = 4;
			while (++l < 6)
				var->forbidden[i + k][j + l] = '0';
		}
	}
}

void	forbidden_helper2(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	if (c == '2')
	{
		k = 8;
		while (++k < 10)
		{
			l = -1;
			while (++l < 16)
				var->forbidden[i + k][j + l] = c;
		}
	}
	else if (c == '3')
	{
		k = -1;
		while (++k < 16)
		{
			l = 4;
			while (++l < 6)
				var->forbidden[i + k][j + l] = c;
		}
	}
}

void	forbidden_helper(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	k = 0;
	while (k < 16)
	{
		l = 0;
		while (l < 16)
		{
			var->forbidden[i + k][j + l] = c;
			l++;
		}
		k++;
	}
}

void	init_forbidden(t_var *var, int i, int j)
{
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == '1')
				forbidden_helper(var, i * 15, j * 15, '1');
			if (var->map[i][j] == '2')
				forbidden_helper2(var, i * 15, j * 15, '2');
			if (var->map[i][j] == '3')
				forbidden_helper2(var, i * 15, j * 15, '3');
			if (var->map[i][j] == '4')
				forbidden_helper3(var, i * 15, j * 15, '4');
			if (var->map[i][j] == '5')
				forbidden_helper3(var, i * 15, j * 15, '5');
			if (var->map[i][j] == '6')
				forbidden_helper4(var, i * 15, j * 15, '6');
			if (var->map[i][j] == 'r')
				forbidden_helper5(var, i * 15, j * 15, 'r');
			j++;
		}
		i++;
	}
}

int	init_var(t_var *var, int i, int j)
{
	var->forbidden = malloc(sizeof(char *) * (MAP_SIZE + 1));
	if (!var->forbidden)
		return (free4(var, 0, 0), 0);
	while (++i < MAP_SIZE)
	{
		j = 0;
		var->forbidden[i] = malloc(sizeof(char) * (MAP_SIZE + 1));
		if (!var->forbidden[i])
			return (free4(var, i, 0), 0);
		while (j <= MAP_SIZE)
		{
			var->forbidden[i][j] = '0';
			j++;
		}
	}
	var->forbidden[i] = 0;
	init_forbidden(var, 0, 0);
	var->position.x = var->position2.x / 15;
	var->position.y = var->position2.y / 15;
	return (1);
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	var.delay = 0;
	var.maximum = sqrt(pow(960, 2) + pow(505, 2));
	var.height = 5;
	var.width = 5;
	var.floor = -1;
	var.ceiling = -1;
	var.wall_x = 0;
	var.wall_y = 0;
	var.door = 0;
	var.door2 = 0;
	var.door3 = 0;
	var.doorx = 0;
	var.doory = 0;
	var.sprite = 0;
	var.doortime = 0;
	var.doortime2 = 0;
	var.doorsense = 0;
	var.e_pressed = 0;
	var.w_pressed = 0;
	var.s_pressed = 0;
	var.a_pressed = 0;
	var.d_pressed = 0;
	var.up_pressed = 0;
	var.down_pressed = 0;
	var.left_pressed = 0;
	var.right_pressed = 0;
	var.shift_pressed = 0;
	var.vide = 0;
	var.health = 0;
	var.directx = 0;
	var.directy = 0;
	var.plusx = 0;
	var.plusy = 0;
	var.pitch = 0;
	var.pitch2 = 0;
	var.angle = 0;
	var.text_x = 0;
	var.text_y = 0;
	var.north = 0;
	var.south = 0;
	var.east = 0;
	var.west = 0;
	var.no = 0;
	var.so = 0;
	var.we = 0;
	var.ea = 0;
	var.xru = 0;
	var.yru = 0;
	var.iru = 0;
	var.angleru = 0;
	var.ru2 = 0;
	if (argc != 2)
		return (0);
	if (!check_arg(&var, argv))
		return (0);
	if (!init_var(&var, -1, 0))
		return (0);
	var.posx = var.position2.x;
	var.posy = var.position2.y;
	var.mlx = mlx_init();
	if (!var.mlx)
		return (0);
	var.win = mlx_new_window(var.mlx, 1920, 1010, "cub3d");
	var.img = mlx_xpm_file_to_image(var.mlx, "./xpms/Red_dot.xpm", &var.height, &var.width);
	if (!var.img)
		return (0);
	var.imgd = mlx_xpm_file_to_image(var.mlx, "./xpms/Door.xpm", &var.height1, &var.width1);
	if (!var.imgd)
		return (0);
	var.imgru1 = mlx_xpm_file_to_image(var.mlx, "./xpms/Rush1.xpm", &var.heightru1, &var.widthru1);
	if (!var.imgru1)
		return (0);
	var.imgru2 = mlx_xpm_file_to_image(var.mlx, "./xpms/Rush2.xpm", &var.heightru2, &var.widthru2);
	if (!var.imgru2)
		return (0);
	var.addrd = mlx_get_data_addr(var.imgd, &var.bitd, &var.lend, &var.endiand);
	var.imag = mlx_new_image(var.mlx, 150, 150);
	var.addr = mlx_get_data_addr(var.imag, &var.bit, &var.len, &var.endian);
	var.addrru1 = mlx_get_data_addr(var.imgru1, &var.bitru1, &var.lenru1, &var.endianru1);
	var.addrru2 = mlx_get_data_addr(var.imgru2, &var.bitru2, &var.lenru2, &var.endianru2);
	var.imgno = mlx_xpm_file_to_image(var.mlx, var.north, &var.heightno, &var.widthno);
	var.imgso = mlx_xpm_file_to_image(var.mlx, var.south, &var.heightso, &var.widthso);
	var.imgwe = mlx_xpm_file_to_image(var.mlx, var.west, &var.heightwe, &var.widthwe);
	var.imgea = mlx_xpm_file_to_image(var.mlx, var.east, &var.heightea, &var.widthea);
	var.addrno = mlx_get_data_addr(var.imgno, &var.bitno, &var.lenno, &var.endianno);
	var.addrso = mlx_get_data_addr(var.imgso, &var.bitso, &var.lenso, &var.endianso);
	var.addrwe = mlx_get_data_addr(var.imgwe, &var.bitwe, &var.lenwe, &var.endianwe);
	var.addrea = mlx_get_data_addr(var.imgea, &var.bitea, &var.lenea, &var.endianea);
	i = 0;
	while (var.element[i])
		printf("%s\n", var.element[i++]);
	i = 0;
	while (var.map[i])
		printf("%s\n", var.map[i++]);
	mlx_mouse_move(var.mlx, var.win, 1800, 900);
	printf("0x%X,", var.floor);
	printf("0x%X,", var.ceiling);
	// int	j = 0;
	// while (i < MAP_SIZE)
	// {
	// 	j = 0;
	// 	while (j < MAP_SIZE)
	// 		printf("%c", var.forbidden[i][j++]);
	// 	i++;
	// }
	// printf("x : %d, y : %d\n", var.position.x, var.position.y);
	mlx_hook(var.win, 2, 1L << 0, escape, &var);
	mlx_hook(var.win, 6, 1L << 6, mouse_move, &var);
	mlx_hook(var.win, 3, 1L << 1, release, &var);
	mlx_hook(var.win, 17, 0, close_win, &var);
	mlx_loop_hook(var.mlx, update, &var);
	mlx_loop(var.mlx);
}
