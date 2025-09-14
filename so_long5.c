/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**allocate_map(int max_i)
{
	char	**map_fill;
	int		i;

	if (max_i <= 0)
	{
		write(2, "Error: Invalid map size\n", 24);
		return (NULL);
	}
	map_fill = malloc(sizeof(char *) * (max_i + 1));
	if (!map_fill)
	{
		write(2, "Error: Memory allocation failed\n", 32);
		return (NULL);
	}
	i = 0;
	while (i <= max_i)
	{
		map_fill[i] = NULL;
		i++;
	}
	return (map_fill);
}

int	read_map_lines(int fd, char **map_fill, int max_i)
{
	int		i;
	char	*tmp;
	int		len;

	if (!map_fill || max_i <= 0)
		return (-1);
	i = 0;
	while (i < max_i)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return (-1);
		len = get_clean_length(tmp);
		if (len == 0)
		{
			free(tmp);
			continue ;
		}
		map_fill[i] = tmp;
		i++;
	}
	return (i);
}
