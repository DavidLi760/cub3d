/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:01:14 by davli             #+#    #+#             */
/*   Updated: 2024/10/26 19:22:59 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_order(t_var *var)
{
	var->spriteorder[0] = '0';
	var->spriteorder[1] = '0';
	var->spriteorder[2] = '0';
	if (var->iru >= var->iscp && var->iru >= var->iech)
		var->spriteorder[0] = 'r';
	else if (var->iru >= var->iech || var->iru >= var->iscp)
		var->spriteorder[1] = 'r';
	else
		var->spriteorder[2] = 'r';
	if (var->iscp >= var->iru && var->iscp >= var->iech)
		var->spriteorder[0] = 's';
	else if (var->iscp >= var->iech || var->iscp >= var->iru)
		var->spriteorder[1] = 's';
	else
		var->spriteorder[2] = 's';
	if (var->iech >= var->iru && var->iech >= var->iscp)
		var->spriteorder[0] = 'e';
	else if (var->iech >= var->iscp || var->iech >= var->iru)
		var->spriteorder[1] = 'e';
	else
		var->spriteorder[2] = 'e';
	var->spriteorder[3] = 0;
	print_monster(var, var->spriteorder);
}

void	help_boss(t_var *var)
{
	var->davlisize = 40000 / (var->idavli * 1.5);
	if (var->angledavli >= 0 && var->final <= 3)
		my_put_image_to_image6(var, var->angleddavli * 1920 - var->davlisize \
				/ 1.5, 500 - var->pitch - var->davlisize / 2, var->davlisize);
	else if (var->angledavli >= 0 && var->final > 3)
		my_put_image_to_image8(var, var->angleddavli * 1920 - var->davlisize \
				/ 1.5, 500 - var->pitch - var->davlisize / 2, var->davlisize);
}

void	print_boss(t_var *var)
{
	if (var->right_angle > var->left_angle && var->angledavli \
			> var->left_angle && var->angledavli < var->right_angle)
		var->angleddavli = (var->angledavli - var->left_angle) \
			/ (var->right_angle - var->left_angle);
	else if (var->right_angle < var->left_angle && var->angledavli \
			> var->right_angle && var->angledavli > var->left_angle)
		var->angleddavli = (var->angledavli - var->left_angle) / (2 * PI \
				- var->left_angle + var->right_angle);
	else if (var->right_angle < var->left_angle && var->angledavli \
			< var->right_angle && var->angledavli < var->left_angle)
		var->angleddavli = (var->angledavli + (2 * PI - var->left_angle)) \
			/ (2 * PI - var->left_angle + var->right_angle);
	else if (var->left_angle < var->right_angle && var->angledavli \
			> var->left_angle && var->angledavli > var->right_angle)
		var->angleddavli = (var->angledavli - 2 * PI - var->left_angle) \
			/ (var->right_angle - var->left_angle);
	else if (var->left_angle < var->right_angle && var->angledavli \
			< var->left_angle && var->angledavli < var->right_angle)
		var->angleddavli = (var->angledavli - var->left_angle) \
			/ (var->right_angle - var->left_angle);
	else if (var->left_angle > var->right_angle && var->angledavli \
			< var->left_angle && var->angledavli > var->right_angle)
		var->angleddavli = (var->angledavli - var->left_angle) \
		/ (2 * PI - var->left_angle + var->right_angle);
	help_boss(var);
}

void	help_boss2(t_var *var)
{
	var->usersize = 40000 / (var->iuser * 1.5);
	if (var->angleuser >= 0)
		my_put_image_to_image7(var, var->angleduser * 1920 - var->usersize \
				/ 1.5, 500 - var->pitch - var->usersize / 2, var->usersize);
}

void	print_boss2(t_var *var)
{
	if (var->right_angle > var->left_angle && var->angleuser \
			> var->left_angle && var->angleuser < var->right_angle)
		var->angleduser = (var->angleuser - var->left_angle) \
			/ (var->right_angle - var->left_angle);
	else if (var->right_angle < var->left_angle && var->angleuser \
			> var->right_angle && var->angleuser > var->left_angle)
		var->angleduser = (var->angleuser - var->left_angle) \
		/ (2 * PI - var->left_angle + var->right_angle);
	else if (var->right_angle < var->left_angle && var->angleuser \
			< var->right_angle && var->angleuser < var->left_angle)
		var->angleduser = (var->angleuser + (2 * PI - var->left_angle)) \
		/ (2 * PI - var->left_angle + var->right_angle);
	else if (var->left_angle < var->right_angle && var->angleuser \
			> var->left_angle && var->angleuser > var->right_angle)
		var->angleduser = (var->angleuser - 2 * PI - var->left_angle) \
		/ (var->right_angle - var->left_angle);
	else if (var->left_angle < var->right_angle && var->angleuser \
			< var->left_angle && var->angleuser < var->right_angle)
		var->angleduser = (var->angleuser - var->left_angle) / \
			(var->right_angle - var->left_angle);
	else if (var->left_angle > var->right_angle && var->angleuser < \
			var->left_angle && var->angleuser > var->right_angle)
		var->angleduser = (var->angleuser - var->left_angle) \
		/ (2 * PI - var->left_angle + var->right_angle);
	help_boss2(var);
}
