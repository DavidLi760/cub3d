/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:42:49 by davli             #+#    #+#             */
/*   Updated: 2024/10/29 11:48:15 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*my_pixel_from_texture2(t_var *var, int x, int y, char no)
{
	if (no == 'p')
		return (var->addrp + (y * var->lenp + x * (var->bitp / 8)));
	else if (no == 's')
		return (var->addrscp + (y * var->lenscp + x * (var->bitscp / 8)));
	else if (no == 'c')
		return (var->addrscp2 + (y * var->lenscp2 + x * (var->bitscp2 / 8)));
	else if (no == 'E')
		return (var->addrech + (y * var->lenech + x * (var->bitech / 8)));
	else if (no == 'D')
		return (var->addrdavli + (y * var->lendavli + x * (var->bitdavli / 8)));
	else if (no == 'U')
		return (var->addruser + (y * var->lenuser + x * (var->bituser / 8)));
	else if (no == 'A')
		return (var->addrdavli2 + (y * var->lendavli2 + x * \
				(var->bitdavli2 / 8)));
	return (0);
}

int	my_pixel_from_texture(t_var *var, int x, int y, char no)
{
	int		color;
	char	*pixel;

	if (no == 'n')
		pixel = var->addrno + (y * var->lenno + x * (var->bitno / 8));
	else if (no == 'S')
		pixel = var->addrso + (y * var->lenso + x * (var->bitso / 8));
	else if (no == 'w')
		pixel = var->addrwe + (y * var->lenwe + x * (var->bitwe / 8));
	else if (no == 'e')
		pixel = var->addrea + (y * var->lenea + x * (var->bitea / 8));
	else if (no == 'd')
		pixel = var->addrd + (y * var->lend + x * (var->bitd / 8));
	else if (no == 'r')
		pixel = var->addrru1 + (y * var->lenru1 + x * (var->bitru1 / 8));
	else if (no == 'u')
		pixel = var->addrru2 + (y * var->lenru2 + x * (var->bitru2 / 8));
	else
		pixel = my_pixel_from_texture2(var, x, y, no);
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_block(t_var *var, int i, int j, int color)
{
	int	k;
	int	l;

	k = -1;
	while (k < 16)
	{
		l = -1;
		while (++l < 16)
			my_pixel_put(var, j * 15 + 50 + l, i * 15 + 50 + k, color);
		k++;
	}
}

void	draw_door(t_var *var, int j, int i, int no)
{
	int	k;
	int	l;

	k = -1;
	while (++k < 16)
	{
		l = -1;
		while (++l < 16)
		{
			if ((l == 8 && no == 0) || (k == 8 && no == 1))
				my_pixel_put(var, j + l, i + k, 0x0000FF00);
			else
				my_pixel_put(var, j + l, i + k, 0x00000000);
		}
	}
}

void	draw_wall(t_var *var, int j, int i, int color)
{
	int	k;
	int	l;

	k = -1;
	while (++k < 16)
	{
		l = -1;
		while (++l < 16)
		{
			if ((k == 0 || l == 0))
				my_pixel_put(var, j + l, i + k, 0x00000000);
			else
				my_pixel_put(var, j + l, i + k, color);
		}
	}
}
