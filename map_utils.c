#include "so_long.h"

void	dfs_collectibles(char **map, int i, int j, int max_i, int max_j)
{
	if (i < 0 || j < 0 || i >= max_i || j >= max_j)
		return ;
	if (map[i][j] == '1' || map[i][j] == 'V' || map[i][j] == 'E')
		return ;
	map[i][j] = 'V';
	dfs_collectibles(map, i + 1, j, max_i, max_j);
	dfs_collectibles(map, i - 1, j, max_i, max_j);
	dfs_collectibles(map, i, j + 1, max_i, max_j);
	dfs_collectibles(map, i, j - 1, max_i, max_j);
}

void	dfs_exit(char **map, int i, int j, int max_i, int max_j)
{
	if (i < 0 || j < 0 || i >= max_i || j >= max_j)
		return ;
	if (map[i][j] == '1' || map[i][j] == 'V')
		return ;
	map[i][j] = 'V';
	dfs_exit(map, i + 1, j, max_i, max_j);
	dfs_exit(map, i - 1, j, max_i, max_j);
	dfs_exit(map, i, j + 1, max_i, max_j);
	dfs_exit(map, i, j - 1, max_i, max_j);
}

char	*allocate_map_row(int max_j)
{
	char	*row;
	int		i;

	row = malloc(sizeof(char) * (max_j + 1));
	if (!row)
		return (NULL);
	i = 0;
	while (i <= max_j)
		row[i++] = '\0';
	return (row);
}

void	copy_map_row(char **copy, char **map, int i, int max_j)
{
	int	j;

	j = 0;
	while (j < max_j)
	{
		copy[i][j] = map[i][j];
		j++;
	}
	copy[i][j] = '\0';
}

void	free_partial_map(char **copy, int allocated_rows)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (i < allocated_rows)
	{
		if (copy[i])
			free(copy[i]);
		i++;
	}
	free(copy);
}
