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
			if (var->map[k / 15][l / 15] == '1')
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
		var->text_y = var->heightno * i / max + (var->plusx / 14.00);
	if (var->so)
		var->text_y = var->heightso * i / max + (var->plusx / 14.00);
	if (var->we)
		var->text_y = var->heightwe * i / max + (var->plusy / 14.00);
	if (var->ea)
		var->text_y = var->heightea * i / max + (var->plusy / 14.00);
}

int	mix_color(t_var *var, int now)
{
	int	color;

	color = now;
	int r1 = color >> 16 & 0xFF;
	int	g1 = color >> 8 & 0xFF;
	int	b1 = (color & 0xFF);
	int	r2 = 0x000000 >> 16 & 0xFF;
	int	g2 = 0x000000 >> 8 & 0xFF;
	int	b2 = 0x000000 & 0xFF;
	int	r = (int)((1 - (var->dist / (DIST * 1.5))) * r1 + var->dist / (DIST * 1.5) * r2);
	int	g = (int)((1 - (var->dist / (DIST * 1.5))) * g1 + var->dist / (DIST * 1.5) * g2);
	int	b = (int)((1 - (var->dist / (DIST * 1.5))) * b1 + var->dist / (DIST * 1.5) * b2);
	return ((r << 16) | (g << 8) | b);
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
	while (start_y < 0)
		start_y++;
	// while (var->vide == 1 && start_y < 505 - var->pitch)
	// {
	// 	my_pixel_put2(var, x, start_y, var->ceiling);
	// 	my_pixel_put2(var, x + 1, start_y++, var->ceiling);
	// }
	// while (var->vide == 1 && start_y < 505 - var->pitch)
	// {
	// 	my_pixel_put2(var, x, start_y, 0x00000000);
	// 	my_pixel_put2(var, x + 1, start_y++, 0x00000000);
	// }
	// while (var->vide == 1 && start_y < 1010)
	// {
	// 	my_pixel_put2(var, x, start_y, var->floor);
	// 	my_pixel_put2(var, x + 1, start_y++, var->floor);
	// }
	while (var->vide == 1 && start_y < end_y && start_y < 1010) // DESSIN DES MURS
	{
		my_pixel_put2(var, x, start_y, 0x0F0000);
		my_pixel_put2(var, x + 1, start_y++, 0x0F0000);
	}
	while (!var->vide && start_y < end_y && start_y < 1010) // DESSIN DES MURS
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
		var->dist = sqrt(pow(var->posx - var->plusx, 2) + pow(var->posy - var->plusy, 2));
		if (var->dist < 0)
			var->dist *= -1;
		color = mix_color(var, color);
		my_pixel_put2(var, x, start_y, color);
		my_pixel_put2(var, x + 1, start_y++, color);
	}
	while (start_y < 1010)
	{
		my_pixel_put2(var, x, start_y, var->floor);
		my_pixel_put2(var, x + 1, start_y++, var->floor);
	}
	draw_cross(var, 504, 1920);
	draw_health_bar(var, 970, 50);
}

double	is_a_grid(t_var *var, double angle, double x, double y)
{
	double tempx;
	double tempy;

	while (x < 105 && y < 105 &&
		!is_a_wall(var, var->posy + sin(angle) * y, var->posx + cos(angle) * x))
	{
		if (var->posy + sin(angle) * y - 10.90 > 15)
			tempy = var->posy + sin(angle) * y - 10.90;
		tempy = fmod(tempy, 15);
		if (var->posx + cos(angle) * x - 10.00 > 15)
			tempx = var->posx + cos(angle) * x - 10.00;
		tempx = fmod(tempx, 15);
		// printf("%f, ", var->posx);
		// printf("%f\n", var->posy);
		if (sin(angle) >= 0.1)
			tempy = (15 - tempy) / sin(angle);
		else if (sin(angle) <= 0.1)
			tempy = tempy / sin(angle);
		if (cos(angle) >= 0.1)
			tempx = (15 - tempx) / cos(angle);
		else if (cos(angle) <= 0.1)
			tempx = tempx / cos(angle);
		if (fabs(tempx) > fabs(tempy))
		{
			y += tempy;
			x += tempy;
		}
		else
		{
			y += tempx;
			x += tempx;
		}
		// printf("%f, ", (var->posy + sin(angle) * y));
		// printf("%f\n", tempy);
	}
	return (x);
}

void	get_wall_xy(t_var *var)
{
	if (var->we || var->ea)
	{
		if (var->we)
			var->wall_x = fmod(var->wall_x, 15.00);
		else
			var->wall_x = fmod(var->wall_x, 15.00);
	}
	if (var->no || var->so)
	{
		if (var->no)
			var->wall_y = fmod(var->wall_y, 15.00);
		else
			var->wall_y = fmod(var->wall_y, 15.00);
	}
}

void	get_text_x(t_var *var)
{
	if (var->we == 1|| var->ea == 1)
	{
		if (var->we)
			var->text_x = var->widthwe * ((30 - var->wall_y) / 15);
		else if (var->ea)
			var->text_x = var->widthea * ((15 - var->wall_y) / 15);	
	}
	else if (var->no == 1|| var->so == 1)
	{
		if (var->no)
			var->text_x = var->widthno * ((30 - var->wall_x) / 15);
		else if (var->so)
			var->text_x = var->widthso * ((15 - var->wall_x) / 15);
	}
}

void	trace_ray(t_var *var, double angle, double *i)
{
	*i = 0;
	while (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5)] != '1' && *i < DIST)
	{
		// (*i) += is_a_grid(var, angle, 0, 0);
		if (var->forbidden[(int)(var->posy + sin(angle) * ((*i) + 1) + 5)][(int)(var->posx + cos(angle) * ((*i) + 1) + 5)] != '1')
			*i += 1;
		else
		*i += 0.01;
	}
	if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5 - 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '0')
	{
		var->no = 1;
		printf("no");
	}
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 - 0.01)] == '0')
	{
		var->we = 1;
		printf("we");
	}
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i + 5 + 0.01)] == '0')
	{
		var->ea = 1;
		printf("ea");
	}
	else if (var->forbidden[(int)(var->posy + sin(angle) * *i + 5 + 0.01)][(int)(var->posx + cos(angle) * *i + 5)] == '0')
	{
		var->so = 1;
		printf("so");
	}
	var->wall_x = var->posx + cos(angle) * *i + 5;
	var->wall_y = var->posy + sin(angle) * *i + 5;
	var->plusx = var->posx + cos(angle) * *i + 5;
	var->plusy = var->posy + sin(angle) * *i + 5;
	printf("x:%f, ", var->wall_x);
	printf("y:%f\n", var->wall_y);
	get_wall_xy(var);
	get_text_x(var);
	if (100 + cos(angle) * *i < 150 && 100 + cos(angle) * *i > 0)
		if (100 + sin(angle) * *i < 150 && 100 + sin(angle) * *i > 0)
			my_pixel_put(var, 100 + cos(angle) * *i, 100 + sin(angle) * *i, 0x00FFFFFF);
	if (*i >= DIST && var->forbidden[(int)(var->posy + sin(angle) * *i + 5)][(int)(var->posx + cos(angle) * *i) + 5] != '1')
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
	start_angle = var->angle  - PI / 3 / 2;
	while (i < 960)
	{
		var->ray_angle = start_angle + i * (PI / 3 / 960);
		trace_ray(var, var->ray_angle, &distance);
		wall_height = 1010 / (distance * cos(var->ray_angle - var->angle) / 15);
		draw_wall_column(var, pixel, wall_height);
		i++;
		pixel += 2;
		var->no = 0;
		var->so = 0;
		var->we = 0;
		var->ea = 0;
		var->vide = 0;
	}
	while (get_time() < start + MS)
		usleep(5);
}

int	update(t_var *var)
{
	var->imag2 = mlx_new_image(var->mlx, 1920, 1920);
	var->addr2 = mlx_get_data_addr(var->imag2, &var->bit2, &var->len2, &var->endian2);
	if (var->w_pressed == 1)
	{
		if (var->w_pressed == 1 && is_a_wall(var, var->posy + var->directy, var->posx) && !is_a_wall(var, var->posy, var->posx + var->directx))
			var->posx += var->directx * (var->shift_pressed * 0.25 + 0.25);
		else if (var->w_pressed == 1 && is_a_wall(var, var->posy, var->posx + var->directx) && !is_a_wall(var, var->posy + var->directy, var->posx))
			var->posy += var->directy * (var->shift_pressed * 0.25 + 0.25);
		else if (!is_a_wall(var, var->posy + var->directy, var->posx + var->directx))
		{
			var->posx += var->directx * (var->shift_pressed * 0.25 + 0.25);
			var->posy += var->directy * (var->shift_pressed * 0.25 + 0.25);
		}
	}
	if (var->s_pressed == 1)
	{
		if (is_a_wall(var, var->posy - var->directy, var->posx) && !is_a_wall(var, var->posy, var->posx - var->directx))
			var->posx -= var->directx * (var->shift_pressed * 0.25 + 0.25);
		else if (is_a_wall(var, var->posy, var->posx - var->directx) && !is_a_wall(var, var->posy - var->directy, var->posx))
			var->posy -= var->directy * (var->shift_pressed * 0.25 + 0.25);
		else if (!is_a_wall(var, var->posy - var->directy, var->posx - var->directx))
		{
			var->posx -= var->directx * (var->shift_pressed * 0.25 + 0.25);
			var->posy -= var->directy * (var->shift_pressed * 0.25 + 0.25);
		}
	}
	if (var->a_pressed == 1)
	{
		if (is_a_wall(var, var->posy - var->directx, var->posx) && !is_a_wall(var, var->posy, var->posx + var->directy))
			var->posx += var->directy * (var->shift_pressed * 0.25 + 0.25);
		else if (is_a_wall(var, var->posy, var->posx + var->directy) && !is_a_wall(var, var->posy - var->directx, var->posx))
			var->posy -= var->directx * (var->shift_pressed * 0.25 + 0.25);
		else if (!is_a_wall(var, var->posy - var->directx, var->posx + var->directy))
		{
			var->posx += var->directy * (var->shift_pressed * 0.25 + 0.25);
			var->posy -= var->directx * (var->shift_pressed * 0.25 + 0.25);
		}
	}
	if (var->d_pressed == 1)
	{
		if (is_a_wall(var, var->posy + var->directx, var->posx) && !is_a_wall(var, var->posy, var->posx - var->directy))
			var->posx -= var->directy * (var->shift_pressed * 0.25 + 0.25);
		else if (is_a_wall(var, var->posy, var->posx - var->directy) && !is_a_wall(var, var->posy + var->directx, var->posx))
			var->posy += var->directx * (var->shift_pressed * 0.25 + 0.25);
		else if (!is_a_wall(var, var->posy + var->directx, var->posx - var->directy))
		{
			var->posx -= var->directy * (var->shift_pressed * 0.25 + 0.25);
			var->posy += var->directx * (var->shift_pressed * 0.25 + 0.25);
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
	ray_casting(var, 0);
	var->no = 0;
	var->so = 0;
	var->we = 0;
	var->ea = 0;
	var->vide = 0;
	mlx_mouse_move(var->mlx, var->win, 1800, 900);
	mlx_put_image_to_window(var->mlx, var->win, var->imag2, 0, 0);
	mlx_put_image_to_window(var->mlx, var->win, var->imag, -50, -50);
	mlx_destroy_image(var->mlx, var->imag2);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 50, 50);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 50 + var->directx * 3, 50 + var->directy * 3);
	return (0);
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
			j++;
		}
		printf("\n");
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
	var.height = 5;
	var.width = 5;
	var.floor = -1;
	var.ceiling = -1;
	var.wall_x = 0;
	var.wall_y = 0;
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
	var.directx = 0;
	var.directy = 0;
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
	var.img = mlx_xpm_file_to_image(var.mlx, "./Red_dot.xpm", &var.height, &var.width);
	if (!var.img)
		return (0);
	var.img1 = mlx_xpm_file_to_image(var.mlx, "carre_bleu.xpm", &var.height, &var.width);
	if (!var.img1)
		return (0);
	var.img2 = mlx_xpm_file_to_image(var.mlx, "carre_blanc.xpm", &var.height, &var.width);
	if (!var.img2)
		return (0);
	var.img2a = mlx_xpm_file_to_image(var.mlx, "pixel_noir.xpm", &var.height, &var.width);
	var.img3 = mlx_xpm_file_to_image(var.mlx, "carre_vide.xpm", &var.height, &var.width);
	if (!var.img3)
		return (0);
	var.imag = mlx_new_image(var.mlx, 150, 150);
	var.addr = mlx_get_data_addr(var.imag, &var.bit, &var.len, &var.endian);
	i = 0;
	var.imgno = mlx_xpm_file_to_image(var.mlx, var.north, &var.heightno, &var.widthno);
	var.imgso = mlx_xpm_file_to_image(var.mlx, var.south, &var.heightso, &var.widthso);
	var.imgwe = mlx_xpm_file_to_image(var.mlx, var.west, &var.heightwe, &var.widthwe);
	var.imgea = mlx_xpm_file_to_image(var.mlx, var.east, &var.heightea, &var.widthea);
	var.addrno = mlx_get_data_addr(var.imgno, &var.bitno, &var.lenno, &var.endianno);
	var.addrso = mlx_get_data_addr(var.imgso, &var.bitso, &var.lenso, &var.endianso);
	var.addrwe = mlx_get_data_addr(var.imgwe, &var.bitwe, &var.lenwe, &var.endianwe);
	var.addrea = mlx_get_data_addr(var.imgea, &var.bitea, &var.lenea, &var.endianea);
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
	printf("x : %d, y : %d\n", var.position.x, var.position.y);
	mlx_hook(var.win, 2, 1L << 0, escape, &var);
	mlx_hook(var.win, 6, 1L << 6, mouse_move, &var);
	mlx_hook(var.win, 3, 1L << 1, release, &var);
	mlx_hook(var.win, 17, 0, close_win, &var);
	mlx_loop_hook(var.mlx, update, &var);
	mlx_loop(var.mlx);
}
