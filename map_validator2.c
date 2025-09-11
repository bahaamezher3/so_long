/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	validate_map_basic_checks(char **map, int max_i, int max_j)
{
	if (!check_boundaries(map, max_i, max_j))
		error_exit("Map must be rectangular and surrounded by walls");
	if (!validate_elements(map, max_i, max_j))
		error_exit("Map must contain exactly 1 player, 1 exit, and "
			"at least 1 collectible");
	return (1);
}

int	validate_collectibles_path(char **map, int max_i, int max_j)
{
	char	**map_copy;
	int		result;

	map_copy = map_dup(map, max_i, max_j);
	if (!map_copy)
		error_exit("Memory allocation failed");
	if (!find_player_and_run_dfs_collectibles(map_copy, max_i, max_j))
	{
		freer(map_copy, max_i);
		error_exit("No player found in map");
	}
	result = check_collectibles_reachable(map, map_copy, max_i, max_j);
	freer(map_copy, max_i);
	if (!result)
		error_exit("Map has unreachable collectibles");
	return (1);
}

int	validate_exit_path(char **map, int max_i, int max_j)
{
	char	**map_copy;
	int		result;

	map_copy = map_dup(map, max_i, max_j);
	if (!map_copy)
		error_exit("Memory allocation failed");
	if (!find_player_and_run_dfs_exit(map_copy, max_i, max_j))
	{
		freer(map_copy, max_i);
		error_exit("No player found in map");
	}
	result = check_exit_reachable(map, map_copy, max_i, max_j);
	freer(map_copy, max_i);
	if (!result)
		error_exit("Map has unreachable exit");
	return (1);
}

int	check_path(char **map, int max_i, int max_j)
{
	if (!map || max_i <= 0 || max_j <= 0)
		error_exit("Invalid map parameters");
	validate_map_basic_checks(map, max_i, max_j);
	validate_collectibles_path(map, max_i, max_j);
	validate_exit_path(map, max_i, max_j);
	return (1);
}

void	map_validator(char **map, int max_i, int max_j)
{
	if (!map || max_i <= 0 || max_j <= 0)
		error_exit_with_cleanup("Invalid map parameters", map, max_i);
	if (!check_path(map, max_i, max_j))
		error_exit_with_cleanup("No valid path in map", map, max_i);
}
