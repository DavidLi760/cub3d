/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:05:58 by davli             #+#    #+#             */
/*   Updated: 2024/08/29 18:28:22 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	escape(int keycode, t_var *var)
{
	if (keycode == 65307)
	{	
		mlx_destroy_window(var->mlx, var->win);
		exit(0);
	}
	return (0);
}

int	close_win(t_var *var)
{
	if (var->win)
		mlx_destroy_window(var->mlx, var->win);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc < 2)
		return (0);
	(void)argv;
	var.mlx = mlx_init();
	if (!var.mlx)
		return (0);
	var.win = mlx_new_window(var.mlx, 600, 600, "cub3d");
	mlx_hook(var.win, 2, 1L << 0, escape, &var);
	mlx_hook(var.win, 17, 0, close_win, &var);
	mlx_loop(var.mlx);
}
