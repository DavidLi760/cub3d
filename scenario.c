/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenario.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:07 by davli             #+#    #+#             */
/*   Updated: 2024/10/22 16:16:15 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    scenario(t_var *var)
{
    if (var->posy > 2 * 15 && var->doornumber == 0)
        var->doornumber = 1;
    if (var->posy > 68 && var->doortime && var->posx < 95 && var->doornumber == 1)
        var->doornumber = 2;
    if (var->posy > 200 && var->doortime && var->posx < 95 && var->doornumber == 2)
    {
        var->screech = 1;
        var->doornumber = 3;
        var->distance -= 150;
    }
    if (var->doornumber == 3)
    {
        if (var->posy < 200 && var->distance < 150)
            var->distance += 150;
        if (var->posy > 200 && var->distance > 150)
            var->distance -= 150;
    }
    if (var->posy > 235 && var->posy < 260 && var->posx > 110 && var->doortime && var->doornumber == 3)
    {
        var->doornumber = 4;
        var->distance += 150;
    }
    if (var->posy > 335 && var->posx > 220 && var->doortime && var->doornumber == 4)
    {
        var->doornumber = 5;
        var->rush = 1;
        var->xru = 45 + 4;
        var->yru = 250 + 4.5;
    }
    if (var->doornumber == 5)
    {
        if (var->distance > 150 && (var->xru == 49 || var->xru == 89 || var->xru == 129 || var->xru == 169))
            var->distance -= 150;
        if (var->distance < 150 && (var->xru == 69 || var->xru == 109 || var->xru == 149 || var->xru == 189))
            var->distance += 150;
        if (var->xru < 191)
            var->xru += 1;
        if (var->xru < 245 && var->xru > 190)
            var->xru += 2;
        if (var->xru > 244 && var->yru < 700 && var->doornumber == 5)
            var->yru += 2;
    }
    if (var->posy > 485 && var->posx < 270 && var->doortime && var->doornumber == 5)
    {
        if (var->distance < 150)
            var->distance += 150;
        var->doornumber = 6;
        var->rush = 0;
        var->xru = 0;
        var->yru = 0;
        var->scp173 = 1;
        var->xscp = 225;
        var->yscp = 575;
    }
    if (var->posy < 550 && var->posy > 520 && var->posx > 275 && var->doortime && var->doornumber == 6)
    {
        var->doornumber = 7;
        var->scp173 = 0;
        var->xscp = 0;
        var->yscp = 0;
        var->distance -= 150;
    }
    if (var->doornumber == 7)
    {
        var->numberech++;
        if (var->numberech == 200 || var->numberech % 600 == 0)
            var->screech = 1;
        if (var->posy < 550 && var->posx < 275 && var->distance < 150)
            var->distance += 150;
        if (var->posx > 275 && var->distance > 150)
            var->distance -= 150;
    }
    if (var->posy > 680 && var->posx < 185 && var->doortime && var->doornumber == 7)
    {
        var->doornumber = 8;
        var->distance += 150;
    }
    if (var->posy > 840 && var->posx < 120 && var->doortime && var->doornumber == 8)
    {
        var->doornumber = 9;
        var->rush = 1;
        var->xru = 105;
        var->yru = 500;
    }
    if (var->doornumber == 9)
    {
        if (var->distance > 150 && (var->yru == 500 || var->yru == 580 || var->yru == 660))
            var->distance -= 150;
        if (var->distance < 150 && (var->yru == 540 || var->yru == 620 || var->yru == 720))
            var->distance += 150;
        if (var->yru < 1200)
            var->yru += 2;
    }
    if (var->posy > 1100 && var->doortime && var->doornumber == 9)
    {
        var->doornumber = 10;
        var->rush = 0;
        var->xru = 0;
        var->yru = 0;
        var->scp173 = 1;
        var->xscp = 60;
        var->yscp = 1185;
    }
    if (var->posy > 1200 && var->doortime && var->doornumber == 10)
    {
        var->doornumber = 11;
        var->scp173 = 0;
        var->xscp = 0;
        var->yscp = 0;
        var->distance -= 150;
        var->numberech = 0;
    }
    if (var->doornumber == 11)
    {
        var->numberech++;
        if (var->numberech == 10 || var->numberech % 800 == 0)
            var->screech = 1;
    }
    if (var->posy > 1370 && var->doortime && var->doornumber == 11)
    {
        var->doornumber = 12;
        var->distance += 150;
    }
    if (var->posy > 1505 && var->posx > 280 && var->doortime && var->doornumber == 12)
    {
        var->doornumber = 13;
        var->xscp = 285;
        var->yscp = 1605;
        var->scp173 = 1;
    }
    if (var->posx > 380 && var->posy > 1670 && var->doortime && var->doornumber == 13)
        var->doornumber = 14;
    if (var->posy > 1880 && var->doortime)
    {
        var->doornumber = 15;
        var->xscp = 0;
        var->yscp = 0;
        var->scp173 = 0;
        var->numberech = 0;
    }
    if (var->doornumber == 15)
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
                mlx_string_put(var->mlx, var->win, 920, 750, 0xFF0000,"WELCOME STRANGER");
            if (var->numberech > 250 && var->numberech < 450)
                mlx_string_put(var->mlx, var->win, 850, 750, 0xFF0000,"NOW I WILL ASK YOU ONE FINAL QUESTION");
            if (var->numberech > 450)
            {
                var->final = 2;
                var->xuser = var->xdavli - 20;
                var->yuser = var->ydavli;
                var->xdavli += 20;
            }
        }
        if (var->final == 2)
        {
            if (var->numberech++ < 550)
            {
                var->posx = 393;
                var->posy = 1950;
            }
            mlx_string_put(var->mlx, var->win, 850, 750, 0xFF0000, "WHICH ONE OF US IS THE MOST BEAUTIFUL ?");
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
        if (var->final == 3)
        {
            var->posx = 411;
            var->posy = 2010;
            var->xuser = 0;
            var->yuser = 0;
            var->numberech++;
            if (var->numberech > 50 && var->numberech < 200)
                mlx_string_put(var->mlx, var->win, 920, 750, 0xFF0000, "GOOD ANSWER");
            if (var->numberech > 200)
                var->final = 4;
        }
        if (var->final == 4)
        {
            if (var->numberech > 200 && var->numberech < 400)
                mlx_string_put(var->mlx, var->win, 920, 750, 0xFF0000, "NOW DIE !!");
            if (var->numberech == 450)
                var->final = 5;
            var->numberech++;
        }
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
        if (var->final == 6)
        {
            var->numberech++;
            if (var->numberech > 50)
            {
                mlx_string_put(var->mlx, var->win, 940, 200, 0xFFFF00, "You win !");
                mlx_string_put(var->mlx, var->win, 940, 400, 0xFFFF00, "You win !");
                mlx_string_put(var->mlx, var->win, 940, 600, 0xFFFF00, "You win !");
                mlx_string_put(var->mlx, var->win, 940, 800, 0xFFFF00, "You win !");
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
}
