/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:00:01 by davli             #+#    #+#             */
/*   Updated: 2024/09/12 14:01:46 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->addr + (y * var->len + x * (var->bit / 8));
	*(unsigned int *)dst = color;
}

void	my_pixel_put2(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->addr2 + (y * var->len + x * (var->bit / 8));
	*(unsigned int *)dst = color;
}

void	draw_block(t_var *var, int i, int j, int color)
{
    int k;
    int l;

    k = -1;
    while (k < 16)
    {
        l = -1;
        while (++l < 16)
            my_pixel_put(var, j * 15 + 50 + l, i * 15 + 50 + k, color);
        k++;
    }
}

void    draw_wall(t_var *var, int j, int i, int color)
{
    int k;
    int l;

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
            if (color == 0x000000FF)
                var->forbidden[i + k][j + l] = '1';
            else if (color == 0x00000000)
                var->forbidden[i + k][j + l] = '0';
        }
    }
}