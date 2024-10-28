/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:19:29 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:52:13 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_closet2(t_var *var)
{
	if (var->closet3 == 1)
		var->closet2--;
	if (var->closet3 == 1 && var->closet2 == 2)
	{
		var->closet3 = 0;
		var->closet2 = 0;
	}
	if (var->closet2 >= 30 && var->e_pressed == 1)
		var->closet3 = 1;
	if (var->door2 == 1 && var->e_pressed == 1 && (var->map[(int)var->doory \
				/ 15][(int)var->doorx / 15] == '6') && var->doortime2 < 17)
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
}

void	door_modify(t_var *var)
{
	if (var->doortime2 > 16 && var->door3 == 1)
		var->door3 = 0;
	if (var->door3 == 0 && var->e_pressed == 1 && var->map[(int)var->doory \
			/ 15][(int)var->doorx / 15] == '6' && var->doortime2 == 17)
	{
		var->door3 = 2;
		var->door2 = 0;
	}
	if (var->door3 == 2 && var->doortime2 > 0)
		var->doortime2 -= 1;
	if (var->doortime2 == 0 && var->door3 == 2)
		var->door3 = 0;
	if (var->door2 == 2 && var->doortime == 1 && var->map[(int)var->doory \
			/ 15][(int)var->doorx / 15] == '2')
		var->map[(int)var->doory / 15][(int)var->doorx / 15] = '4';
	else if (var->door2 == 2 && var->doortime == 1 && var->map[(int)var->doory \
			/ 15][(int)var->doorx / 15] == '3')
		var->map[(int)var->doory / 15][(int)var->doorx / 15] = '5';
	if (var->door2 == 1)
		var->door2 = 0;
	if (var->closet2 == 1)
		var->closet2 = 0;
}

void	death(t_var *var)
{
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
}

void	norm_update(t_var *var)
{
	var->no = 0;
	var->so = 0;
	var->we = 0;
	var->ea = 0;
	var->vide = 0;
	if (var->m_pressed == 0)
		mlx_mouse_move(var->mlx, var->win, 1800, 900);
	init_forbidden(var, 0, 0);
	death_animation(var);
	screamer_text(var);
	scenario(var);
	door_closet(var);
	closet2(var);
	door_closet2(var);
	door_modify(var);
	init_screech(var);
}

int	update(t_var *var)
{
	long long	start;

	start = get_time();
	var->imag2 = mlx_new_image(var->mlx, 1920, 1920);
	var->addr2 = mlx_get_data_addr(var->imag2, \
			&var->bit2, &var->len2, &var->endian2);
	walking_update(var);
	update_view(var);
	update_pos(var);
	minimap(var, -1, 0);
	init_monster(var);
	init_monster2(var);
	death_update(var);
	ray_casting(var, 0);
	norm_update(var);
	death(var);
	while (get_time() < start + MS)
		usleep(5);
	return (0);
}
