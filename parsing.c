/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:23:02 by davli             #+#    #+#             */
/*   Updated: 2024/09/05 15:19:09 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *str)
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
	return (0);
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

int	get_map(t_var *var)
{
	int	i;

	i = 0;
	var->split = ft_split(var->file, "\n");
	if (!var->split)
        return (printf("Error : Empty file\n"), 0);
	if (!count_line(var, 1))
		return (printf("Error : No map found\n"), 0);
    if (!count_line(var, 0))
        return (printf("Error : No texture found\n"), 0);
    var->element = malloc(sizeof(char *) * (count_line(var, 0) + 1));
    var->map = malloc(sizeof(char *) * (count_line(var, 1) + 1));
	if (!var->element || !var->map)
        return (0);
    
    return (1);
}

int	is_map_closed(t_var *var)
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
	if (!check_extension(argv[1]))
		return (0);
	if (!get_map(var))
		return (0);
	while (var->split[i])
		printf("%s\n", var->split[i++]);
	if (!is_map_closed(var))
		return (0);
	return (1);
}
