/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 19:42:27 by davli             #+#    #+#             */
/*   Updated: 2024/09/05 19:42:38 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_line(t_var *var, int no)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var->split[i] && !(var->split[i][0] >= '0'
		&& var->split[i][0] <= '9') && var->split[i][0] != ' ')
		i++;
	while (var->split[i + j])
		j++;
	if (no == 0)
		return (i);
	return (j);
}

char	*get_element(int i, t_var *var)
{
	int		j;
	char	*element;

	j = 0;
	while (var->split[i][j])
		j++;
	element = malloc(sizeof(char) * j + 1);
	if (!element)
		return (free3(var, i), NULL);
	j = -1;
	while (var->split[i][++j])
		element[j] = var->split[i][j];
	return (element);
}

int	find_max(int i, t_var *var)
{
	int	j;
	int	max;

	max = 0;
	while (var->split[i])
	{
		j = 0;
		while (var->split[i][j])
			j++;
		if (max < j)
			max = j;
		i++;
	}
	return (max);
}

char	*get_map(int i, t_var *var, int max)
{
	int		j;
	char	*map;

	map = malloc(sizeof(char) * max + 1);
	if (!map)
		return (free3(var, i), NULL);
	j = -1;
	while (var->split[i][++j])
		map[j] = var->split[i][j];
	while (j < max)
	{
		map[j] = ' ';
		j++;
	}
	map[j] = 0;
	return (map);
}

int	get_split(t_var *var, int i, int j)
{
	var->split = ft_split(var->file, "\n");
	if (!var->split)
		return (printf("Error : Empty file\n"), 0);
	if (!count_line(var, 1))
		return (printf("Error : No map found\n"), 0);
	if (!count_line(var, 0))
		return (printf("Error : No texture found\n"), 0);
	var->element = malloc(sizeof(char *) * (count_line(var, 0) + 1));
	if (!var->element)
		return (free2(var, 0), 0);
	var->map = malloc(sizeof(char *) * (count_line(var, 1) + 1));
	if (!var->map)
		return (free2(var, 1), 0);
	while (++i < count_line(var, 0))
		var->element[i] = get_element(i, var);
	var->element[i] = 0;
	var->max = find_max(i, var);
	while (i < count_line(var, 0) + count_line(var, 1))
		var->map[j++] = get_map(i++, var, var->max);
	var->map[j] = 0;
	return (1);
}
