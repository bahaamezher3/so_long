/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map_pointers(char **copy, int max_i)
{
	int	i;

	i = 0;
	while (i <= max_i)
	{
		copy[i] = NULL;
		i++;
	}
}

char	**map_dup(char **map, int max_i, int max_j)
{
	int		i;
	char	**copy;

	if (!map || max_i <= 0 || max_j <= 0)
		return (NULL);
	copy = malloc(sizeof(char *) * (max_i + 1));
	if (!copy)
		return (NULL);
	init_map_pointers(copy, max_i);
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

int	find_player_and_run_dfs_collectibles(char **map_copy,
		int max_i, int max_j)
{
	int		i;
	int		j;
	int		dims[2];

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
				dims[0] = max_i;
				dims[1] = max_j;
				dfs_collectibles(map_copy, i, j, dims);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	find_player_and_run_dfs_exit(char **map_copy, int max_i, int max_j)
{
	int		i;
	int		j;
	int		dims[2];

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
				dims[0] = max_i;
				dims[1] = max_j;
				dfs_exit(map_copy, i, j, dims);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
