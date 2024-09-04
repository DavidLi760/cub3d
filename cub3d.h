/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davli <davli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:06:18 by davli             #+#    #+#             */
/*   Updated: 2024/09/04 17:09:52 by davli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx/mlx.h"

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

typedef struct s_var
{
	void	*mlx;
	void	*win;
	void	*img;
	double	dot_x;
	double	dot_y;
	char	*file;
	char	**split;
	char	**element;
	char	**map;
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

#endif
