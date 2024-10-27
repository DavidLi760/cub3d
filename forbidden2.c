/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:20:48 by davli             #+#    #+#             */
/*   Updated: 2024/10/27 11:32:17 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forbidden_helper5(t_var *var, int i, int j, char c)
{
	if (c == 'D')
	{
		var->xdavli = j;
		var->ydavli = i;
	}
}

void	get_c(t_var *var, int i, int j, char *c)
{
	if (var->map[i / 15][j / 15 + 1] == '1')
		*c = 'e';
	else if (var->map[i / 15][j / 15 - 1] == '1')
		*c = 'w';
	else if (var->map[i / 15 + 1][j / 15] == '1')
		*c = 's';
	else if (var->map[i / 15 - 1][j / 15] == '1')
		*c = 'n';
}

void	helper6_utils1(t_var *var, int i, int j, char c)
{
	if (c == 'w')
	{
		var->k = 2;
		while (++var->k < 14)
		{
			var->l = 0;
			while (++var->l < 3)
				var->forbidden[i + var->k][j + var->l] = 'p';
		}
	}
	if (c == 'e')
	{
		var->k = 2;
		while (++var->k < 14)
		{
			var->l = 12;
			while (++var->l < 15)
				var->forbidden[i + var->k][j + var->l] = 'p';
		}
	}
}

void	helper6_utils2(t_var *var, int i, int j, char c)
{
	if (c == 'n')
	{
		var->k = 0;
		while (++var->k < 3)
		{
			var->l = 2;
			while (++var->l < 14)
				var->forbidden[i + var->k][j + var->l] = 'p';
		}
	}
	if (c == 's')
	{
		var->k = 12;
		while (++var->k < 15)
		{
			var->l = 2;
			while (++var->l < 14)
				var->forbidden[i + var->k][j + var->l] = 'p';
		}
	}
}

void	forbidden_helper6(t_var *var, int i, int j, char c)
{
	get_c(var, i, j, &c);
	helper6_utils1(var, i, j, c);
	helper6_utils2(var, i, j, c);
}
