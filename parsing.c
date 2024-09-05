/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:23:02 by davli             #+#    #+#             */
/*   Updated: 2024/09/05 17:06:17 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(t_var *var, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str[--i] == "buc."[j] && j < 4)
		j++;
	if (j == 4)
		return (1);
	printf("Error : Wrong extension");
	return (free(var->file), 0);
}

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
		return (free_special(var, i), NULL);
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
		return (free_special(var, i), NULL);
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
		return (free_malloc(var, 0), 0);
	var->map = malloc(sizeof(char *) * (count_line(var, 1) + 1));
	if (!var->map)
		return (free_malloc(var, 1), 0);
	while (++i < count_line(var, 0))
		var->element[i] = get_element(i, var);
	var->element[i] = 0;
	var->max = find_max(i, var);
	while (i < count_line(var, 0) + count_line(var, 1))
		var->map[j++] = get_map(i++, var, var->max);
	var->map[j] = 0;
	return (1);
}

int	is_wall_closed(t_var *var)
{
	(void)var;
	return (1);
}

int	check_arg(t_var *var, char **argv)
{
	int	i;

	i = 0;
	var->fd = open(argv[1], O_RDONLY);
	var->file = get_next_line(var->fd);
	close(var->fd);
	if (!var->file)
		return (printf("Error : File don't exist\n"), 0);
	if (!check_extension(var, argv[1]))
		return (0);
	if (!get_split(var, -1, 0))
		return (free(var->file), 0);
	if (!is_wall_closed(var))
		return (0);
	return (1);
}
