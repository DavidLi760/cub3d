/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:10:52 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 19:01:07 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_monster2(t_var *var, char *tab, int i)
{
	if (tab[i] == 'r' && var->angleru >= 0)
		my_put_image_to_image(var, var->angledru * 1920 - var->rusize \
		/ 1.5, 500 - var->pitch - var->rusize / 2, var->rusize);
	if (tab[i] == 's' && var->anglescp >= 0 && var->angledscp > 0.1 && \
	var->angledscp < 0.8 && var->iscp > 15)
		my_put_image_to_image3(var, var->angledscp * 1920 - (var->scpsize \
		/ 2), 500 - var->pitch - var->scpsize / 2, var->scpsize);
	else if (tab[i] == 's' && ((var->anglescp >= 0 && (var->angledscp < \
	0.1 || var->angledscp > 0.8)) || var->iscp <= 15))
		my_put_image_to_image4(var, var->angledscp * 1920 - (var->scpsize \
		/ 2), 500 - var->pitch - var->scpsize / 2, var->scpsize);
	if (tab[i] == 'e' && var->angleech >= 0 && var->highech == 1
		&& var->screech)
		my_put_image_to_image5(var, var->angledech * 1920 - var->echsize \
		/ 1.5, -400 - var->pitch - var->echsize / 2, var->echsize);
	else if (tab[i] == 'e' && var->angleech >= 0
		&& var->highech == 2 && var->screech)
		my_put_image_to_image5(var, var->angledech * 1920 - var->echsize \
		/ 1.5, 1400 - var->pitch - var->echsize / 2, var->echsize);
}

void	print_monster(t_var *var, char *tab)
{
	int	i;

	i = 0;
	if (var->angleru >= 0)
		rush(var);
	if (var->anglescp >= 0)
		scp173(var);
	if (var->angleech >= 0)
		screech(var);
	while (i < 3)
	{
		print_monster2(var, tab, i);
		i++;
	}
}

void	rush(t_var *var)
{
	if (var->right_angle > var->left_angle && var->angleru > \
	var->left_angle && var->angleru < var->right_angle)
		var->angledru = (var->angleru - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->right_angle < var->left_angle && var->angleru > \
	var->right_angle && var->angleru > var->left_angle)
		var->angledru = (var->angleru - var->left_angle) / (2 * PI - \
		var->left_angle + var->right_angle);
	else if (var->right_angle < var->left_angle && var->angleru < \
	var->right_angle && var->angleru < var->left_angle)
		var->angledru = (var->angleru + (2 * PI - var->left_angle)) \
		/ (2 * PI - var->left_angle + var->right_angle);
	else if (var->left_angle < var->right_angle && var->angleru > \
	var->left_angle && var->angleru > var->right_angle)
		var->angledru = (var->angleru - 2 * PI - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->left_angle < var->right_angle && var->angleru < \
	var->left_angle && var->angleru < var->right_angle)
		var->angledru = (var->angleru - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->left_angle > var->right_angle && var->angleru < \
	var->left_angle && var->angleru > var->right_angle)
		var->angledru = (var->angleru - var->left_angle) / (2 * \
		PI - var->left_angle + var->right_angle);
	var->rusize = 40000 / (var->iru * 1.5);
}

void	scp173(t_var *var)
{
	if (var->right_angle > var->left_angle && var->anglescp > var->left_angle
		&& var->anglescp < var->right_angle)
		var->angledscp = (var->anglescp - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->right_angle < var->left_angle && var->anglescp > \
	var->right_angle && var->anglescp > var->left_angle)
		var->angledscp = (var->anglescp - var->left_angle) / (2 * PI - \
		var->left_angle + var->right_angle);
	else if (var->right_angle < var->left_angle && var->anglescp < \
	var->right_angle && var->anglescp < var->left_angle)
		var->angledscp = (var->anglescp + (2 * PI - var->left_angle)) / (2 * \
		PI - var->left_angle + var->right_angle);
	else if (var->left_angle < var->right_angle && var->anglescp > \
	var->left_angle && var->anglescp > var->right_angle)
		var->angledscp = (var->anglescp - 2 * PI - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->left_angle < var->right_angle && var->anglescp < \
	var->left_angle && var->anglescp < var->right_angle)
		var->angledscp = (var->anglescp - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->left_angle > var->right_angle && var->anglescp < \
	var->left_angle && var->anglescp > var->right_angle)
		var->angledscp = (var->anglescp - var->left_angle) / (2 * PI - \
		var->left_angle + var->right_angle);
	scp_mechanics(var);
}

void	screech(t_var *var)
{
	if (var->right_angle > var->left_angle && var->angleech > \
	var->left_angle && var->angleech < var->right_angle)
		var->angledech = (var->angleech - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->right_angle < var->left_angle && var->angleech > \
	var->right_angle && var->angleech > var->left_angle)
		var->angledech = (var->angleech - var->left_angle) / (2 * PI - \
		var->left_angle + var->right_angle);
	else if (var->right_angle < var->left_angle && var->angleech < \
	var->right_angle && var->angleech < var->left_angle)
		var->angledech = (var->angleech + (2 * PI - var->left_angle)) / \
		(2 * PI - var->left_angle + var->right_angle);
	else if (var->left_angle < var->right_angle && var->angleech > \
	var->left_angle && var->angleech > var->right_angle)
		var->angledech = (var->angleech - 2 * PI - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->left_angle < var->right_angle && var->angleech < \
	var->left_angle && var->angleech < var->right_angle)
		var->angledech = (var->angleech - var->left_angle) / \
		(var->right_angle - var->left_angle);
	else if (var->left_angle > var->right_angle && var->angleech < \
	var->left_angle && var->angleech > var->right_angle)
		var->angledech = (var->angleech - var->left_angle) / (2 * PI - \
		var->left_angle + var->right_angle);
	screech2(var);
}
