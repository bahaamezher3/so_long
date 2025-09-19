NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = so_long.c so_long2.c so_long3.c so_long4.c so_long5.c so_long6.c\
       map_utils.c map_utils2.c \
       map_validator.c map_validator2.c map_validator3.c \
       window_utils.c window_utils2.c window_utils3.c window_utils4.c window_utils5.c window_utils6.c \
       utils.c \
       get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

LIBMLX = minilibx-linux/libmlx.a
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(LIBMLX) $(NAME)

$(LIBMLX):
	make -C minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C minilibx-linux

fclean: clean
	rm -f $(NAME)
	make clean -C minilibx-linux

re: fclean all

.PHONY: all clean fclean re