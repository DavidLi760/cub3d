/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:02:52 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:02:57 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scp_mechanics(t_var *var)
{
	var->scpsize = 40000 / (var->iscp * 1.5);
	if ((var->angledscp < 0 || var->angledscp > 0.9) && var->iscp > \
	10 && var->scp173)
	{
		if (var->xscp < var->posx)
			var->xscp += 0.5;
		else if (var->xscp > var->posx)
			var->xscp -= 0.5;
		if (var->yscp < var->posy)
			var->yscp += 0.5;
		else if (var->yscp > var->posy)
			var->yscp -= 0.5;
	}
}

void	screech_mechanics(t_var *var)
{
	if (var->lookech > 5)
	{
		var->screech = 0;
		var->lookech = 0;
		var->highech = 0;
		var->timeech = 0;
	}
	if (var->screech)
		var->timeech++;
	if (var->timeech > 200)
	{
		var->lookech = 0;
		var->highech = 0;
		var->attackech++;
		var->health++;
		if (var->timeech > 267)
		{
			var->timeech = 0;
			var->screech = 0;
		}
	}
	if (var->attackech > 0)
		var->attackech++;
	if (var->attackech > 6)
		var->attackech = 0;
}

void	screech2(t_var *var)
{
	var->echsize = 40000 / (var->iech * 1.5);
	if (var->angledech > 0.4 && var->angledech < 0.75 && var->highech == 2
		&& var->pitch > 800 && var->pitch < 1200)
		var->lookech++;
	else if (var->angledech > 0.4 && var->angledech < 0.75
		&& var->highech == 1 && var->pitch < -800 && var->pitch > -1200)
		var->lookech++;
	screech_mechanics(var);
}
