/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:11:46 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 15:12:11 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_dimension_counters(int *h, int *w,
			int *line_count, int *expected_len)
{
	if (!h || !w || !line_count || !expected_len)
		exit(EXIT_ERROR);
	*h = 0;
	*w = 0;
	*line_count = 0;
	*expected_len = -1;
}

void	cleanup_fd_exit(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	exit(EXIT_ERROR);
}

void	check_first_line(int first_line, int len, char *tmp, int fd)
{
	if (first_line && len == 0)
	{
		write(2, "Map Error: First line cannot be empty\n", 39);
		free(tmp);
		cleanup_fd_exit(fd);
	}
}

void	check_map_continuity(int map_ended, int len, char *tmp, int fd)
{
	if (map_ended && len > 0)
	{
		write(2, "Map Error: Empty lines in middle of map\n", 41);
		free(tmp);
		cleanup_fd_exit(fd);
	}
}

void	check_line_length(int *expected_len, int len, char *tmp, int fd)
{
	if (*expected_len == -1)
		*expected_len = len;
	else if (len != *expected_len)
	{
		write(2, "Map Error: Inconsistent line length\n", 37);
		free(tmp);
		cleanup_fd_exit(fd);
	}
}
