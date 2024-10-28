/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenario2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:46:24 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:49:09 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scenario4(t_var *var)
{
	if (var->posy > 485 && var->posx < 270 && var->doortime
		&& var->doornumber == 5)
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
	if (var->posy < 550 && var->posy > 520 && var->posx > 275
		&& var->doortime && var->doornumber == 6)
	{
		var->doornumber = 7;
		var->scp173 = 0;
		var->xscp = 0;
		var->yscp = 0;
		var->distance -= 150;
	}
}

void	scenario5(t_var *var)
{
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
	if (var->posy > 680 && var->posx < 185
		&& var->doortime && var->doornumber == 7)
	{
		var->doornumber = 8;
		var->distance += 150;
	}
	if (var->posy > 840 && var->posx < 120
		&& var->doortime && var->doornumber == 8)
	{
		var->doornumber = 9;
		var->rush = 1;
		var->xru = 105;
		var->yru = 500;
	}
}

void	scenario6(t_var *var)
{
	if (var->doornumber == 9)
	{
		if (var->distance > 150 && (var->yru == 500
				|| var->yru == 580 || var->yru == 660))
			var->distance -= 150;
		if (var->distance < 150 && (var->yru == 540
				|| var->yru == 620 || var->yru == 720))
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
}

void	scenario7(t_var *var)
{
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
}

void	scenario8(t_var *var)
{
	if (var->posy > 1505 && var->posx > 280 && var->doortime
		&& var->doornumber == 12)
	{
		var->doornumber = 13;
		var->xscp = 285;
		var->yscp = 1605;
		var->scp173 = 1;
	}
	if (var->posx > 380 && var->posy > 1670
		&& var->doortime && var->doornumber == 13)
		var->doornumber = 14;
	if (var->posy > 1880 && var->doortime)
	{
		var->doornumber = 15;
		var->xscp = 0;
		var->yscp = 0;
		var->scp173 = 0;
		var->numberech = 0;
	}
}
