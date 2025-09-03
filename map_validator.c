#include "so_long.h"

static void error_exit(char *message)
{
    write(2, "Error\n", 6);
    if (message)
    {
        write(2, message, ft_strlen_custom(message));
        write(2, "\n", 1);
    }
    exit(EXIT_ERROR);
}

int check_boundaries(char **map, int max_i, int max_j)
{
    int i;
    int j;

    if (!map)
        return (0);

    if (max_i < 3 || max_j < 3)
        return (0);

    // Check top and bottom walls
    j = 0;
    while (j < max_j)
    {
        if (map[0][j] != '1' || map[max_i - 1][j] != '1')
            return (0);
        j++;
    }

    // Check left and right walls
    i = 0;
    while (i < max_i)
    {
        if (map[i][0] != '1' || map[i][max_j - 1] != '1')
            return (0);
        i++;
    }

    return (1);
}

static int check_element_counts(int count_p, int count_e, int count_c)
{
    if (count_p != 1)
        return (0);
    if (count_e != 1)
        return (0);
    if (count_c < 1)
        return (0);
    return (1);
}

int validate_elements(char **map, int max_i, int max_j)
{
    int i;
    int j;
    int count_e;
    int count_c;
    int count_p;

    count_c = 0;
    count_e = 0;
    count_p = 0;
    i = 0;
    while (i < max_i)
    {
        j = 0;
        while (j < max_j)
        {
            if (map[i][j] == 'P')
                count_p++;
            else if (map[i][j] == 'E')
                count_e++;
            else if (map[i][j] == 'C')
                count_c++;
            else if (map[i][j] != '0' && map[i][j] != '1')
                return (0);
            j++;
        }
        i++;
    }

    return (check_element_counts(count_p, count_e, count_c));
}

int check_collectibles_reachable(char **map, char **map_copy, int max_i, int max_j)
{
    int i;
    int j;

    i = 0;
    while (i < max_i)
    {
        j = 0;
        while (j < max_j)
        {
            // If collectible wasn't reached by DFS (not marked as 'V')
            if (map[i][j] == 'C' && map_copy[i][j] == 'C')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int check_exit_reachable(char **map, char **map_copy, int max_i, int max_j)
{
    int i;
    int j;

    i = 0;
    while (i < max_i)
    {
        j = 0;
        while (j < max_j)
        {
            // If exit wasn't reached by DFS (not marked as 'V')
            if (map[i][j] == 'E' && map_copy[i][j] == 'E')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int check_path(char **map, int max_i, int max_j)
{
    char **map_copy1;
    char **map_copy2;
    int result;

    if (!check_boundaries(map, max_i, max_j))
        error_exit("Map must be rectangular and surrounded by walls");
    
    if (!validate_elements(map, max_i, max_j))
        error_exit("Map must contain exactly 1 player, 1 exit, and at least 1 collectible");

    // First check: Can player reach all collectibles?
    map_copy1 = map_dup(map, max_i, max_j);
    if (!map_copy1)
        error_exit("Memory allocation failed");

    if (!find_player_and_run_dfs_collectibles(map_copy1, max_i, max_j))
    {
        freer(map_copy1, max_i);
        error_exit("No player found in map");
    }

    result = check_collectibles_reachable(map, map_copy1, max_i, max_j);
    freer(map_copy1, max_i);
    
    if (!result)
        error_exit("Map has unreachable collectibles");

    // Second check: Can player reach exit?
    map_copy2 = map_dup(map, max_i, max_j);
    if (!map_copy2)
        error_exit("Memory allocation failed");

    if (!find_player_and_run_dfs_exit(map_copy2, max_i, max_j))
    {
        freer(map_copy2, max_i);
        error_exit("No player found in map");
    }

    result = check_exit_reachable(map, map_copy2, max_i, max_j);
    freer(map_copy2, max_i);
    
    if (!result)
        error_exit("Map has unreachable exit");
    
    return (1);
}

void map_validator(char **map, int max_i, int max_j)
{
    if (!check_path(map, max_i, max_j))
        error_exit("No valid path in map");
}