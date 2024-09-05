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

int	find_max(int i, char **argv)
{
	int	j;
	int	max;

	max = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			j++;
		if (max < j)
			max = j;
		i++;
	}
	return (max);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int	i;

	i = 0;
	i = find_max(i, argv);
	printf("%d\n", i);
	// while (argv[i])
	// 	printf("%s\n", argv[i++]);
}
