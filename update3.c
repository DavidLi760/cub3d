/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:54:05 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 18:54:13 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	screamer_text(t_var *var)
{
	mlx_put_image_to_window(var->mlx, var->win, var->imag2, 0, 0);
	if (var->distance > 100)
		mlx_put_image_to_window(var->mlx, var->win, var->imag, -55, -55);
	if (var->attackech > 0 && var->attackech < 6)
		mlx_put_image_to_window(var->mlx, var->win, var->imgech2, 0, 0);
	mlx_destroy_image(var->mlx, var->imag2);
	mlx_put_image_to_window(var->mlx, var->win, var->img, 44, 44);
	if (var->timeech < 50 && var->screech)
		mlx_string_put(var->mlx, var->win, 930, 450, 0xFF0000, "Behind you...");
	if (var->door2 == 1 && (var->map[(int)var->doory / 15][(int)var->doorx \
		/ 15] == '2' || var->map[(int)var->doory / 15][(int)var->doorx / 15] \
		== '3' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '6'))
		mlx_string_put(var->mlx, var->win, 940, 750, \
				0x00FFFFFF, "Press E to open!");
	if (var->closet2 == 1 && var->map[(int)var->closety \
			/ 15][(int)var->closetx / 15] == 'p')
		mlx_string_put(var->mlx, var->win, \
				940, 750, 0x00FFFFFF, "Press E to hide!");
	mlx_string_put(var->mlx, var->win, 1500, 50, 0xFFFFFF, "Room :");
	var->itoa = ft_itoa(var->doornumber);
	mlx_string_put(var->mlx, var->win, 1550, 50, 0xFFFFFF, var->itoa);
	free(var->itoa);
}

void	door_closet(t_var *var)
{
	if (var->door2 == 1 && var->e_pressed == 1 && (var->map[(int)var->doory \
			/ 15][(int)var->doorx / 15] == '2' || var->map[(int)var->doory \
			/ 15][(int)var->doorx / 15] == '3'))
		var->door2 = 2;
	if (var->closet2 == 1 && var->e_pressed == 1 && var->map[(int)var->closety \
			/ 15][(int)var->closetx / 15] == 'p')
		var->closet2 = 2;
	if (var->closet2 == 2)
	{
		var->closet2x = ((int)var->closetx / 15) * 15;
		var->closet2y = ((int)var->closety / 15) * 15;
		var->closet2 = 3;
	}
}

void	closet2(t_var *var)
{
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
}
