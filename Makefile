NAME		= Cub3D
CC			= gcc
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
				forbidden.c\
				forbidden2.c\
				parsing.c\
				parsing2.c\
				parsing3.c\
				get_next_line.c\
				ft_split.c\
				ft_atoi.c\
				utils.c\
				walking.c\
				monster.c\
				ft_itoa.c\
				scenario.c\
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
