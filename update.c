/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:19:29 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 17:19:36 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_view(t_var *var)
{
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
}

void	update_pos(t_var *var)
{
	if (var->posx >= var->position2.x + 1)
		var->position2.x += 1;
	if (var->posx <= var->position2.x - 1)
		var->position2.x -= 1;
	if (var->posy >= var->position2.y + 1)
		var->position2.y += 1;
	if (var->posy <= var->position2.y - 1)
		var->position2.y -= 1;
}

void	death_update(t_var *var)
{
	if (var->iscp < 10 && var->closet2 < 3)
		var->died++;
	if (var->iru < 50 && var->closet2 < 3)
		var->died++;
	if (var->idavli < 10 && var->final == 5)
		var->died++;
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
}

int	update(t_var *var)
{
	long long	start;

	start = get_time();
	var->imag2 = mlx_new_image(var->mlx, 1920, 1920);
	var->addr2 = mlx_get_data_addr(var->imag2, &var->bit2, &var->len2, &var->endian2);
	walking_update(var);
	update_view(var);
	update_pos(var);
	minimap(var, -1, 0);
	init_monster(var);
	init_monster2(var);
	death_update(var);
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
		my_put_image_to_image2(var, 0, -500, 2000);
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
		mlx_string_put(var->mlx, var->win, 930, 450, 0xFF0000, "Behind you...");
	if (var->door2 == 1 && (var->map[(int)var->doory / 15][(int)var->doorx / 15] == '2' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '3' || var->map[(int)var->doory / 15][(int)var->doorx / 15] == '6'))
		mlx_string_put(var->mlx, var->win, 940, 750, 0x00FFFFFF, "Press E to open!");
	if (var->closet2 == 1 && var->map[(int)var->closety / 15][(int)var->closetx / 15] == 'p')
		mlx_string_put(var->mlx, var->win, 940, 750, 0x00FFFFFF, "Press E to hide!");
	mlx_string_put(var->mlx, var->win, 1500, 50, 0xFFFFFF, "Room :");
	var->itoa = ft_itoa(var->doornumber);
	mlx_string_put(var->mlx, var->win, 1550, 50, 0xFFFFFF, var->itoa);
	free(var->itoa);
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
	if (fmod(var->posy, 2.0) > 1.0 && var->highech == 0)
		var->highech = 1;
	if (fmod(var->posy, 2.0) <= 1.0 && var->highech == 0)
		var->highech = 2;
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
			close_win(var);
		}
	}
	while (get_time() < start + MS)
		usleep(5);
	return (0);
}