/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define TILE_SIZE 64
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

# define EXIT_SUCCESS 0
# define EXIT_ERROR 1
# define EXIT_MALLOC_ERROR 2
# define EXIT_MAP_ERROR 3

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	t_img	player;
	t_img	wall;
	t_img	collectible;
	t_img	exit;
	t_img	floor;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
}	t_game;

typedef struct s_move
{
	int	old_x;
	int	old_y;
	int	new_x;
	int	new_y;
}	t_move;

char	**read_map_with_error_handle(char *filename);
void	map_dimensioner(char *filename, int *height, int *width);
int		get_clean_length(char *line);
void	freer(char **map, int i);
int		check_file_access(char *filename);

int		check_path(char **map, int max_i, int max_j);
int		check_boundaries(char **map, int max_i, int max_j);
int		validate_elements(char **map, int max_i, int max_j);
int		update_counts_and_validate_cell(char cell, int *count_p,
			int *count_e, int *count_c);
int		check_collectibles_reachable(char **map, char **map_copy,
			int max_i, int max_j);
int		check_exit_reachable(char **map, char **map_copy,
			int max_i, int max_j);
void	map_validator(char **map, int max_i, int max_j);

void	dfs_collectibles(char **map, int i, int j, int dims[2]);
void	dfs_exit(char **map, int i, int j, int dims[2]);
char	**map_dup(char **map, int max_i, int max_j);
int		find_player_and_run_dfs_collectibles(char **map_copy,
			int max_i, int max_j);
int		find_player_and_run_dfs_exit(char **map_copy, int max_i, int max_j);

void	init_game(t_game *game);
void	load_images(t_game *game);
void	find_player_position(t_game *game);
void	count_collectibles(t_game *game);
void	draw_tile(t_game *game, int x, int y);
void	draw_map(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);

void	put_nbr(int n);
int		ft_strlen_custom(const char *s);

void	init_img_struct(t_img *img);
void	init_game_values(t_game *game);
void	cleanup_on_init_error(t_game *game);
void	load_single_image(t_game *game, t_img *img, char *path);
void	cleanup_images_on_error(t_game *game);
void	handle_image_load_error(t_game *game, char *path, char *prefix);
void	validate_and_get_image_data(t_game *game, t_img *img, char *path);
int		move_player(t_game *game, int new_x, int new_y);
void	redraw_player_move(t_game *game, t_move move);
void	handle_win_condition(t_game *game);
void	update_player_position(t_game *game, int new_x, int new_y);
int		handle_expose(t_game *game);

void	error_exit(char *message);
void	error_exit_with_cleanup(char *message, char **map, int max_i);
int		check_element_counts(int count_p, int count_e, int count_c);
int		validate_map_basic_checks(char **map, int max_i, int max_j);
int		validate_collectibles_path(char **map, int max_i, int max_j);
int		validate_exit_path(char **map, int max_i, int max_j);

int		read_and_process_line(int fd, int *expected_len, int *line_count);
int		open_or_exit_ro(char *filename);
char	**allocate_map_or_exit(int fd, int max_i);
void	handle_read_result(int result, char **map_fill, int max_i, int fd);
void	init_dimension_counters(int *height, int *width,
			int *line_count, int *expected_len);
void	validate_dimensions_or_exit(int line_count, int expected_len);
void	scan_dimensions(int fd, int *expected_len, int *line_count);

char	*allocate_map_row(int max_j);
void	copy_map_row(char **copy, char **map, int i, int max_j);
void	free_partial_map(char **copy, int allocated_rows);
void	init_map_pointers(char **copy, int max_i);

int		check_file_extension(char *filename);
void	validate_line_length_and_cleanup(char *tmp, int len,
			int expected_len, int fd);

char	**allocate_map(int max_i);
int		read_map_lines(int fd, char **map_fill, int max_i);
void	init_and_validate_game(t_game *game, char **argv);
void	setup_game_graphics(t_game *game);
void	cleanup_and_exit(t_game *game, int exit_code);

#endif