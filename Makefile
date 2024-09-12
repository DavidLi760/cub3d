NAME		= Cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -lX11 -lmlx -lXext -lm -lz -Lmlx
MLX			= mlx/libmlx.a
SRCS		=	main.c\
				parsing.c\
				parsing2.c\
				get_next_line.c\
				ft_split.c\
				utils.c\
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
