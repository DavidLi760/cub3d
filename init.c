/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:07:51 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 17:09:45 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init1(t_var *var)
{
	var->maximum = sqrt(pow(960, 2) + pow(505, 2));
	var->height = 5;
	var->width = 5;
	var->floor = -1;
	var->ceiling = -1;
	var->wall_x = 0;
	var->wall_y = 0;
	var->door = 0;
	var->door2 = 0;
	var->door3 = 0;
	var->doorx = 0;
	var->doory = 0;
	var->sprite = 0;
	var->doortime = 0;
	var->doortime2 = 0;
	var->doorsense = 0;
	var->e_pressed = 0;
	var->w_pressed = 0;
	var->s_pressed = 0;
	var->a_pressed = 0;
	var->d_pressed = 0;
	var->m_pressed = 0;
	var->up_pressed = 0;
	var->down_pressed = 0;
	var->dst = 0;
}

void	init2(t_var *var)
{
	var->left_pressed = 0;
	var->right_pressed = 0;
	var->shift_pressed = 0;
	var->vide = 0;
	var->health = 0;
	var->energy = 0;
	var->directx = 0;
	var->directy = 0;
	var->plusx = 0;
	var->plusy = 0;
	var->pitch = 0;
	var->pitch2 = 0;
	var->angle = 0;
	var->text_x = 0;
	var->text_y = 0;
	var->north = 0;
	var->south = 0;
	var->east = 0;
	var->west = 0;
	var->no = 0;
	var->so = 0;
	var->we = 0;
	var->ea = 0;
	var->xru = 0;
	var->yru = 0;
}

void	init3(t_var *var)
{
	var->iru = 0;
	var->angleru = 0;
	var->angledru = 0;
	var->xscp = 0;
	var->yscp = 0;
	var->iscp = 0;
	var->anglescp = 0;
	var->angledscp = 0;
	var->xech = 0;
	var->yech = 0;
	var->iech = 0;
	var->angleech = 0;
	var->angledech = 0;
	var->xdavli = 0;
	var->ydavli = 0;
	var->idavli = 0;
	var->angledavli = 0;
	var->angleddavli = 0;
	var->rusize = 0;
	var->scpsize = 0;
	var->echsize = 0;
	var->davlisize = 0;
	var->usersize = 0;
	var->xuser = 0;
	var->yuser = 0;
}

void	init4(t_var *var)
{
	var->iuser = 0;
	var->angleuser = 0;
	var->angleduser = 0;
	var->left_angle = 0;
	var->right_angle = 0;
	var->ru2 = 0;
	var->screech = 0;
	var->scp173 = 0;
	var->lookech = 0;
	var->rusens = 0;
	var->closet = 0;
	var->closet2 = 0;
	var->closet3 = 0;
	var->closetx = 0;
	var->closety = 0;
	var->closet2x = 0;
	var->closet2y = 0;
	var->died = 0;
	var->timeech = 0;
	var->attackech = 0;
	var->highech = 0;
	var->doornumber = 0;
	var->final = 0;
	var->distance = DIST;
	var->pixel = 0;
}

int	init_all(t_var *var, int no)
{
	if (no == 0)
	{
		init1(var);
		init2(var);
		init3(var);
		init4(var);
	}
	if (no == 1)
	{
		if (!init_img1(var))
			return (0);
		if (!init_img2(var))
			return (0);
		if (!init_img3(var))
			return (0);
		if (!init_img4(var))
			return (0);
		if (!init_img5(var) || !init_img6(var))
			return (0);
		var->addrea = mlx_get_data_addr(var->imgea, \
		&var->bitea, &var->lenea, &var->endianea);
		if (!var->addrea)
			return (0);
	}
	return (1);
}
