NAME = so_long

SRCS = so_long.c \
       so_long2.c \
       utils.c \
       map_utils.c \
       map_utils2.c \
       map_validator.c \
       map_validator2.c \
       window_utils.c \
       window_utils2.c \
       window_utils3.c \
       window_utils4.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# MiniLibX
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS)
	$(CC) $(OBJS) $(GNL_OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re