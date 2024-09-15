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
	mlx_put_image_to_window(var->mlx, var->win, var->imag, -50, -50);
}

// int	can_move(t_var *var, double i, double j)
// {
// 	int k;
// 	int l;

// 	k = (int)i;
// 	l = (int)j;
// 	while (k < 16)

// 	return (1);
// }

int	is_a_wall(t_var *var, int i, int j)
{
	int	k;
	int	l;

	k = i - 1 + 4;
	l = j - 1 + 4;
	while (k <= i + 6)
	{
		l = j - 1 + 4;
		while (l <= j + 6)
		{
			if (var->map[k / 15][l / 15] == '1')
				return (1);
			l++;
		}
		k++;
	}
	return (0);
}

void	trace_ray(t_var *var, double angle, int *i)
{

	*i = 0;
	while (!is_a_wall(var, var->posy + sin(angle) * *i, var->posx + cos(angle) * *i))
	{
		if (100 + cos(angle) * *i < 150 && 100 + cos(angle) * *i > 0)
			if (100 + sin(angle) * *i < 150 && 100 + sin(angle) * *i > 0)
				my_pixel_put(var, 100 + cos(angle) * *i, 100 + sin(angle) * *i, 0x00FFFFFF);
		(*i)++;
	}
}

void	draw_walls(t_var *var, int x, int wall_h)
{
	int	start;
	int	end;
	int y;
	int	i;

	i = 0;
	start = (1010 - wall_h) / 2;
	end = (1010 + wall_h) / 2;
	y = start;
	while (i < y)
	{
		my_pixel_put2(var, x, y, 0x00000000);
		i++;
	}
	while (y < end && y > 0 && y < 1010)
	{
		my_pixel_put2(var, x, y, 0x00FF00);
		y++;
	}
	while (end < 1010)
	{
		my_pixel_put2(var, x, y, 0x00000000);
		end++;
	}
}

void	ray_casting(t_var *var, int i)
{
	double	start_angle;
	int		wall_h;
	double	dist;

	wall_h = 0;
	start_angle = var->angle - PI / 3 / 2;
	while (i < 960)
	{
		var->ray_angle = start_angle + i * (PI / 3 / 960);
		trace_ray(var, var->ray_angle, &wall_h);
		dist = wall_h * cos(var->ray_angle - var->angle);
		wall_h = (int)(1010 / dist);
		draw_walls(var, i, wall_h);
		i++;
	}
}

int	update(t_var *var)
{
	var->delay++;
	if (var->delay > DELAY)
	{
		if (var->w_pressed == 1)
		{
			if (var->w_pressed == 1 && is_a_wall(var, var->posy + var->directy, var->posx) && !is_a_wall(var, var->posy, var->posx + var->directx))
				var->posx += var->directx * 1;
			else if (var->w_pressed == 1 && is_a_wall(var, var->posy, var->posx + var->directx) && !is_a_wall(var, var->posy + var->directy, var->posx))
				var->posy += var->directy * 1;
			else if (!is_a_wall(var, var->posy + var->directy, var->posx + var->directx))
			{
				var->posx += var->directx * 1;
				var->posy += var->directy * 1;
			}
		}
		if (var->s_pressed == 1)
		{
			if (is_a_wall(var, var->posy - var->directy, var->posx) && !is_a_wall(var, var->posy, var->posx - var->directx))
				var->posx -= var->directx * 1;
			else if (is_a_wall(var, var->posy, var->posx - var->directx) && !is_a_wall(var, var->posy - var->directy, var->posx))
				var->posy -= var->directy * 1;
			else if (!is_a_wall(var, var->posy - var->directy, var->posx - var->directx))
			{
				var->posx -= var->directx * 1;
				var->posy -= var->directy * 1;
			}
		}
		if (var->a_pressed == 1)
		{
			if (is_a_wall(var, var->posy - var->directx, var->posx) && !is_a_wall(var, var->posy, var->posx + var->directy))
				var->posx += var->directy * 1;
			else if (is_a_wall(var, var->posy, var->posx + var->directy) && !is_a_wall(var, var->posy - var->directx, var->posx))
				var->posy -= var->directx * 1;
			else if (!is_a_wall(var, var->posy - var->directx, var->posx + var->directy))
			{
				var->posx += var->directy * 1;
				var->posy -= var->directx * 1;
			}
		}
		if (var->d_pressed == 1)
		{
			if (is_a_wall(var, var->posy + var->directx, var->posx) && !is_a_wall(var, var->posy, var->posx - var->directy))
				var->posx -= var->directy * 1;
			else if (is_a_wall(var, var->posy, var->posx - var->directy) && !is_a_wall(var, var->posy + var->directx, var->posx))
				var->posy += var->directx * 1;
			else if (!is_a_wall(var, var->posy + var->directx, var->posx - var->directy))
			{
				var->posx -= var->directy * 1;
				var->posy += var->directx * 1;
			}
		}
		if (var->up_pressed == 1)
		{
			var->angle += 0;
		}
		if (var->left_pressed == 1)
		{
			var->angle += -0.15;
		}
		if (var->down_pressed == 1)
		{
			var->angle += 0;
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
		mlx_put_image_to_window(var->mlx, var->win, var->imag2, 0, 0);
		minimap(var, -1, 0);
		ray_casting(var, 0);
		mlx_put_image_to_window(var->mlx, var->win, var->img, 50, 50);
		mlx_put_image_to_window(var->mlx, var->win, var->img, 50 + var->directx * 3, 50 + var->directy * 3);
	}
	return (0);
}

int	init_var(t_var *var, int i, int j)
{
	var->forbidden = malloc(sizeof(char *) * 1010);
	if (!var->forbidden)
		return (free4(var, 0), 0);
	while (++i < 1010)
	{
		var->forbidden[i] = malloc(sizeof(char) * 1980);
		if (!var->forbidden[i])
			return (free4(var, i), 0);
		while (j < 1980)
		{
			var->forbidden[i][j] = 0;
			j++;
		}
	}
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
	var.e_pressed = 0;
	var.w_pressed = 0;
	var.s_pressed = 0;
	var.a_pressed = 0;
	var.d_pressed = 0;
	var.directx = 0;
	var.directy = 0;
	var.angle = 0;
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
	var.img = mlx_xpm_file_to_image(var.mlx, "Red_dot.xpm", &var.height, &var.width);
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
	var.imag2 = mlx_new_image(var.mlx, 1920, 1010);
	var.addr2 = mlx_get_data_addr(var.imag2, &var.bit2, &var.len2, &var.endian2);
	i = 0;
	while (var.element[i])
		printf("%s\n", var.element[i++]);
	i = 0;
	while (var.map[i])
		printf("%s\n", var.map[i++]);
	// printf("x : %d, y : %d\n", var.position.x, var.position.y);
	mlx_hook(var.win, 2, 1L << 0, escape, &var);
	mlx_hook(var.win, 3, 1L << 1, release, &var);
	mlx_hook(var.win, 17, 0, close_win, &var);
	mlx_loop_hook(var.mlx, update, &var);
	mlx_loop(var.mlx);
}
