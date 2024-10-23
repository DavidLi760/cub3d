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

int	check_corner(t_var *var, int i, int j, int max)
{
	while (var->map[i])
		i++;
	max = i - 1;
	while (var->map[0][++j])
		if (var->map[0][j] == '0' || var->map[0][j] == '2' || var->map[0][j] == '3')
			return (printf("Error : Wall not closed\n"), 0);
	j = -1;
	while (var->map[max][++j])
		if (var->map[max][j] == '0' || var->map[max][j] == '2' || var->map[max][j] == '3')
			return (printf("Error : Wall not closed\n"), 0);
	i = -1;
	while (++i <= max)
		if (var->map[i][0] == '0' || var->map[i][0] == '2' || var->map[i][0] == '3')
			return (printf("Error : Wall not closed\n"), 0);
	i = -1;
	while (++i <= max)
		if (var->map[i][j - 1] == '0' || var->map[i][j - 1] == '2' || var->map[i][j - 1] == '3')
			return (printf("Error : Wall not closed\n"), 0);
	return (1);
}

int	is_wall_closed(t_var *var, int i, int j)
{
	if (!check_corner(var, 0, -1, 0))
		return (free4(var, -1, 0), 0);
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] == '0' || var->map[i][j] == 'W'
				|| var->map[i][j] == 'E' || var->map[i][j] == 'S'
				|| var->map[i][j] == 'N' || var->map[i][j] == '2'
				|| var->map[i][j] == '3')
			{
				if (var->map[i - 1][j] == ' ' || var->map[i + 1][j] == ' '
					|| var->map[i][j - 1] == ' ' || var->map[i][j + 1] == ' ')
				{
					printf("Error : Wall not correctly closed\n");
					return (free4(var, -1, 0), 0);
				}
			}
			j++;
		}
		i++;
	}
	var->max = i;
	return (1);
}

int	is_right_char(t_var *var, int i, int j)
{
	while (var->map[i])
	{
		j = 0;
		while (var->map[i][j])
		{
			if (var->map[i][j] != 'E' && var->map[i][j] != 'W'
				&& var->map[i][j] != 'N' && var->map[i][j] != 'S'
				&& var->map[i][j] != ' ' && var->map[i][j] != '0'
				&& var->map[i][j] != '1' && var->map[i][j] != '2'
				&& var->map[i][j] != '3' && var->map[i][j] != '6'
				&& var->map[i][j] != 'r' && var->map[i][j] != 'p'
				&& var->map[i][j] != 's' && var->map[i][j] != 'e'
				&& var->map[i][j] != 'D')
				return (printf("Error : Unknown character on the map\n"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

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

int	check_arg(t_var *var, char **argv)
{
	var->fd = open(argv[1], O_RDONLY);
	var->file = get_next_line(var->fd);
	close(var->fd);
	if (!var->file)
		return (printf("Error : File don't exist\n"), 0);
	if (!check_extension(var, argv[1]))
		return (0);
	if (!get_split(var, -1, 0))
		return (free(var->file), 0);
	if (!is_wall_closed(var, 0, 0))
		return (0);
	if (!is_right_char(var, 0, 0) || !is_player_valid(var, 0, 0))
		return (free4(var, 0, 0), 0);
	if (!is_right_element(var, 0))
		return (free4(var, -1, 0), 0);
	return (1);
}
