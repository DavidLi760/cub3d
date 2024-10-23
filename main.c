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
	if (keycode == M && var->m_pressed == 0)
		var->m_pressed = 1;
	if (keycode == M && var->m_pressed == 2)
		var->m_pressed = 0;
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
	
	if (var->m_pressed == 0)
	{
		var->pitch2 = 0;
		var->angle += d_x * 0.001;
		var->pitch += d_y * 1;
		if (var->pitch <= -1500)
			var->pitch = -1500;
		if (var->pitch >= 1500)
			var->pitch = 1500;
	}
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
	if (keycode == M && var->m_pressed)
		var->m_pressed = 2;
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
		// if (no == 465)
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
	if (var->closet == 1 && var->closet2 == 0 && var->dist < 30 && no == 465)
	{
		var->closet2 = 1;
		var->closetx = var->plusx;
		var->closety = var->plusy;
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
	if (*i >= var->distance && var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i) + 5] == '0')
		var->vide = 1;
}

void	ray_casting(t_var *var, int i)
{
	double		distance;
	int			wall_height;
	int			pixel;
	int			x;

	x = 0;
	distance = 0;
	pixel = 0;
	var->left_angle = var->angle - PI / 3 / 2;
	if (var->left_angle < 0)
		var->left_angle += 2 * PI;
	while (i < 960)
	{
		var->ray_angle = var->left_angle + i * (PI / 3 / 960);
		if (var->ray_angle > 2 * PI)
			var->ray_angle -= (2 * PI);
		var->ru = 0;
		if (var->ray_angle > var->angleru - var->iru * (PI / 3 / 960) && var->ray_angle < var->angleru + var->iru * (PI / 3 / 960))
			var->ru = (var->ray_angle - (var->angleru - var->iru * (PI / 3 / 960))) / var->angledru;
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
	}

	if (var->iru > var->iscp && var->iru > var->iech)
		var->spriteorder[0] = 'r';
	else if (var->iru > var->iech || var->iru > var->iscp)
		var->spriteorder[1] = 'r';
	else
		var->spriteorder[2] = 'r';
	if (var->iscp > var->iru && var->iscp > var->iech)
		var->spriteorder[0] = 's';
	else if (var->iscp > var->iech || var->iscp > var->iru)
		var->spriteorder[1] = 's';
	else
		var->spriteorder[2] = 's';
	if (var->iech > var->iru && var->iech > var->iscp)
		var->spriteorder[0] = 'e';
	else if (var->iech > var->iscp || var->iech > var->iru)
		var->spriteorder[1] = 'e';
	else
		var->spriteorder[2] = 'e';
	var->spriteorder[3] = 0;
	print_monster(var, var->spriteorder);
	if (var->angledavli >= 0)
	{
		var->right_angle = var->ray_angle;
		if (var->right_angle > var->left_angle && var->angledavli > var->left_angle && var->angledavli < var->right_angle)
			var->angleddavli = (var->angledavli - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->right_angle < var->left_angle && var->angledavli > var->right_angle && var->angledavli > var->left_angle)
			var->angleddavli = (var->angledavli - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->right_angle < var->left_angle && var->angledavli < var->right_angle && var->angledavli < var->left_angle)
			var->angleddavli = (var->angledavli + (2 * PI - var->left_angle)) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->left_angle < var->right_angle && var->angledavli > var->left_angle && var->angledavli > var->right_angle)
			var->angleddavli = (var->angledavli - 2 * PI - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle < var->right_angle && var->angledavli < var->left_angle && var->angledavli < var->right_angle)
			var->angleddavli = (var->angledavli - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle > var->right_angle && var->angledavli < var->left_angle && var->angledavli > var->right_angle)
			var->angleddavli = (var->angledavli - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
	}
	var->davlisize = 40000 / (var->idavli * 1.5);
	if (var->angledavli >= 0 && var->final <= 3)
		my_put_image_to_image6(var, var->angleddavli * 1920 - var->davlisize / 1.5, 500 - var->pitch - var->davlisize / 2, var->davlisize);
	else if (var->angledavli >= 0 && var->final > 3)
		my_put_image_to_image8(var, var->angleddavli * 1920 - var->davlisize / 1.5, 500 - var->pitch - var->davlisize / 2, var->davlisize);
	if (var->angleuser >= 0)
	{
		var->right_angle = var->ray_angle;
		if (var->right_angle > var->left_angle && var->angleuser > var->left_angle && var->angleuser < var->right_angle)
			var->angleduser = (var->angleuser - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->right_angle < var->left_angle && var->angleuser > var->right_angle && var->angleuser > var->left_angle)
			var->angleduser = (var->angleuser - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->right_angle < var->left_angle && var->angleuser < var->right_angle && var->angleuser < var->left_angle)
			var->angleduser = (var->angleuser + (2 * PI - var->left_angle)) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->left_angle < var->right_angle && var->angleuser > var->left_angle && var->angleuser > var->right_angle)
			var->angleduser = (var->angleuser - 2 * PI - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle < var->right_angle && var->angleuser < var->left_angle && var->angleuser < var->right_angle)
			var->angleduser = (var->angleuser - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle > var->right_angle && var->angleuser < var->left_angle && var->angleuser > var->right_angle)
			var->angleduser = (var->angleuser - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
	}
	var->usersize = 40000 / (var->iuser * 1.5);
	if (var->angleuser >= 0)
			my_put_image_to_image7(var, var->angleduser * 1920 - var->usersize / 1.5, 500 - var->pitch - var->usersize / 2, var->usersize);
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
	draw_cross(var, 504, 1920);
	draw_health_bar(var, 950, 50);
	draw_energy_bar(var, 970, 50);
}

int	update(t_var *var)
{
	long long	start;

	start = get_time();
	var->imag2 = mlx_new_image(var->mlx, 1920, 1920);
	var->addr2 = mlx_get_data_addr(var->imag2, &var->bit2, &var->len2, &var->endian2);
	if (var->final == 2)
	{
		if (var->w_pressed == 1)
		{
			var->posy += 0.77027027027;
			var->posx += 0.2297297297;
		}
	}
	else
	{
		if (var->w_pressed == 1)
			walking_w(var);
		if (var->s_pressed == 1)
		{
			if (var->forbidden[(int)(var->posy - var->directy) + 5][(int)var->posx + 5] != '0' && var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directx) + 5] == '0')
				var->posx -= var->directx * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			else if (var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directx) + 5] != '0' && var->forbidden[(int)(var->posy - var->directy) + 5][(int)var->posx + 5] == '0')
				var->posy -= var->directy * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			else if (var->forbidden[(int)(var->posy - var->directy) + 5][(int)(var->posx - var->directx) + 5] == '0')
			{
				var->posx -= var->directx * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
				var->posy -= var->directy * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			}
		}
		if (var->a_pressed == 1)
		{
			if (var->forbidden[(int)(var->posy - var->directx) + 5][(int)var->posx + 5] != '0' && var->forbidden[(int)var->posy + 5][(int)(var->posx + var->directy) + 5] == '0')
				var->posx += var->directy * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			else if (var->forbidden[(int)var->posy + 5][(int)(var->posx + var->directy) + 5] != '0' && var->forbidden[(int)(var->posy - var->directx) + 5][(int)var->posx + 5] == '0')
				var->posy -= var->directx * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			else if (var->forbidden[(int)(var->posy - var->directx) + 5][(int)(var->posx + var->directy) + 5] == '0')
			{
				var->posx += var->directy * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
				var->posy -= var->directx * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			}
		}
		if (var->d_pressed == 1)
		{
			if (var->forbidden[(int)(var->posy + var->directx) + 5][(int)var->posx + 5] != '0' && var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directy) + 5] == '0')
				var->posx -= var->directy * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			else if (var->forbidden[(int)var->posy + 5][(int)(var->posx - var->directy) + 5] != '0' && var->forbidden[(int)(var->posy + var->directx) + 5][(int)var->posx + 5] == '0')
				var->posy += var->directx * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			else if (var->forbidden[(int)(var->posy + var->directx) + 5][(int)(var->posx - var->directy) + 5] == '0')
			{
				var->posx -= var->directy * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
				var->posy += var->directx * (0.5 + (var->shift_pressed && var->energy < 190) * 0.5 - 0.25 * var->w_pressed);
			}
		}
	}
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
	var->iru = sqrt(pow(fabs(var->xru - var->posx), 2) + pow(fabs(var->yru - var->posy), 2));
	var->angleru = atan2((var->yru - var->posy), (var->xru - var->posx));
	if (var->angleru < 0)
		var->angleru += 2 * PI;
	if (var->angleru > 2 * PI)
		var->angleru -= 2 * PI;
	if (var->iru > var->distance)
		var->angleru = -1;
	var->iscp = sqrt(pow(fabs(var->xscp - var->posx), 2) + pow(fabs(var->yscp - var->posy), 2));
	var->anglescp = atan2((var->yscp - var->posy), (var->xscp - var->posx));
	if (var->anglescp < 0)
		var->anglescp += 2 * PI;
	if (var->anglescp > 2 * PI)
		var->anglescp -= 2 * PI;
	if (var->iscp > var->distance)
		var->anglescp = -1;
	var->iech = sqrt(pow(fabs(var->xech - var->posx), 2) + pow(fabs(var->yech - var->posy), 2));
	var->angleech = atan2((var->yech - var->posy), (var->xech - var->posx));
	if (var->angleech < 0)
		var->angleech += 2 * PI;
	if (var->angleech > 2 * PI)
		var->angleech -= 2 * PI;
	if (var->iech > var->distance)
		var->angleech = -1;
	if (var->iscp < 10 && var->closet2 < 3)
		var->died++;
	if (var->iru < 50 && var->closet2 < 3)
		var->died++;
	if (var->idavli < 10 && var->final == 5)
		var->died++;
	var->idavli = sqrt(pow(fabs(var->xdavli - var->posx), 2) + pow(fabs(var->ydavli - var->posy), 2));
	var->angledavli = atan2((var->ydavli - var->posy), (var->xdavli - var->posx));
	if (var->angledavli < 0)
		var->angledavli += 2 * PI;
	if (var->angledavli > 2 * PI)
		var->angledavli -= 2 * PI;
	if (var->idavli > var->distance)
		var->angledavli = -1;
	var->iuser = sqrt(pow(fabs(var->xuser - var->posx), 2) + pow(fabs(var->yuser - var->posy), 2));
	var->angleuser = atan2((var->yuser - var->posy), (var->xuser - var->posx));
	if (var->angleuser < 0)
		var->angleuser += 2 * PI;
	if (var->angleuser > 2 * PI)
		var->angleuser -= 2 * PI;
	if (var->iuser > var->distance)
		var->angleuser = -1;
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
	ray_casting(var, 0);
	var->no = 0;
	var->so = 0;
	var->we = 0;
	var->ea = 0;
	var->vide = 0;
	if (var->m_pressed== 0)
		mlx_mouse_move(var->mlx, var->win, 1800, 900);
	init_forbidden(var, 0, 0);
	if (var->died && var->iru < 60)
	{
		if (var->died > 20)
			my_put_image_to_image2(var, 0, -500, 2000);
		else
			my_put_image_to_image(var, 0, -600, 2000);
	}
	if (var->died && var->idavli < 20)
	{
		my_put_image_to_image2(var, 0, 0, 5000);
		my_put_image_to_image8(var, 0, -600, 2000);	
	}
	mlx_put_image_to_window(var->mlx, var->win, var->imag2, 0, 0);
	if (var->distance > 100)
		mlx_put_image_to_window(var->mlx, var->win, var->imag, -55, -55);
	if (var->attackech > 0 && var->attackech < 6)
		mlx_put_image_to_window(var->mlx, var->win, var->imgech2, 0, 0);
	mlx_destroy_image(var->mlx, var->imag2);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 44, 44);
	if (var->timeech < 50 && var->screech)
		mlx_string_put(var->mlx, var->win, 930, 450, 0xFF0000, "Pssst...");
	if (var->door2 == 1 && (var->map[(int)var->doory / 15][(int)var->doorx / 15] == '2' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '3' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '6'))
		mlx_string_put(var->mlx, var->win, 940, 750, 0x00FFFFFF, "Press E to open!");
	if (var->closet2 == 1 && var->map[(int)var->closety / 15][(int)var->closetx / 15] == 'p')
		mlx_string_put(var->mlx, var->win, 940, 750, 0x00FFFFFF, "Press E to hide!");
	mlx_string_put(var->mlx, var->win, 1500, 50, 0xFFFFFF, "Room :");
	mlx_string_put(var->mlx, var->win, 1550, 50, 0xFFFFFF, ft_itoa(var->doornumber));
	scenario(var);
	if (var->door2 == 1 && var->e_pressed == 1 && (var->map[(int)var->doory / 15][(int)var->doorx / 15] == '2' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '3'))
		var->door2 = 2;
	if (var->closet2 == 1 && var->e_pressed == 1 && var->map[(int)var->closety / 15][(int)var->closetx / 15] == 'p')
		var->closet2 = 2;
	if (var->closet2 == 2)
	{
		var->closet2x = ((int)var->closetx / 15) * 15;
		var->closet2y = ((int)var->closety / 15) * 15;
		var->closet2 = 3;
	}
	if (var->closet2 > 2)
	{
		var->posx = var->closet2x;
		var->posy = var->closet2y;
		if (var->map[(int)var->posy / 15][(int)var->posx / 15 + 1] == '1')
			var->sens = 'e';
		else if (var->map[(int)var->posy / 15][(int)var->posx / 15 - 1] == '1')
			var->sens = 'w';
		else if (var->map[(int)var->posy / 15 + 1][(int)var->posx / 15] == '1')
			var->sens = 's';
		else if (var->map[(int)var->posy / 15 - 1][(int)var->posx / 15] == '1')
			var->sens = 'n';
		if (var->sens == 'e')
			var->angle = PI;
		else if (var->sens == 'w')
			var->angle = 0;
		else if (var->sens == 'n')
			var->angle = PI / 2;
		else if (var->sens == 's')
			var->angle = 3 * PI / 2;
		if (var->closet2 < 30 && var->closet3 == 0)
			var->closet2++;
	}
	if (var->closet3 == 1)
		var->closet2--;
	if (var->closet3 == 1 && var->closet2 == 2)
	{
		var->closet3 = 0;
		var->closet2 = 0;
	}
	if (var->closet2 >= 30 && var->e_pressed == 1)
		var->closet3 = 1;
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
	if (var->closet2 == 1)
		var->closet2 = 0;
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
	if (fmod(var->posx, 2.0) > 0.5 && var->highech == 0)
		var->highech = 1;
	else if (fmod(var->posx, 2.0) <= 0.5 && var->highech == 0)
		var->highech = 2;
	// if (var->iech > 25)
	// {
	// 	if (var->xech < var->posx)
	// 		var->xech += 1;
	// 	else if (var->xech > var->posx)
	// 		var->xech -= 1;
	// 	if (var->yech < var->posy)
	// 		var->yech += 1;
	// 	else if (var->yech > var->posy)
	// 		var->yech -= 1;
	// }
	if (var->health > 200)
		var->died = 30;
	if (var->died)
	{
		var->died++;
		if (var->died > 30)
		{
			printf("\n ------------\n");
			printf("|  You Died  |\n");
			printf(" ------------\n");
			exit(0);
		}
	}
	while (get_time() < start + MS)
		usleep(5);
	return (0);
}

void	forbidden_helper6(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	if (var->map[i / 15][j / 15 + 1] == '1')
		c = 'e';
	else if (var->map[i / 15][j / 15 - 1] == '1')
		c = 'w';
	else if (var->map[i / 15 + 1][j / 15] == '1')
		c = 's';
	else if (var->map[i / 15 - 1][j / 15] == '1')
		c = 'n';
	if (c == 'w')
	{
		k = 2;
		while (++k < 14)
		{
			l = 0;
			while (++l < 3)
				var->forbidden[i + k][j + l] = 'p';
		}
	}
	else if (c == 'e')
	{
		k = 2;
		while (++k < 14)
		{
			l = 12;
			while (++l < 15)
				var->forbidden[i + k][j + l] = 'p';
		}
	}
	else if (c == 'n')
	{
		k = 0;
		while (++k < 3)
		{
			l = 2;
			while (++l < 14)
				var->forbidden[i + k][j + l] = 'p';
		}
	}
	else if (c == 's')
	{
		k = 12;
		while (++k < 15)
		{
			l = 2;
			while (++l < 14)
				var->forbidden[i + k][j + l] = 'p';
		}
	}
}

void	forbidden_helper5(t_var *var, int i, int j, char c)
{
	if (c == 'D')
	{
		var->xdavli = j;
		var->ydavli = i;
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
			{
					var->forbidden[i + k][j + l] = c;
			}
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
			if (var->map[i][j] == 'D' && var->xdavli == 0)
				forbidden_helper5(var, i * 15, j * 15, 'D');
			if (var->map[i][j] == 'p')
				forbidden_helper6(var, i * 15, j * 15, 'p');
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
	i = -1;
	var->i = malloc(sizeof(double) * 1920);
	if (!var->i)
		return (free4(var, i, 0), 0);
	while (++i < 1920)
		var->i[i] = 0;
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
	var.m_pressed = 0;
	var.up_pressed = 0;
	var.down_pressed = 0;
	var.left_pressed = 0;
	var.right_pressed = 0;
	var.shift_pressed = 0;
	var.vide = 0;
	var.health = 0;
	var.energy = 0;
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
	var.angledru = 0;
	var.xscp = 0;
	var.yscp = 0;
	var.iscp = 0;
	var.anglescp = 0;
	var.angledscp = 0;
	var.xech = 0;
	var.yech = 0;
	var.iech = 0;
	var.angleech = 0;
	var.angledech = 0;
	var.xdavli = 0;
	var.ydavli = 0;
	var.idavli = 0;
	var.angledavli = 0;
	var.angleddavli = 0;
	
	var.xuser = 0;
	var.yuser = 0;
	var.iuser = 0;
	var.angleuser = 0;
	var.angleduser = 0;
	var.left_angle = 0;
	var.right_angle = 0;
	var.ru2 = 0;
	var.screech = 0;
	var.scp173 = 0;
	var.lookech = 0;
	var.rusens = 0;
	var.closet = 0;
	var.closet2 = 0;
	var.closet3 = 0;
	var.closetx = 0;
	var.closety = 0;
	var.closet2x = 0;
	var.closet2y = 0;
	var.died = 0;
	var.timeech = 0;
	var.attackech = 0;
	var.highech = 0;
	var.doornumber = 0;
	var.final = 0;
	var.distance = DIST;
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
	var.img = mlx_xpm_file_to_image(var.mlx, "./xpms/Red_dot.xpm", &var.width, &var.height);
	if (!var.img)
		return (0);
	var.imgd = mlx_xpm_file_to_image(var.mlx, "./xpms/Door.xpm", &var.width1, &var.height1);
	if (!var.imgd)
		return (0);
	var.imgp = mlx_xpm_file_to_image(var.mlx, "./xpms/Closet.xpm", &var.width1, &var.height1);
	if (!var.imgp)
		return (0);
	var.imgru1 = mlx_xpm_file_to_image(var.mlx, "./xpms/Rush1.xpm", &var.widthru1, &var.heightru1);
	if (!var.imgru1)
		return (0);
	var.imgru2 = mlx_xpm_file_to_image(var.mlx, "./xpms/Rush2.xpm", &var.widthru2, &var.heightru2);
	if (!var.imgru2)
		return (0);
	var.imgscp = mlx_xpm_file_to_image(var.mlx, "./xpms/SCP173.xpm", &var.widthscp, &var.heightscp);
	if (!var.imgscp)
		return (0);
	var.imgscp2 = mlx_xpm_file_to_image(var.mlx, "./xpms/SCP173_2.xpm", &var.widthscp2, &var.heightscp2);
	if (!var.imgscp2)
		return (0);
	var.imgech = mlx_xpm_file_to_image(var.mlx, "./xpms/Screech1.xpm", &var.widthech, &var.heightech);
	if (!var.imgech)
		return (0);
	var.imgech2 = mlx_xpm_file_to_image(var.mlx, "./xpms/Screech2.xpm", &var.widthech2, &var.heightech2);
	if (!var.imgech2)
		return (0);
	var.imgdavli = mlx_xpm_file_to_image(var.mlx, "./xpms/davli.xpm", &var.widthdavli, &var.heightdavli);
	if (!var.imgdavli)
		return (0);
	var.imgdavli2 = mlx_xpm_file_to_image(var.mlx, "./xpms/davli2.xpm", &var.widthdavli2, &var.heightdavli2);
	if (!var.imgdavli2)
		return (0);
	var.imguser = mlx_xpm_file_to_image(var.mlx, "./xpms/fflamion.xpm", &var.widthuser, &var.heightuser);
	if (!var.imguser)
		return (0);
	var.addrd = mlx_get_data_addr(var.imgd, &var.bitd, &var.lend, &var.endiand);
	var.addrp = mlx_get_data_addr(var.imgp, &var.bitp, &var.lenp, &var.endianp);
	var.imag = mlx_new_image(var.mlx, 150, 150);
	var.addr = mlx_get_data_addr(var.imag, &var.bit, &var.len, &var.endian);
	var.addrru1 = mlx_get_data_addr(var.imgru1, &var.bitru1, &var.lenru1, &var.endianru1);
	var.addrru2 = mlx_get_data_addr(var.imgru2, &var.bitru2, &var.lenru2, &var.endianru2);
	var.addrscp = mlx_get_data_addr(var.imgscp, &var.bitscp, &var.lenscp, &var.endianscp);
	var.addrscp2 = mlx_get_data_addr(var.imgscp2, &var.bitscp2, &var.lenscp2, &var.endianscp2);
	var.addrech = mlx_get_data_addr(var.imgech, &var.bitech, &var.lenech, &var.endianech);
	var.addrech2 = mlx_get_data_addr(var.imgech2, &var.bitech2, &var.lenech2, &var.endianech2);
	var.addrdavli = mlx_get_data_addr(var.imgdavli, &var.bitdavli, &var.lendavli, &var.endiandavli);
	var.addrdavli2 = mlx_get_data_addr(var.imgdavli2, &var.bitdavli2, &var.lendavli2, &var.endiandavli2);
	var.addruser = mlx_get_data_addr(var.imguser, &var.bituser, &var.lenuser, &var.endianuser);

	var.imgno = mlx_xpm_file_to_image(var.mlx, var.north, &var.widthno, &var.heightno);
	var.imgso = mlx_xpm_file_to_image(var.mlx, var.south, &var.widthso, &var.heightso);
	var.imgwe = mlx_xpm_file_to_image(var.mlx, var.west, &var.widthwe, &var.heightwe);
	var.imgea = mlx_xpm_file_to_image(var.mlx, var.east, &var.widthea, &var.heightea);
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
	mlx_mouse_hide(var.mlx, var.win);
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
