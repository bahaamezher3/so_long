#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define TILE_SIZE 32
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
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     map_width;
    int     map_height;
    t_img   player;
    t_img   wall;
    t_img   collectible;
    t_img   exit;
    t_img   floor;
    int     player_x;
    int     player_y;
    int     collectibles;
    int     moves;
}   t_game;

/* Main functions */
char    **read_map_with_error_handle(char *filename);
void    map_dimensioner(char *filename, int *height, int *width);
int     get_clean_length(char *line);
void    freer(char **map, int i);
int     check_file_access(char *filename);

/* Map validation functions */
int     check_path(char **map, int max_i, int max_j);
int     check_boundaries(char **map, int max_i, int max_j);
int     validate_elements(char **map, int max_i, int max_j);
int     check_collectibles_reachable(char **map, char **map_copy, int max_i, int max_j);
int     check_exit_reachable(char **map, char **map_copy, int max_i, int max_j);
void    map_validator(char **map, int max_i, int max_j);

/* Map utilities */
void    dfs_collectibles(char **map, int i, int j, int max_i, int max_j);
void    dfs_exit(char **map, int i, int j, int max_i, int max_j);
char    **map_dup(char **map, int max_i, int max_j);
int     find_player_and_run_dfs_collectibles(char **map_copy, int max_i, int max_j);
int     find_player_and_run_dfs_exit(char **map_copy, int max_i, int max_j);

/* Game functions */
void    init_game(t_game *game);
void    load_images(t_game *game);
void    find_player_position(t_game *game);
void    count_collectibles(t_game *game);
void    draw_tile(t_game *game, int x, int y);
void    draw_map(t_game *game);
int     handle_keypress(int keycode, t_game *game);
int     handle_close(t_game *game);

/* Utility functions */
void    put_nbr(int n);
int     ft_strlen_custom(const char *s);
void    *ft_memset(void *s, int c, size_t n);

#endif