/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:38:23 by davli             #+#    #+#             */
/*   Updated: 2024/09/05 16:40:29 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_corner(char **map, int i, int j, int max)
{
	while (map[i])
		i++;
	max = i - 1;
	while (map[0][++j])
		if (map[0][j] == '0')
			return (0);
	j = -1;
	while (map[max][++j])
		if (map[max][j] == '0')
			return (0);
	i = -1;
	while (++i <= max)
		if (map[i][0] == '0')
			return (0);
	i = -1;
	while (++i <= max)
		if (map[i][j - 1] == '0')
			return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int	i;

	i = 0;
	int	fd = open(argv[1], O_RDONLY);
	char *mapp = get_next_line(fd);
	char **map = ft_split(mapp, "\n");
	check_corner(map, 0, -1, 0);
	printf("%d\n", check_corner(map, 0, -1, 0));
	// while (argv[i])
	// 	printf("%s\n", argv[i++]);
}
