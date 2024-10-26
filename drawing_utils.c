/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:24:27 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 20:24:35 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
