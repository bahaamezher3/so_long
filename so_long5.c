/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:06:20 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 15:12:03 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int			read_map_loop(t_mapread *mr);

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
		map_fill[i++] = NULL;
	return (map_fill);
}

void	cleanup_remaining_lines(int fd)
{
	char	*tmp;

	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		free(tmp);
	}
}

int	read_map_lines(int fd, char **map_fill, int max_i)
{
	t_mapread	mr;

	if (!map_fill || max_i <= 0)
		return (-1);
	mr.map_fill = map_fill;
	mr.i = 0;
	mr.max_i = max_i;
	mr.map_ended = 0;
	mr.fd = fd;
	return (read_map_loop(&mr));
}
