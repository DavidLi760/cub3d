/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:13:58 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 16:14:06 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	forbidden_helper4(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	if (c == '6')
	{
		k = 8;
		while (++k < 10)
		{
			l = 1;
			while (l < 16 - var->doortime2)
				var->forbidden[i + k][j + l++] = '2';
			while (++l < 16)
				var->forbidden[i + k][j + l] = '0';
		}
	}
}

void	forbidden_helper3(t_var *var, int i, int j, char c)
{
	if (c == '4')
	{
		var->k = 8;
		while (++var->k < 10)
		{
			var->l = 0;
			while (var->l < 16 - var->doortime)
				var->l++;
			while (++var->l < 16)
				var->forbidden[i + var->k][j + var->l] = '0';
		}
	}
	else if (c == '5')
	{
		var->k = 0;
		while (var->k < 15 - var->doortime)
			var->k++;
		while (++var->k < 16)
		{
			var->l = 4;
			while (++var->l < 6)
				var->forbidden[i + var->k][j + var->l] = '0';
		}
	}
}

void	forbidden_helper2(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	if (c == '2')
	{
		k = 8;
		while (++k < 10)
		{
			l = -1;
			while (++l < 16)
			{
					var->forbidden[i + k][j + l] = c;
			}
		}
	}
	else if (c == '3')
	{
		k = -1;
		while (++k < 16)
		{
			l = 4;
			while (++l < 6)
				var->forbidden[i + k][j + l] = c;
		}
	}
}

void	forbidden_helper(t_var *var, int i, int j, char c)
{
	int	k;
	int	l;

	k = 0;
	while (k < 16)
	{
		l = 0;
		while (l < 16)
		{
			var->forbidden[i + k][j + l] = c;
			l++;
		}
		k++;
	}
}

void	init_forbidden(t_var *var, int i, int j)
{
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == '1')
				forbidden_helper(var, i * 15, j * 15, '1');
			if (var->map[i][j] == '2')
				forbidden_helper2(var, i * 15, j * 15, '2');
			if (var->map[i][j] == '3')
				forbidden_helper2(var, i * 15, j * 15, '3');
			if (var->map[i][j] == '4')
				forbidden_helper3(var, i * 15, j * 15, '4');
			if (var->map[i][j] == '5')
				forbidden_helper3(var, i * 15, j * 15, '5');
			if (var->map[i][j] == '6')
				forbidden_helper4(var, i * 15, j * 15, '6');
			if (var->map[i][j] == 'D' && var->xdavli == 0)
				forbidden_helper5(var, i * 15, j * 15, 'D');
			if (var->map[i][j] == 'p')
				forbidden_helper6(var, i * 15, j * 15, 'p');
			j++;
		}
		i++;
	}
}
