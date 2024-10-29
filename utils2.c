/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:09:49 by davli             #+#    #+#             */
/*   Updated: 2024/10/29 11:11:10 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long long	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	str_cmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[j] == ' ' && s1[j])
		j++;
	if (s1[i + j] != s2[i])
		return (0);
	while (s1[i + j] == s2[i] && s2[i])
		i++;
	if (s1[i + j] != s2[i] && s2[i])
		return (0);
	return (1);
}

void	my_pixel_put(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->addr + (y * var->len + x * (var->bit / 8));
	*(unsigned int *)dst = color;
}

void	my_pixel_put2(t_var *var, int x, int y, int color)
{
	char	*dst;

	dst = var->addr2 + (y * var->len2 + x * (var->bit2 / 8));
	*(unsigned int *)dst = color;
}

int	is_charset(char c, char *set)
{
	int	i;

	i = 0;
	while (c != set[i] && set[i])
		i++;
	if (!set[i])
		return (0);
	return (1);
}
