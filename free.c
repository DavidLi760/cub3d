/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:57:17 by davli             #+#    #+#             */
/*   Updated: 2024/09/10 15:15:15 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free2(t_var *var, int no)
{
	int	i;

	i = 0;
	while (var->split[i])
		free(var->split[i++]);
	free(var->split);
	if (no == 0)
		return ;
	if (no == 1)
		free(var->element);
	if (no == 2)
	{
		free(var->element);
		free(var->map);
	}
}

void	free3(t_var *var, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < i && j < count_line(var, 0))
		free(var->element[j++]);
	if (i > count_line(var, 0))
		while (j + k < i)
			free(var->map[k++]);
	free2(var, 2);
}

void	free4(t_var *var, int no)
{
	int	i;

	i = 0;
	while (var->element[i])
		free(var->element[i++]);
	i = 0;
	while (var->map[i])
		free(var->map[i++]);
	free(var->file);
	free2(var, 2);
	i = 0;
	while (i < no && i < 1110)
		free(var->forbidden[i++]);
	if (no > 0)
		free(var->forbidden);
}

void	free_list(t_var *var)
{
	free4(var, 1010);
	mlx_destroy_image(var->mlx, var->img);
	mlx_destroy_image(var->mlx, var->img1);
	mlx_destroy_image(var->mlx, var->img2);
	mlx_destroy_image(var->mlx, var->img3);
	mlx_destroy_image(var->mlx, var->imag);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
}
