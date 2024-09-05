/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:57:17 by davli             #+#    #+#             */
/*   Updated: 2024/09/05 17:45:59 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_malloc(t_var *var, int no)
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

void    free_special(t_var *var, int i)
{
    int j;
    int k;

    j = 0;
    k = 0;
    while (j < i && j < count_line(var, 0))
        free(var->element[j++]);
    if (i > count_line(var, 0))
        while (j + k < i)
            free(var->map[k++]);
    free_malloc(var, 2);
}

void	free_list(t_var *var)
{
	int	i;

	i = 0;
	if (var->split)
		while (var->split[i])
			free(var->split[i++]);
	*var->split = NULL;
	free(var->split);
	i = 0;
	if (var->file)
		free(var->file);
	if (var->map)
		while (var->map[i])
			free(var->map[i++]);
	*var->map = NULL;
	free(var->map);
	i = 0;
	if (var->element)
		while (var->element[i])
			free(var->element[i++]);
	*var->element = NULL;
	free(var->element);
	mlx_destroy_image(var->mlx, var->img);
	mlx_destroy_display(var->mlx);
	free(var->mlx);
}
