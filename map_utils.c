#include "so_long.h"

void dfs(char **map, int i, int j, int max_i, int max_j)
{
    if (i < 0 || j < 0 || i >= max_i || j >= max_j)
        return;
    if (map[i][j] == '1' || map[i][j] == 'V')
        return;
    map[i][j] = 'V';
    dfs(map, i + 1, j, max_i, max_j);
    dfs(map, i - 1, j, max_i, max_j);
    dfs(map, i, j + 1, max_i, max_j);
    dfs(map, i, j - 1, max_i, max_j);
}

char **map_dup(char **map, int max_i, int max_j)
{
    int     i, j;
    char    **copy;

    copy = malloc(sizeof(char *) * (max_i + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < max_i)
    {
        copy[i] = malloc(sizeof(char) * (max_j + 1));
        if (!copy[i])
        {
            freer(copy, i);
            return (NULL);
        }
        j = 0;
        while (j < max_j)
        {
            copy[i][j] = map[i][j];
            j++;
        }
        copy[i][j] = '\0';
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

int find_player_and_run_dfs(char **map_copy, int max_i, int max_j)
{
    int i, j;
    
    for (i = 0; i < max_i; i++)
    {
        for (j = 0; j < max_j; j++)
        {
            if (map_copy[i][j] == 'P')
            {
                dfs(map_copy, i, j, max_i, max_j);
                return (1);
            }
        }
    }
    return (0);
}