/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_or_exit_ro(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(EXIT_ERROR);
	return (fd);
}

int	read_and_process_line(int fd, int *expected_len, int *line_count)
{
	char	*tmp;
	int		len;

	tmp = get_next_line(fd);
	if (!tmp)
		return (-1);
	len = get_clean_length(tmp);
	if (len == 0)
	{
		free(tmp);
		return (0);
	}
	if (*expected_len == -1)
		*expected_len = len;
	else
		validate_line_length_and_cleanup(tmp, len, *expected_len, fd);
	(*line_count)++;
	free(tmp);
	return (1);
}

char	**allocate_map_or_exit(int fd, int max_i)
{
	char	**map_fill;

	map_fill = allocate_map(max_i);
	if (!map_fill)
	{
		close(fd);
		exit(EXIT_MALLOC_ERROR);
	}
	return (map_fill);
}

void	handle_read_result(int result, char **map_fill, int max_i, int fd)
{
	if (result == -1)
	{
		freer(map_fill, max_i);
		close(fd);
		exit(EXIT_MAP_ERROR);
	}
}
