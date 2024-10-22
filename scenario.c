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
    if (var->posy > 4 * 15 && var->doortime && var->posx < 95 && var->doornumber == 1)
        var->doornumber = 2;
    if (var->posy > 14 * 15 && var->doortime && var->doornumber == 2)
    {
        var->screech = 1;
        var->doornumber = 3;
        var->distance -= 150;
    }
    if (var->posy < 18 * 15 && var->posx > 7 * 15 && var->doortime && var->doornumber == 3)
    {
        var->doornumber = 4;
        var->distance += 150;
    }
    if (var->posy > 23 * 15 && var->doortime && var->doornumber == 4)
    {
        var->doornumber = 5;
        var->rush = 1;
        var->xru = 45 + 4;
        var->yru = 250 + 4.5;
    }
    if (var->doornumber == 5)
    {
        if (var->distance > 150 && (var->xru == 49 || var->xru == 129 || var->xru == 209))
            var->distance -= 150;
        if (var->distance < 150 && (var->xru == 89 || var->xru == 169 || var->xru == 245))
            var->distance += 150;
        if (var->xru < 245 && var->doornumber == 5)
            var->xru += 2;
        if (var->xru > 244 && var->yru < 700 && var->doornumber == 5)
            var->yru += 2;
    }
    if (var->posy > 32 * 15 && var->doortime == 1 && var->doornumber == 5)
    {
        var->doornumber = 6;
        var->rush = 0;
        var->xru = 0;
        var->yru = 0;
        var->scp173 = 1;
        var->xscp = 225;
        var->yscp = 575;
    }
    if (var->posy < 540 && var->posy > 520 && var->posx > 270 && var->doortime && var->doornumber == 6)
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
        if (var->numberech == 10 || var->numberech % 1000 == 0)
            var->screech = 1;
    }
    if (var->posy > 680 && var->posy < 710 && var->doortime && var->doornumber == 7)
    {
        var->doornumber = 8;
        var->distance += 150;
    }
    if (var->posy > 800 && var->posx < 130 && var->doortime && var->doornumber == 8)
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
    if (var->posy > 1505 && var->posy < 1535 && var->posx > 280 && var->doortime && var->doornumber == 12)
    {
        var->doornumber = 13;
        var->xscp = 285;
        var->yscp = 1605;
        var->scp173 = 1;
    }

    printf("posx : %f\n", var->posx);
    printf("posy : %f\n", var->posy);
    // if (var->pos)
}
