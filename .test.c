/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:38:23 by davli             #+#    #+#             */
/*   Updated: 2024/09/05 16:40:29 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	init_var(t_var *var, int i, int j)
{
	// var->forbidden = malloc(sizeof(char *) * 1010);
	// if (!var->forbidden)
	// 	return (free4(var, 0), 0);
	// while (++i < 1010)
	// {
	// 	var->forbidden[i] = malloc(sizeof(char) * 1980);
	// 	if (!var->forbidden[i])
	// 		return (free4(var, i), 0);
	// 	while (j < 1980)
	// 	{
	// 		var->forbidden[i][j] = 0;
	// 		j++;
	// 	}
	// }
	// var->position.x = var->position2.x / 15;
	// var->position.y = var->position2.y / 15;
	return (1);
}

double	is_a_grid(t_var *var, double angle, double x, double y)
{
	double tempx;
	double tempy;

	while (x < 105 && y < 105 &&
		!is_a_wall(var, var->posy + sin(angle) * y, var->posx + cos(angle) * x))
	{
		tempy = var->posy + sin(angle) * y - 10.90;
		if (tempy <= 10.90)
			tempy += 10.90;
		tempy = fmod(tempy, 15);
		tempx = var->posx + cos(angle) * x - 10.00;
		if (tempx <= 10.00)
			tempx += 10.00;
		tempx = fmod(tempx, 15);
		// printf("%f, ", tempx);
		// printf("%f\n", tempy);
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
	}
	return (x);
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
	var.angle = PI / 2;
	if (!check_arg(&var, argv))
		return (0);
	if (!init_var(&var, -1, 0))
		return (0);
	// printf("%f", is_a_grid(&var, 0, 25, 25));
}