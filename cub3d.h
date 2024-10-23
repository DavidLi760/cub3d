/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:06:18 by davli             #+#    #+#             */
/*   Updated: 2024/09/12 14:01:35 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "mlx/mlx.h"

# define MS 10
# define DIST 200
# define MAP_SIZE 5000
# define HEIGHT 1010
# define BUFFER_SIZE 42
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define M 109
# define SHIFT 65505
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define PI 3.14159265358

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_var
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*imag;
	void	*imag2;
	void	*imgd;
	void	*imgno;
	void	*imgso;
	void	*imgwe;
	void	*imgea;
	void	*imgru1;
	void	*imgru2;
	void	*imgp;
	void	*imgscp;
	void	*imgscp2;
	void	*imgech;
	void	*imgech2;
	void	*imgdavli;
	void	*imgdavli2;
	void	*imguser;

	char	*addr;
	char	*addr2;
	char	*addrd;
	char	*addrno;
	char	*addrso;
	char	*addrwe;
	char	*addrea;
	char	*addrru1;
	char	*addrru2;
	char	*addrp;
	char	*addrscp;
	char	*addrscp2;
	char	*addrech;
	char	*addrech2;
	char	*addrdavli;
	char	*addrdavli2;
	char	*addruser;

	int		len;
	int		len2;
	int		lend;
	int		lenno;
	int		lenso;
	int		lenwe;
	int		lenea;
	int		lenru1;
	int		lenru2;
	int		lenp;
	int		lenscp;
	int		lenscp2;
	int		lenech;
	int		lenech2;
	int		lendavli;
	int		lendavli2;
	int		lenuser;

	int		bit;
	int		bit2;
	int		bitd;
	int		bitno;
	int		bitso;
	int		bitwe;
	int		bitea;
	int		bitru1;
	int		bitru2;
	int		bitp;
	int		bitscp;
	int		bitscp2;
	int		bitech;
	int		bitech2;
	int		bitdavli;
	int		bitdavli2;
	int		bituser;

	int		endian;
	int		endian2;
	int		endiand;
	int		endianno;
	int		endianso;
	int		endianwe;
	int		endianea;
	int		endianru1;
	int		endianru2;
	int		endianp;
	int		endianscp;
	int		endianscp2;
	int		endianech;
	int		endianech2;
	int		endiandavli;
	int		endiandavli2;
	int		endianuser;

	int		diff_x;
	int		diff_y;
	char	**forbidden;
	char	*file;
	char	**split;
	char	**element;
	char	**map;
	int		player;
	double	directx;
	double	directy;
	int		pitch;
	double	pitch2;
	double	angle;
	double	posx;
	double	posy;
	double	wall_x;
	double	wall_y;
	double	plusx;
	double	plusy;
	double	dist;
	double	ray_angle;
	double	text_x;
	double	text_y;
	double	xru;
	double	yru;
	t_pos	position;
	t_pos	position2;
	int		health;
	int		energy;
	int		max;
	int		maxj;
	int		maximum;
	int		fd;
	int		width;
	int		height;
	int		width1;
	int		height1;
	int		widthno;
	int		heightno;
	int		widthso;
	int		heightso;
	int		widthwe;
	int		heightwe;
	int		widthea;
	int		heightea;
	int		delay;

	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;

	int		w_pressed;
	int		a_pressed;
	int		s_pressed;
	int		d_pressed;
	int		e_pressed;
	int		m_pressed;
	int		shift_pressed;
	int		left_pressed;
	int		up_pressed;
	int		right_pressed;
	int		down_pressed;

	int		no;
	int		so;
	int		we;
	int		ea;
	int		vide;
	int		sprite;

	int		door;
	int		door2;
	int		door3;
	double	doorx;
	double	doory;
	double	doortime;
	double	doortime2;
	double	doorsense;

	double	iru;
	double	angleru;
	double	angledru;
	double	rusize;
	double	ru;
	int		ru2;
	int		rusens;
	int		widthru1;
	int		widthru2;
	int		heightru1;
	int		heightru2;

	double	xscp;
	double	yscp;
	double	iscp;
	double	anglescp;
	double	angledscp;
	double	scpsize;
	int		widthscp;
	int		widthscp2;
	int		heightscp;
	int		heightscp2;

	double	xech;
	double	yech;
	double	iech;
	double	angleech;
	double	angledech;
	double	echsize;
	double	xangleech;
	double	yangleech;
	double	highech;
	int		lookech;
	int		timeech;
	int		attackech;
	int		numberech;
	int		widthech;
	int		widthech2;
	int		heightech;
	int		heightech2;

	double	xdavli;
	double	ydavli;
	double	idavli;
	double	angledavli;
	double	angleddavli;
	double	davlisize;
	int		widthdavli;
	int		widthdavli2;
	int		heightdavli;
	int		heightdavli2;

	double	xuser;
	double	yuser;
	double	iuser;
	double	angleuser;
	double	angleduser;
	double	usersize;
	int		widthuser;
	int		heightuser;
	int		mix;
	int		closet;
	int		closet2;
	int		closet3;
	double	closetx;
	double	closety;
	double	closet2x;
	double	closet2y;
	char	sens;
	double	left_angle;
	double	right_angle;
	double	inter;
	double	*i;
	int		distance;
	char	spriteorder[3];
	int		screech;
	int		scp173;
	int		rush;
	int		money;
	int		died;
	double	deathx;
	double	deathy;
	int		doornumber;
	int		final;
}	t_var;

long long	get_time(void);
int			check_arg(t_var *var, char **argv);
size_t		ft_strlen(char *s);
char		*get_next_line(int fd);
char		**ft_split(char *str, char *set);
int			get_split(t_var *var, int i, int j);
void		free_list(t_var *var);
void		free2(t_var *var, int no);
void		free3(t_var *var, int i);
void		free4(t_var *var, int no, int i);
int			count_line(t_var *var, int no);
void		my_pixel_put(t_var *var, int x, int y, int color);
void		my_pixel_put2(t_var *var, int x, int y, int color);
int			my_pixel_from_texture(t_var *var, int x, int y, char no);
void		draw_block(t_var *var, int i, int j, int color);
void		draw_wall(t_var *var, int i, int j, int color);
void		draw_door(t_var *var, int i, int j, int no);
void		init_forbidden(t_var *var, int i, int j);
int			str_cmp(char *s1, char *s2);
int			is_right_element(t_var *var, int i);
int			ft_atoi(const char *str);
void		walking_w(t_var *var);
void		my_put_image_to_image(t_var *var, int x, int y, int size);
void		my_put_image_to_image2(t_var *var, int x, int y, int size);
void		my_put_image_to_image3(t_var *var, int x, int y, int size);
void		my_put_image_to_image4(t_var *var, int x, int y, int size);
void		my_put_image_to_image5(t_var *var, int x, int y, int size);
void		my_put_image_to_image6(t_var *var, int x, int y, int size);
void		my_put_image_to_image7(t_var *var, int x, int y, int size);
void		my_put_image_to_image8(t_var *var, int x, int y, int size);

void		rush(t_var *var);
void		scp173(t_var *var);
void		screech(t_var *var);
void		print_monster(t_var *var, char *tab);
char		*ft_itoa(int nb);
void		scenario(t_var *var);

#endif