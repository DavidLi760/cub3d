/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:04:21 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 17:15:09 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_monster(t_var *var)
{
	var->iru = sqrt(pow(fabs(var->xru - var->posx), 2) \
			+ pow(fabs(var->yru - var->posy), 2));
	var->angleru = atan2((var->yru - var->posy), (var->xru - var->posx));
	if (var->angleru < 0)
		var->angleru += 2 * PI;
	if (var->angleru > 2 * PI)
		var->angleru -= 2 * PI;
	if (var->iru > var->distance)
		var->angleru = -1;
	var->iscp = sqrt(pow(fabs(var->xscp - var->posx), 2) \
			+ pow(fabs(var->yscp - var->posy), 2));
	var->anglescp = atan2((var->yscp - var->posy), (var->xscp - var->posx));
	if (var->anglescp < 0)
		var->anglescp += 2 * PI;
	if (var->anglescp > 2 * PI)
		var->anglescp -= 2 * PI;
	if (var->iscp > var->distance)
		var->anglescp = -1;
	var->iech = sqrt(pow(fabs(var->xech - var->posx), 2) \
			+ pow(fabs(var->yech - var->posy), 2));
	var->angleech = atan2((var->yech - var->posy), (var->xech - var->posx));
}

void	init_monster2(t_var *var)
{
	if (var->angleech < 0)
		var->angleech += 2 * PI;
	if (var->angleech > 2 * PI)
		var->angleech -= 2 * PI;
	if (var->iech > var->distance)
		var->angleech = -1;
	var->idavli = sqrt(pow(fabs(var->xdavli - var->posx), 2) \
			+ pow(fabs(var->ydavli - var->posy), 2));
	var->angledavli = atan2((var->ydavli \
	- var->posy), (var->xdavli - var->posx));
	if (var->angledavli < 0)
		var->angledavli += 2 * PI;
	if (var->angledavli > 2 * PI)
		var->angledavli -= 2 * PI;
	if (var->idavli > var->distance)
		var->angledavli = -1;
	var->iuser = sqrt(pow(fabs(var->xuser - var->posx), 2) \
			+ pow(fabs(var->yuser - var->posy), 2));
	var->angleuser = atan2((var->yuser - var->posy), (var->xuser - var->posx));
	if (var->angleuser < 0)
		var->angleuser += 2 * PI;
	if (var->angleuser > 2 * PI)
		var->angleuser -= 2 * PI;
	if (var->iuser > var->distance)
		var->angleuser = -1;
}
