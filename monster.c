/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:10:52 by davli             #+#    #+#             */
/*   Updated: 2024/10/20 19:11:03 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_monster(t_var *var, char *tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        if (tab[i] == 'r')
            rush(var);
        else if (tab[i] == 's')
            scp173(var);
        else if (tab[i] == 'e')
            screech(var);
        i++;
    }
}

void    rush(t_var *var)
{
    if (var->angleru >= 0)
	{
		var->right_angle = var->ray_angle;
		if (var->right_angle > var->left_angle && var->angleru > var->left_angle && var->angleru < var->right_angle)
			var->angledru = (var->angleru - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->right_angle < var->left_angle && var->angleru > var->right_angle && var->angleru > var->left_angle)
			var->angledru = (var->angleru - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->right_angle < var->left_angle && var->angleru < var->right_angle && var->angleru < var->left_angle)
			var->angledru = (var->angleru + (2 * PI - var->left_angle)) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->left_angle < var->right_angle && var->angleru > var->left_angle && var->angleru > var->right_angle)
			var->angledru = (var->angleru - 2 * PI - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle < var->right_angle && var->angleru < var->left_angle && var->angleru < var->right_angle)
			var->angledru = (var->angleru - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle > var->right_angle && var->angleru < var->left_angle && var->angleru > var->right_angle)
			var->angledru = (var->angleru - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
	}
	var->rusize = 40000 / (var->iru * 1.5);
	if (var->angleru >= 0 && fmod(var->xru, 2) == 0)
		my_put_image_to_image(var, var->angledru * 1920 - var->rusize / 1.5, 500 - var->pitch - var->rusize / 2, var->rusize);
	else if (var->angleru >= 0 && fmod(var->xru, 2) != 0)
		my_put_image_to_image2(var, var->angledru * 1920 - var->rusize / 1.5, 500 - var->pitch - var->rusize / 2, var->rusize);

}

void    scp173(t_var *var)
{
    if (var->anglescp >= 0)
	{
		var->right_angle = var->ray_angle;
		if (var->right_angle > var->left_angle && var->anglescp > var->left_angle && var->anglescp < var->right_angle)
			var->angledscp = (var->anglescp - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->right_angle < var->left_angle && var->anglescp > var->right_angle && var->anglescp > var->left_angle)
			var->angledscp = (var->anglescp - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->right_angle < var->left_angle && var->anglescp < var->right_angle && var->anglescp < var->left_angle)
			var->angledscp = (var->anglescp + (2 * PI - var->left_angle)) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->left_angle < var->right_angle && var->anglescp > var->left_angle && var->anglescp > var->right_angle)
			var->angledscp = (var->anglescp - 2 * PI - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle < var->right_angle && var->anglescp < var->left_angle && var->anglescp < var->right_angle)
			var->angledscp = (var->anglescp - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle > var->right_angle && var->anglescp < var->left_angle && var->anglescp > var->right_angle)
			var->angledscp = (var->anglescp - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
	}
	var->scpsize = 40000 / (var->iscp * 1.5);
	if ((var->angledscp < 0.1 || var->angledscp > 0.9) && var->iscp > 10 && var->iscp < 130)
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
	if (var->anglescp >= 0 && var->angledscp > 0.2 && var->angledscp < 0.8 && var->iscp > 15)
		my_put_image_to_image3(var, var->angledscp * 1920 - (var->scpsize / 2), 500 - var->pitch - var->scpsize / 2, var->scpsize);
	else if ((var->anglescp >= 0 && (var->angledscp < 0.2 || var->angledscp > 0.8)) || var->iscp <= 15)
		my_put_image_to_image4(var, var->angledscp * 1920 - (var->scpsize / 2), 500 - var->pitch - var->scpsize / 2, var->scpsize);
}

void    screech(t_var *var)
{
	if (var->angleech >= 0)
	{
		var->right_angle = var->ray_angle;
		if (var->right_angle > var->left_angle && var->angleech > var->left_angle && var->angleech < var->right_angle)
			var->angledech = (var->angleech - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->right_angle < var->left_angle && var->angleech > var->right_angle && var->angleech > var->left_angle)
			var->angledech = (var->angleech - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->right_angle < var->left_angle && var->angleech < var->right_angle && var->angleech < var->left_angle)
			var->angledech = (var->angleech + (2 * PI - var->left_angle)) / (2 * PI - var->left_angle + var->right_angle);
		else if (var->left_angle < var->right_angle && var->angleech > var->left_angle && var->angleech > var->right_angle)
			var->angledech = (var->angleech - 2 * PI - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle < var->right_angle && var->angleech < var->left_angle && var->angleech < var->right_angle)
			var->angledech = (var->angleech - var->left_angle) / (var->right_angle - var->left_angle);
		else if (var->left_angle > var->right_angle && var->angleech < var->left_angle && var->angleech > var->right_angle)
			var->angledech = (var->angleech - var->left_angle) / (2 * PI - var->left_angle + var->right_angle);
	}
	var->echsize = 40000 / (var->iech * 1.5);
	if (var->angleech >= 0 && fmod(var->xech, 2) == 0)
		my_put_image_to_image5(var, var->angledech * 1920 - var->echsize / 1.5, 500 - var->pitch - var->echsize / 2, var->echsize);
}