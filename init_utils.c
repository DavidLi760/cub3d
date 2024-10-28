/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:12:39 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 17:10:27 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pos(t_var *var)
{
	var->position.x = var->position2.x / 15;
	var->position.y = var->position2.y / 15;
	var->posx = var->position2.x;
	var->posy = var->position2.y;
}

int	init_var(t_var *var, int i, int j)
{
	var->forbidden = malloc(sizeof(char *) * (MAP_SIZE + 1));
	if (!var->forbidden)
		return (free4(var, 0, 0), 0);
	while (++i < MAP_SIZE)
	{
		j = 0;
		var->forbidden[i] = malloc(sizeof(char) * (MAP_SIZE + 1));
		if (!var->forbidden[i])
			return (free4(var, i, 0), 0);
		while (j <= MAP_SIZE)
		{
			var->forbidden[i][j] = '0';
			j++;
		}
	}
	var->forbidden[i] = 0;
	i = -1;
	var->i = malloc(sizeof(double) * 1920);
	if (!var->i)
		return (free4(var, i, 0), 0);
	while (++i < 1920)
		var->i[i] = 0;
	init_forbidden(var, 0, 0);
	set_pos(var);
	return (1);
}

int	init_img6(t_var *var)
{
	var->imgea = mlx_xpm_file_to_image(var->mlx, \
	var->east, &var->widthea, &var->heightea);
	if (!var->imgea)
		return (0);
	var->addrno = \
	mlx_get_data_addr(var->imgno, &var->bitno, &var->lenno, &var->endianno);
	if (!var->addrno)
		return (0);
	var->addrso = \
	mlx_get_data_addr(var->imgso, &var->bitso, &var->lenso, &var->endianso);
	if (!var->addrso)
		return (0);
	var->addrwe = \
	mlx_get_data_addr(var->imgwe, &var->bitwe, &var->lenwe, &var->endianwe);
	if (!var->addrwe)
		return (0);
	return (1);
}
