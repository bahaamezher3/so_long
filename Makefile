NAME = so_long
MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

SRCS = so_long.c \
       map_utils.c \
       map_validator.c \
       utils.c \
       window_utils.c \
       get_next_line/get_next_line.c \
       get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(MLX) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -Iget_next_line -Iminilibx-linux -c $< -o $@

clean:
	$(MAKE) -C $(MLX_PATH) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(MLX)
