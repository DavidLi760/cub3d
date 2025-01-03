/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:01:15 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:19:06 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*copy_element(t_var *var, char *s1, int i, int j)
{
	char	*str;

	while (s1[i] == ' ')
		i++;
	while (s1[i] != ' ')
		i++;
	while (s1[i] == ' ' && s1[i])
		i++;
	while (s1[i + j] && s1[i + j] != ' ')
		j++;
	str = malloc(sizeof(char) * j + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (s1[i] && s1[i] != ' ')
		str[j++] = s1[i++];
	str[j] = 0;
	var->fd = open(str, O_RDONLY);
	if (var->fd == -1)
		return (free(str), NULL);
	close(var->fd);
	return (str);
}

int	check_num(char **temp)
{
	int	i;
	int	j;

	i = 0;
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
		{
			if (temp[i][j] > '9' || temp[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_copy_color(char **temp, int j)
{
	if (j < 4)
	{
		j = 0;
		while (temp[j])
			free(temp[j++]);
		free(temp);
		return (0);
	}
	if (ft_atoi(temp[1]) > 255 || ft_atoi(temp[1]) < 0
		|| ft_atoi(temp[2]) > 255 || ft_atoi(temp[2]) < 0
		|| ft_atoi(temp[3]) > 255 || ft_atoi(temp[3]) < 0)
	{
		j = 0;
		while (temp[j])
			free(temp[j++]);
		free(temp);
		return (0);
	}
	return (1);
}

int	copy_color(t_var *var, char *s1, int j)
{
	char	**temp;
	int		color;

	var->i2 = 0;
	temp = ft_split(s1, " ,", -1, 0);
	if (!temp)
	{
		while (temp[var->i2])
			free(temp[var->i2++]);
		free(temp);
		return (0);
	}
	j = 0;
	while (temp[j])
		j++;
	if (!check_copy_color(temp, j))
		return (-1);
	color = ft_atoi(temp[1]) << 16 | ft_atoi(temp[2]) << 8 | ft_atoi(temp[3]);
	j = 0;
	while (temp[j])
		free(temp[j++]);
	free(temp);
	return (color);
}

int	is_right_element(t_var *var, int i)
{
	while (var->element[i])
	{
		if (str_cmp(var->element[i], "NO ") && !var->north)
			var->north = copy_element(var, var->element[i], 0, 0);
		else if (str_cmp(var->element[i], "SO ") && !var->south)
			var->south = copy_element(var, var->element[i], 0, 0);
		else if (str_cmp(var->element[i], "WE ") && !var->west)
			var->west = copy_element(var, var->element[i], 0, 0);
		else if (str_cmp(var->element[i], "EA ") && !var->east)
			var->east = copy_element(var, var->element[i], 0, 0);
		if (str_cmp(var->element[i], "F ") && var->floor == -1)
			var->floor = copy_color(var, var->element[i], 0);
		if (str_cmp(var->element[i], "C ") && var->ceiling == -1)
			var->ceiling = copy_color(var, var->element[i], 0);
		i++;
	}
	if (!var->north || !var->south || !var->west || !var->east
		|| var->floor == -1 || var->ceiling == -1)
		return (printf("Error : Incorrect Elements\n"), 0);
	return (1);
}
