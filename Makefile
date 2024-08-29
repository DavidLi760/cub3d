NAME		= Cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LFLAGS		= -lX11 -lmlx -lXext -lm -lz -Lmlx
SRCS		= main.c
OBJS		= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
	rm -rf $(OBJS)

.PHONY : re all clean fclean
