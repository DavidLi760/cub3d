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

long long	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int str_cmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (s1[i] != s2[i])
        return (0);
    while (s1[i] == s2[i] && s2[i])
        i++;
    if (s1[i] != s2[i] && s2[i])
        return (0);
    return (1);
}

void	my_pixel_put(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->addr + (y * var->len + x * (var->bit / 8));
	*(unsigned int *)dst = color;
}

void	my_pixel_put2(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->addr2 + (y * var->len2 + x * (var->bit2 / 8));
	*(unsigned int *)dst = color;
}

int my_pixel_from_texture(t_var *var, int x, int y, char no)
{
    int     color;
    char    *pixel;

    if (no == 'n')
        pixel = var->addrno + (y * var->lenno + x * (var->bitno / 8));
    if (no == 's')
        pixel = var->addrso + (y * var->lenso + x * (var->bitso / 8));
    if (no == 'w')
        pixel = var->addrwe + (y * var->lenwe + x * (var->bitwe / 8));
    if (no == 'e')
        pixel = var->addrea + (y * var->lenea + x * (var->bitea / 8));
    if (no == 'd')
        pixel = var->addrd + (y * var->lend + x * (var->bitd / 8));
    color = *(unsigned int *)pixel;
    return (color);
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

void    draw_door(t_var *var, int j, int i, int no)
{
    int k;
    int l;

    k = -1;
    if (no == 0)
    {
        while (++k < 16)
        {
            l = -1;
            while (++l < 16)
            {
                if (l == 8)
                    my_pixel_put(var, j + l, i + k, 0x0000FF00);
                else
                    my_pixel_put(var, j + l, i + k, 0x00000000);
            }
        }
    }
    else if (no == 1)
    {
        k = -1;
        while (++k < 16)
        {
            l = -1;
            while (++l < 16)
            {
                if (k == 8)
                    my_pixel_put(var, j + l, i + k, 0x0000FF00);
                else
                    my_pixel_put(var, j + l, i + k, 0x00000000);
            }
        }
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
        }
    }
}