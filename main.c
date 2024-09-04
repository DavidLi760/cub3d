/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:05:58 by davli             #+#    #+#             */
/*   Updated: 2024/09/04 15:22:35 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	{	
		mlx_destroy_window(var->mlx, var->win);
		exit(0);
	}
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

int	close_win(t_var *var)
{
	if (var->win)
		mlx_destroy_window(var->mlx, var->win);
	exit(0);
	return (0);
}

int	update(t_var *var)
{
	var->delay++;
	if (var->delay > 500)
	{
		if (var->w_pressed == 1)
		{
			var->dot_y -= 0.2;
			if (!var->e_pressed)
				mlx_put_image_to_window(var->mlx, var->win, var->img, var->dot_x, var->dot_y);
		}
		if (var->s_pressed == 1)
		{
			var->dot_y += 0.2;
			if (!var->e_pressed)
				mlx_put_image_to_window(var->mlx, var->win, var->img, var->dot_x, var->dot_y);
		}
		if (var->a_pressed == 1)
		{
			var->dot_x -= 0.2;
			if (!var->e_pressed)
				mlx_put_image_to_window(var->mlx, var->win, var->img, var->dot_x, var->dot_y);
		}
		if (var->d_pressed == 1)
		{
			var->dot_x += 0.2;
			if (!var->e_pressed)
				mlx_put_image_to_window(var->mlx, var->win, var->img, var->dot_x, var->dot_y);
		}
		var->delay = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;

	var.delay = 0;
	var.height = 5;
	var.width = 5;
	var.dot_x = 50;
	var.dot_y = 50;
	var.e_pressed = 0;
	if (argc < 2)
		return (0);
	if (!check_arg(&var, argv))
		return (0);
	var.mlx = mlx_init();
	if (!var.mlx)
		return (0);
	var.win = mlx_new_window(var.mlx, 1920, 1010, "cub3d");
	var.img = mlx_xpm_file_to_image(var.mlx, "Red_dot.xpm", &var.height, &var.width);
	if (!var.img)
		return (0);
	mlx_hook(var.win, 2, 1L << 0, escape, &var);
	mlx_hook(var.win, 3, 1L << 1, release, &var);
	mlx_hook(var.win, 17, 0, close_win, &var);
	mlx_loop_hook(var.mlx, update, &var);
	mlx_loop(var.mlx);
}
