#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../get_next_line/get_next_line.h"

char    **read_map_with_error_handle(char *filename);
void    map_dimentioner(char *filename, int *a, int *b);
int     get_clean_length(char *line);
void    freer(char **map, int i);
int     check_path(char **map, int max_i, int max_j);
int     check_boundaries(char **map, int max_i, int max_j);
int     validate_elements(char **map, int max_i, int max_j);
int     check_reachability(char **map, char **map_copy, int max_i, int max_j);
void    map_validator(char **map, int max_i, int max_j);
void    dfs(char **map, int i, int j, int max_i, int max_j);
char    **map_dup(char **map, int max_i, int max_j);
int     find_player_and_run_dfs(char **map_copy, int max_i, int max_j);
int     check_file_access(char *filename);

#endif