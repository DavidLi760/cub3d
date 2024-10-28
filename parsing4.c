/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:06:38 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:06:44 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	register_angle(t_var *var, char c)
{
	if (c == 'E')
		var->angle = 0;
	if (c == 'W')
		var->angle = PI;
	if (c == 'N')
		var->angle = 3 * PI / 2;
	if (c == 'S')
		var->angle = PI / 2;
}

int	is_player_valid(t_var *var, int i, int j)
{
	var->player = 0;
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == 'E' || var->map[i][j] == 'W'
				|| var->map[i][j] == 'N' || var->map[i][j] == 'S')
			{
				var->player++;
				var->position.x = j;
				var->position.y = i;
				var->position2.x = j * 15;
				var->position2.y = i * 15;
				register_angle(var, var->map[i][j]);
			}
			j++;
		}
		i++;
	}
	var->max = i;
	if (var->player != 1)
		return (printf("Error : Less or more than 1 player\n"), 0);
	return (1);
}
