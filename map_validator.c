/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_boundaries(char **map, int max_i, int max_j)
{
	int	i;
	int	j;

	if (!map || max_i <= 0 || max_j <= 0)
		return (0);
	if (max_i < 3 || max_j < 3)
		return (0);
	j = 0;
	while (j < max_j)
	{
		if (map[0][j] != '1' || map[max_i - 1][j] != '1')
			return (0);
		j++;
	}
	i = 0;
	while (i < max_i)
	{
		if (map[i][0] != '1' || map[i][max_j - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_element_counts(int count_p, int count_e, int count_c)
{
	if (count_p != 1)
		return (0);
	if (count_e != 1)
		return (0);
	if (count_c < 1)
		return (0);
	return (1);
}

int	validate_elements(char **map, int max_i, int max_j)
{
	int	i;
	int	j;
	int	count_e;
	int	count_c;
	int	count_p;

	if (!map || max_i <= 0 || max_j <= 0)
		return (0);
	count_c = 0;
	count_e = 0;
	count_p = 0;
	i = 0;
	while (i < max_i)
	{
		j = 0;
		while (j < max_j)
		{
			if (!update_counts_and_validate_cell(map[i][j],
				&count_p, &count_e, &count_c))
				return (0);
			j++;
		}
		i++;
	}
	return (check_element_counts(count_p, count_e, count_c));
}

int	check_collectibles_reachable(char **map, char **map_copy,
		int max_i, int max_j)
{
	int	i;
	int	j;

	if (!map || !map_copy || max_i <= 0 || max_j <= 0)
		return (0);
	i = 0;
	while (i < max_i)
	{
		j = 0;
		while (j < max_j)
		{
			if (map[i][j] == 'C' && map_copy[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_exit_reachable(char **map, char **map_copy, int max_i, int max_j)
{
	int	i;
	int	j;

	if (!map || !map_copy || max_i <= 0 || max_j <= 0)
		return (0);
	i = 0;
	while (i < max_i)
	{
		j = 0;
		while (j < max_j)
		{
			if (map[i][j] == 'E' && map_copy[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
