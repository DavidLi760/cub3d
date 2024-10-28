/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:05:58 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 18:21:03 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	door_text(t_var *var)
{
	if (var->door && (var->map[(int)var->plusy / 15][(int)var->plusx / 15] == \
	'2' || var->map[(int)var->plusy / 15][(int)var->plusx / 15] == '3'))
		var->text_x = var->text_x;
	else if (var->door && var->map[(int)var->plusy / 15][(int)var->plusx / 15] \
	== '6' && var->door3 == 2)
		var->text_x += var->doortime2 * 28;
	else if (var->door && var->map[(int)var->plusy / 15][(int)var->plusx / 15] \
	== '6' && var->doortime2 * 28 - 84 >= 0 && var->doortime2 * 28 - 84 <= 400)
		var->text_x += var->doortime2 * 28 - 84;
	else if (var->door && (var->map[(int)var->plusy / 15][(int)var->plusx \
	/ 15] == '4' || var->map[(int)var->plusy / 15][(int)var->plusx / 15] \
	== '5') && var->doortime * 28 - 84 >= 0)
		var->text_x += var->doortime * 28 - 84;
	if (var->text_x < 0)
		var->text_x = 0;
	if (var->door && var->text_x > 400)
		var->text_x = 400;
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
		var->wall_height = 1500 / (var->dst * cos(var->ray_angle \
		- var->angle) / 15);
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
