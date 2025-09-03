# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_username <your_email@example.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/02 00:00:00 by username          #+#    #+#              #
#    Updated: 2025/09/02 00:00:00 by username         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

# Compiler and flags (as required by subject)
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -Iget_next_line -Iminilibx-linux

# Libraries
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Get Next Line
GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

# Libft (if using)
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Source files
SRCS = so_long.c \
       map_utils.c \
       map_validator.c \
       utils.c \
       window_utils.c

OBJS = $(SRCS:.c=.o)

# Bonus files
BONUS_SRCS = so_long_bonus.c \
             map_utils_bonus.c \
             map_validator_bonus.c \
             utils_bonus.c \
             window_utils_bonus.c \
             enemy_bonus.c \
             animation_bonus.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Default rule
all: $(NAME)

# Check if libft exists and build it
$(LIBFT_LIB):
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR); \
	fi

# Build MiniLibX
$(MLX_LIB):
	@make -C $(MLX_DIR)

# Build main executable
$(NAME): $(MLX_LIB) $(GNL_OBJS) $(OBJS)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR); \
		$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME); \
	else \
		$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(MLX_FLAGS) -o $(NAME); \
	fi

# Build bonus executable
bonus: $(MLX_LIB) $(GNL_OBJS) $(BONUS_OBJS)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR); \
		$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME); \
	else \
		$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) $(MLX_FLAGS) -o $(NAME); \
	fi

# Compile object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(GNL_OBJS)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR) clean; \
	fi
	@if [ -d "$(MLX_DIR)" ]; then \
		make -C $(MLX_DIR) clean; \
	fi

# Clean everything
fclean: clean
	rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR) fclean; \
	fi

# Rebuild everything
re: fclean all

# Phony targets to avoid conflicts with files of the same name
.PHONY: all clean fclean re bonus