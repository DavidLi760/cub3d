/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenario.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:16:07 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:46:03 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scenario1(t_var *var)
{
	if (var->posy > 2 * 15 && var->doornumber == 0)
		var->doornumber = 1;
	if (var->posy > 68 && var->doortime && var->posx < 95
		&& var->doornumber == 1)
		var->doornumber = 2;
	if (var->posy > 200 && var->doortime && var->posx < 95
		&& var->doornumber == 2)
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
}

void	scenario2(t_var *var)
{
	if (var->posy > 235 && var->posy < 260 && var->posx > 110
		&& var->doortime && var->doornumber == 3)
	{
		var->doornumber = 4;
		var->distance += 150;
	}
	if (var->posy > 335 && var->posx > 220
		&& var->doortime && var->doornumber == 4)
	{
		var->doornumber = 5;
		var->rush = 1;
		var->xru = 45 + 4;
		var->yru = 250 + 4.5;
	}
}

void	scenario3(t_var *var)
{
	if (var->doornumber == 5)
	{
		if (var->distance > 150 && (var->xru == 49 || var->xru == 89
				|| var->xru == 129 || var->xru == 169))
			var->distance -= 150;
		if (var->distance < 150 && (var->xru == 69 || var->xru == 109
				|| var->xru == 149 || var->xru == 189))
			var->distance += 150;
		if (var->xru < 191)
			var->xru += 1;
		if (var->xru < 245 && var->xru > 190)
			var->xru += 2;
		if (var->xru > 244 && var->yru < 700 && var->doornumber == 5)
			var->yru += 2;
	}
}

void	scenario(t_var *var)
{
	scenario1(var);
	scenario2(var);
	scenario3(var);
	scenario4(var);
	scenario5(var);
	scenario6(var);
	scenario7(var);
	scenario8(var);
	if (var->doornumber == 15)
	{
		scenario9(var);
		scenario10(var);
		scenario11(var);
		scenario12(var);
		scenario13(var);
	}
}
