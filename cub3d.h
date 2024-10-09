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
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include "mlx/mlx.h"

# define MS 10
# define DIST 30
# define MAP_SIZE 5000
# define HEIGHT 1010
# define BUFFER_SIZE 500
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
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
	char	*addr;
	char	*addr2;
	char	*addrd;
	char	*addrno;
	char	*addrso;
	char	*addrwe;
	char	*addrea;
	int		vide;
	int		len;
	int		len2;
	int		lend;
	int		lenno;
	int		lenso;
	int		lenwe;
	int		lenea;
	int		bit;
	int		bit2;
	int		bitd;
	int		bitno;
	int		bitso;
	int		bitwe;
	int		bitea;
	int		endian;
	int		endian2;
	int		endiand;
	int		endianno;
	int		endianso;
	int		endianwe;
	int		endianea;
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
	double		text_x;
	double		text_y;
	t_pos	position;
	t_pos	position2;
	int		health;
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
	int		shift_pressed;
	int		left_pressed;
	int		up_pressed;
	int		right_pressed;
	int		down_pressed;
	int		no;
	int		so;
	int		we;
	int		ea;
	double	door;
	double	door2;
	double	door3;
	double	doorx;
	double	doory;
	double	doortime;
	double	doortime2;
	double	doorsense;
	double	fermx;
	double	fermy;
	int		mix;
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

#endif