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
    else if (no == 'p')
        pixel = var->addrp + (y * var->lenp + x * (var->bitp / 8));
    else if (no == 's')
        pixel = var->addrscp + (y * var->lenscp + x * (var->bitscp / 8));
    else if (no == 'c')
        pixel = var->addrscp2 + (y * var->lenscp2 + x * (var->bitscp2 / 8));    
    else if (no == 'E')
        pixel = var->addrech + (y * var->lenech + x * (var->bitech / 8));
    color = *(unsigned int *)pixel;
    return (color);
}

void my_put_image_to_image(t_var *var, int x, int y, int size)
{
    int color;
    double scale_factor = 400.0 / size;
    int i;
    int j;

    i = 0;
    while (i < size && i < 1010)
    {
        j = 0;
        while (j < size && j < 1920)
        {
            int src_x = (int)(j * scale_factor);
            int src_y = (int)(i * scale_factor);

            if (src_x < 400 && src_y < 400)
            {
                color = my_pixel_from_texture(var, src_x, src_y, 'r');
                if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0)
                    if (var->i[(x + j)] > var->iru)
                    {
                        my_pixel_put2(var, x + j, y + i, color);
                    }
            }
            j++;
        }
        i++;
    }
}

void my_put_image_to_image2(t_var *var, int x, int y, int size)
{
    int color;
    double scale_factor = 400.0 / size;
    int i;
    int j;

    i = 0;
    while (i < size && i < 1010)
    {
        j = 0;
        while (j < size && j < 1920)
        {
            int src_x = (int)(j * scale_factor);
            int src_y = (int)(i * scale_factor);

            if (src_x < 400 && src_y < 400)
            {
                color = my_pixel_from_texture(var, src_x, src_y, 'u');
                if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0)
                {
                    if (var->i[(x + j)] > var->iru)
                    {
                        my_pixel_put2(var, x + j, y + i, color);
                    }                
                }
            }
            j++;
        }
        i++;
    }
}

void my_put_image_to_image3(t_var *var, int x, int y, int size)
{
    int color;
    double scale_factor = 400.0 / size;
    int i;
    int j;

    i = 0;
    while (i < size && i < 2000)
    {
        j = 0;
        while (j < size && j < 1920)
        {
            int src_x = (int)(j * scale_factor);
            int src_y = (int)(i * scale_factor);

            if (src_x < 400 && src_y < 400)
            {
                color = my_pixel_from_texture(var, src_x, src_y, 's');
                if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0 && color != 0xFFFFFF)
                    if (var->i[(x + j)] > var->iscp)
                        my_pixel_put2(var, x + j, y + i, color);
            }
            j++;
        }
        i++;
    }
}

void my_put_image_to_image4(t_var *var, int x, int y, int size)
{
    int color;
    double scale_factor = 400.0 / size;
    int i;
    int j;

    i = 0;
    while (i < size && i < 2000)
    {
        j = 0;
        while (j < size && j < 1920)
        {
            int src_x = (int)(j * scale_factor);
            int src_y = (int)(i * scale_factor);

            if (src_x < 400 && src_y < 400)
            {
                color = my_pixel_from_texture(var, src_x, src_y, 'c');
                if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0 && color != 0xFFFFFF)
                    if (var->i[(x + j)] > var->iscp)
                        my_pixel_put2(var, x + j, y + i, color);
            }
            j++;
        }
        i++;
    }
}

void my_put_image_to_image5(t_var *var, int x, int y, int size)
{
    int color;
    double scale_factor = 400.0 / size;
    int i;
    int j;

    i = 0;
    while (i < size && i < 2000)
    {
        j = 0;
        while (j < size && j < 1920)
        {
            int src_x = (int)(j * scale_factor);
            int src_y = (int)(i * scale_factor);

            if (src_x < 400 && src_y < 400)
            {
                color = my_pixel_from_texture(var, src_x, src_y, 'E');
                if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0 && color != 0xFFFFFF)
                    if (var->i[(x + j)] * 2.5 > var->iech && color != 0x0000FF)
                        my_pixel_put2(var, x + j, y + i, color);
            }
            j++;
        }
        i++;
    }
}

// void my_put_image_to_image6(t_var *var, int x, int y, int size)
// {
//     int color;
//     double scale_factor = 400.0 / size;
//     int i;
//     int j;

//     i = 0;
//     while (i < size && i < 2000)
//     {
//         j = 0;
//         while (j < size && j < 1920)
//         {
//             int src_x = (int)(j * scale_factor);
//             int src_y = (int)(i * scale_factor);

//             if (src_x < 1796 && src_y < 1010)
//             {
//                 color = my_pixel_from_texture(var, src_x, src_y, 'h');
//                 if (x + j < 1920 && y + i < 1010 && x + j > 0 && y + i > 0 && color != 0xFFFFFF)
//                     if (var->i[(x + j)] > var->iech)
//                         my_pixel_put2(var, x + j, y + i, color);
//             }
//             j++;
//         }
//         i++;
//     }
// }

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