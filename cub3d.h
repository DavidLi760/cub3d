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
# include <math.h>
# include "mlx/mlx.h"

# define DELAY 500
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
	void	*img1;
	void	*img2;
	void	*img3;
	void	*imag;
	char	*addr;
	int		len;
	int		bit;
	int		endian;
	int		diff_x;
	int		diff_y;
	bool	**forbidden;
	char	*file;
	char	**split;
	char	**element;
	char	**map;
	int		player;
	double	anglex;
	double	angley;
	t_pos	position;
	t_pos	position2;
	int		max;
	int		maxj;
	int		fd;
	int		width;
	int		height;
	int		delay;
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
}	t_var;

int check_arg(t_var *var, char **argv);
size_t	ft_strlen(char *s);
char	*get_next_line(int fd);
char	**ft_split(char *str, char *set);
int		get_split(t_var *var, int i, int j);
void	free_list(t_var *var);
void	free2(t_var *var, int no);
void	free3(t_var *var, int i);
void	free4(t_var *var, int no);
int		count_line(t_var *var, int no);
void	my_pixel_put(t_var *var, int x, int y, int color);
void	draw_block(t_var *var, int i, int j, int color);
void	draw_wall(t_var *var, int i, int j, int color);

#endif
