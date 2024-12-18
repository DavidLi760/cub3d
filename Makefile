NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lX11 -lmlx -lXext -lm -lz -Lmlx
MLX			= mlx/libmlx.a
SRCS		=	main.c\
				init.c\
				init_img.c\
				init_utils.c\
				init_monster.c\
				hooks.c\
				update.c\
				update2.c\
				update3.c\
				sprite_order.c\
				ray_cast.c\
				draw_render.c\
				drawing_utils.c\
				forbidden.c\
				forbidden2.c\
				minimap.c\
				draw_ray.c\
				parsing.c\
				parsing2.c\
				parsing3.c\
				parsing4.c\
				get_next_line.c\
				ft_split.c\
				ft_atoi.c\
				utils.c\
				utils2.c\
				utils3.c\
				utils4.c\
				walking.c\
				monster.c\
				monster2.c\
				ft_itoa.c\
				scenario.c\
				scenario2.c\
				scenario3.c\
				free.c
OBJS		= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LFLAGS) -o $(NAME)

$(MLX) :
	make -C mlx

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
	rm -rf $(OBJS)

.PHONY : re all clean fclean
