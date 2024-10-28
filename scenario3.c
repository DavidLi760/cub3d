/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenario3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:46:49 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:46:49 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scenario9(t_var *var)
{
	if (var->posy > 1950 && var->final == 0)
	{
		var->final = 1;
		var->angle = 0.5 * PI;
	}
	if (var->final == 1)
	{
		var->posx = 393;
		var->posy = 1950;
		var->numberech++;
		if (var->numberech > 80 && var->numberech < 180)
			mlx_string_put(var->mlx, var->win, 920, 750, \
					0xFF0000, "WELCOME STRANGER");
		if (var->numberech > 250 && var->numberech < 450)
			mlx_string_put(var->mlx, var->win, 850, 750, \
					0xFF0000, "NOW I WILL ASK YOU ONE FINAL QUESTION");
		if (var->numberech > 450)
		{
			var->final = 2;
			var->xuser = var->xdavli - 20;
			var->yuser = var->ydavli;
			var->xdavli += 20;
		}
	}
}

void	scenario10(t_var *var)
{
	if (var->final == 2)
	{
		if (var->numberech++ < 550)
		{
			var->posx = 393;
			var->posy = 1950;
		}
		mlx_string_put(var->mlx, var->win, 850, 750, 0xFF0000, \
				"WHICH ONE OF US IS THE MOST BEAUTIFUL ?");
		if (var->angle > 1.8 && var->posy < 1980)
			var->angle = 1.8;
		else if (var->angle < 1.1 && var->posy < 1980)
			var->angle = 1.1;
		if (var->posy > 1980)
			var->angle = 1.33;
		if (var->posy > 2010)
		{
			var->final = 3;
			var->ydavli += 22;
			var->xdavli += 6;
			var->numberech = 0;
		}
	}
}

void	scenario11(t_var *var)
{
	if (var->final == 3)
	{
		var->posx = 411;
		var->posy = 2010;
		var->xuser = 0;
		var->yuser = 0;
		var->numberech++;
		if (var->numberech > 50 && var->numberech < 200)
			mlx_string_put(var->mlx, var->win, 920, 750, \
					0xFF0000, "GOOD ANSWER");
		if (var->numberech > 200)
			var->final = 4;
	}
	if (var->final == 4)
	{
		if (var->numberech > 200 && var->numberech < 400)
			mlx_string_put(var->mlx, var->win, 920, 750, 0xFF0000, \
					"NOW DIE !!");
		if (var->numberech == 450)
			var->final = 5;
		var->numberech++;
	}
}

void	scenario12(t_var *var)
{
	if (var->numberech > 300 && var->final > 3)
		mlx_string_put(var->mlx, var->win, 920, 50, 0xFFFFFF, "RUN AWAY");
	if (var->final == 5)
	{
		var->tempx = fabs(var->xdavli - var->posx);
		var->tempy = fabs(var->ydavli - var->posy);
		if (var->xdavli < var->posx)
			var->xdavli += (var->tempx / (var->tempx + var->tempy)) * 0.9;
		if (var->xdavli > var->posx)
			var->xdavli -= (var->tempx / (var->tempx + var->tempy)) * 0.9;
		if (var->ydavli < var->posy)
			var->ydavli += (var->tempy / (var->tempx + var->tempy)) * 0.9;
		if (var->ydavli > var->posy)
			var->ydavli -= (var->tempy / (var->tempx + var->tempy)) * 0.9;
		var->itoa = ft_itoa(var->idavli);
		mlx_string_put(var->mlx, var->win, 980, 50, 0xFF0000, var->itoa);
		free(var->itoa);
		if (var->posy < 30)
		{
			var->final = 6;
			var->numberech = 0;
		}
	}
}

void	scenario13(t_var *var)
{
	if (var->final == 6)
	{
		var->numberech++;
		if (var->numberech > 50)
		{
			mlx_string_put(var->mlx, var->win, 940, 200, 0xFFFF00, \
					"You win !");
			mlx_string_put(var->mlx, var->win, 940, 400, 0xFFFF00, \
					"You win !");
			mlx_string_put(var->mlx, var->win, 940, 600, 0xFFFF00, \
					"You win !");
			mlx_string_put(var->mlx, var->win, 940, 800, 0xFFFF00, \
					"You win !");
		}
		var->xdavli = var->posx;
		var->ydavli = 60;
		var->xdavli = 70;
		if (var->numberech > 150)
		{
			printf("\n ------------\n");
			printf("|  You won ! |\n");
			printf(" ------------\n");
			close_win(var);
		}
	}
}
