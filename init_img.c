/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:10:18 by davli             #+#    #+#             */
/*   Updated: 2024/10/28 17:10:18 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_img1(t_var *var)
{
	var->img = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/Red_dot.xpm", &var->width, &var->height);
	if (!var->img)
		return (0);
	var->imgd = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/Door.xpm", &var->width1, &var->height1);
	if (!var->imgd)
		return (0);
	var->imgp = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/Closet.xpm", &var->width1, &var->height1);
	if (!var->imgp)
		return (0);
	var->imgru1 = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/Rush1.xpm", &var->widthru1, &var->heightru1);
	if (!var->imgru1)
		return (0);
	var->imgru2 = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/Rush2.xpm", &var->widthru2, &var->heightru2);
	if (!var->imgru2)
		return (0);
	var->imgscp = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/SCP173.xpm", &var->widthscp, &var->heightscp);
	if (!var->imgscp)
		return (0);
	return (1);
}

int	init_img2(t_var *var)
{
	var->imgscp2 = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/SCP173_2.xpm", &var->widthscp2, &var->heightscp2);
	if (!var->imgscp2)
		return (0);
	var->imgech = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/Screech1.xpm", &var->widthech, &var->heightech);
	if (!var->imgech)
		return (0);
	var->imgech2 = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/Screech2.xpm", &var->widthech2, &var->heightech2);
	if (!var->imgech2)
		return (0);
	var->imgdavli = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/davli.xpm", &var->widthdavli, &var->heightdavli);
	if (!var->imgdavli)
		return (0);
	var->imgdavli2 = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/davli2.xpm", &var->widthdavli2, &var->heightdavli2);
	if (!var->imgdavli2)
		return (0);
	var->imguser = mlx_xpm_file_to_image(var->mlx, \
	"./xpms/fflamion.xpm", &var->widthuser, &var->heightuser);
	if (!var->imguser)
		return (0);
	return (1);
}

int	init_img3(t_var *var)
{
	var->addrd = \
	mlx_get_data_addr(var->imgd, &var->bitd, &var->lend, &var->endiand);
	if (!var->addrd)
		return (0);
	var->addrp = \
	mlx_get_data_addr(var->imgp, &var->bitp, &var->lenp, &var->endianp);
	if (!var->addrp)
		return (0);
	var->imag = mlx_new_image(var->mlx, 150, 150);
	if (!var->imag)
		return (0);
	var->addr = \
	mlx_get_data_addr(var->imag, &var->bit, &var->len, &var->endian);
	if (!var->addr)
		return (0);
	var->addrru1 = \
	mlx_get_data_addr(var->imgru1, &var->bitru1, &var->lenru1, &var->endianru1);
	if (!var->addrru1)
		return (0);
	var->addrru2 = \
	mlx_get_data_addr(var->imgru2, &var->bitru2, &var->lenru2, &var->endianru2);
	if (!var->addrru2)
		return (0);
	return (1);
}

int	init_img4(t_var *var)
{
	var->addrscp = \
	mlx_get_data_addr(var->imgscp, &var->bitscp, &var->lenscp, &var->endianscp);
	if (!var->addrscp)
		return (0);
	var->addrscp2 = mlx_get_data_addr(var->imgscp2, \
	&var->bitscp2, &var->lenscp2, &var->endianscp2);
	if (!var->addrscp2)
		return (0);
	var->addrech = \
	mlx_get_data_addr(var->imgech, &var->bitech, &var->lenech, &var->endianech);
	if (!var->addrech)
		return (0);
	var->addrech2 = mlx_get_data_addr(var->imgech2, \
	&var->bitech2, &var->lenech2, &var->endianech2);
	if (!var->addrech2)
		return (0);
	var->addrdavli = mlx_get_data_addr(var->imgdavli, \
	&var->bitdavli, &var->lendavli, &var->endiandavli);
	if (!var->addrdavli)
		return (0);
	var->addrdavli2 = mlx_get_data_addr(var->imgdavli2, \
	&var->bitdavli2, &var->lendavli2, &var->endiandavli2);
	if (!var->addrdavli2)
		return (0);
	return (1);
}

int	init_img5(t_var *var)
{
	var->addruser = mlx_get_data_addr(var->imguser, \
	&var->bituser, &var->lenuser, &var->endianuser);
	if (!var->addruser)
		return (0);
	var->imgno = mlx_xpm_file_to_image(var->mlx, \
	var->north, &var->widthno, &var->heightno);
	if (!var->imgno)
		return (0);
	var->imgso = mlx_xpm_file_to_image(var->mlx, \
	var->south, &var->widthso, &var->heightso);
	if (!var->imgso)
		return (0);
	var->imgwe = mlx_xpm_file_to_image(var->mlx, \
	var->west, &var->widthwe, &var->heightwe);
	if (!var->imgwe)
		return (0);
	return (1);
}
