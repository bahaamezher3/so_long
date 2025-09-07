#include "so_long.h"

// DFS to find all collectibles (treating exit as wall)
void dfs_collectibles(char **map, int i, int j, int max_i, int max_j)
{
    if (i < 0 || j < 0 || i >= max_i || j >= max_j)
        return;
    if (map[i][j] == '1' || map[i][j] == 'V' || map[i][j] == 'E')
        return;
    map[i][j] = 'V';
    dfs_collectibles(map, i + 1, j, max_i, max_j);
    dfs_collectibles(map, i - 1, j, max_i, max_j);
    dfs_collectibles(map, i, j + 1, max_i, max_j);
    dfs_collectibles(map, i, j - 1, max_i, max_j);
}

// DFS to find exit (treating collectibles as passable)
void dfs_exit(char **map, int i, int j, int max_i, int max_j)
{
    if (i < 0 || j < 0 || i >= max_i || j >= max_j)
        return;
    if (map[i][j] == '1' || map[i][j] == 'V')
        return;
    map[i][j] = 'V';
    dfs_exit(map, i + 1, j, max_i, max_j);
    dfs_exit(map, i - 1, j, max_i, max_j);
    dfs_exit(map, i, j + 1, max_i, max_j);
    dfs_exit(map, i, j - 1, max_i, max_j);
}

static char *allocate_map_row(int max_j)
{
    char *row;

    row = malloc(sizeof(char) * (max_j + 1));
    if (!row)
        return (NULL);
    // Initialize the row to prevent uninitialized values
    ft_memset(row, '\0', max_j + 1);
    return (row);
}

static void copy_map_row(char **copy, char **map, int i, int max_j)
{
    int j;

    j = 0;
    while (j < max_j)
    {
        copy[i][j] = map[i][j];
        j++;
    }
    copy[i][j] = '\0';
}

// Free partial allocation on failure
static void free_partial_map(char **copy, int allocated_rows)
{
    int i;
    
    if (!copy)
        return;
    i = 0;
    while (i < allocated_rows)
    {
        if (copy[i])
            free(copy[i]);
        i++;
    }
    free(copy);
}

char **map_dup(char **map, int max_i, int max_j)
{
    int     i;
    char    **copy;

    if (!map || max_i <= 0 || max_j <= 0)
        return (NULL);

    copy = malloc(sizeof(char *) * (max_i + 1));
    if (!copy)
        return (NULL);
        
    // Initialize all pointers to NULL for safe cleanup
    i = 0;
    while (i <= max_i)
    {
        copy[i] = NULL;
        i++;
    }
    
    i = 0;
    while (i < max_i)
    {
        copy[i] = allocate_map_row(max_j);
        if (!copy[i])
        {
            free_partial_map(copy, i);
            return (NULL);
        }
        copy_map_row(copy, map, i, max_j);
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

int find_player_and_run_dfs_collectibles(char **map_copy, int max_i, int max_j)
{
    int i;
    int j;

    if (!map_copy || max_i <= 0 || max_j <= 0)
        return (0);

    i = 0;
    while (i < max_i)
    {
        j = 0;
        while (j < max_j)
        {
            if (map_copy[i][j] == 'P')
            {
                dfs_collectibles(map_copy, i, j, max_i, max_j);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int find_player_and_run_dfs_exit(char **map_copy, int max_i, int max_j)
{
    int i;
    int j;

    if (!map_copy || max_i <= 0 || max_j <= 0)
        return (0);

    i = 0;
    while (i < max_i)
    {
        j = 0;
        while (j < max_j)
        {
            if (map_copy[i][j] == 'P')
            {
                dfs_exit(map_copy, i, j, max_i, max_j);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}