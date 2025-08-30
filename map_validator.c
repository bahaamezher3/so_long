#include "so_long.h"

int check_boundaries(char **map, int max_i, int max_j)
{
    int i;
    int j;

    if (max_i < 3 || max_j < 3)
    {
        write(2, "Map Error: Map too small!\n", 27);
        return (0);
    }

    j = 0;
    while (j < max_j)
    {
        if (map[0][j] != '1' || map[max_i - 1][j] != '1')
        {
            write(2, "Map Error: Map must be surrounded by walls!\n", 45);
            return (0);
        }
        j++;
    }

    i = 0;
    while (i < max_i)
    {
        if (map[i][0] != '1' || map[i][max_j - 1] != '1')
        {
            write(2, "Map Error: Map must be surrounded by walls!\n", 45);
            return (0);
        }
        i++;
    }

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
            {
                write(2, "Map Error: Invalid character in map!\n", 38);
                return (0);
            }
            j++;
        }
        i++;
    }

    if (count_p != 1)
    {
        write(2, "Map Error: Must have exactly one player!\n", 42);
        return (0);
    }
    if (count_e != 1)
    {
        write(2, "Map Error: Must have exactly one exit!\n", 40);
        return (0);
    }
    if (count_c < 1)
    {
        write(2, "Map Error: Must have at least one collectible!\n", 48);
        return (0);
    }

    return (1);
}

int check_reachability(char **map, char **map_copy, int max_i, int max_j)
{
    int i;
    int j;

    i = 0;
    while (i < max_i)
    {
        j = 0;
        while (j < max_j)
        {
            if (map[i][j] == 'E' && map_copy[i][j] == 'E')
            {
                write(2, "Map Error: Exit not reachable!\n", 32);
                return (0);
            }
            if (map[i][j] == 'C' && map_copy[i][j] == 'C')
            {
                write(2, "Map Error: Collectible not reachable!\n", 38);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}


int check_path(char **map, int max_i, int max_j)
{
    char **map_copy;
    int result;

    if (!check_boundaries(map, max_i, max_j))
        return (0);
    
    if (!validate_elements(map, max_i, max_j))
        return (0);

    map_copy = map_dup(map, max_i, max_j);
    if (!map_copy)
        return (0);

    if (!find_player_and_run_dfs(map_copy, max_i, max_j))
    {
        write(2, "Map Error: No player found!\n", 29);
        freer(map_copy, max_i);
        return (0);
    }

    result = check_reachability(map, map_copy, max_i, max_j);
    freer(map_copy, max_i);
    return (result);
}

void map_validator(char **map, int max_i, int max_j)
{
    if (!check_path(map, max_i, max_j))
    {
        write(2, "No Possible Path\n", 17);
        exit(3);
    }
}