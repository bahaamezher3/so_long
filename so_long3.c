/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_dimension_counters(int *height, int *width,
		int *line_count, int *expected_len)
{
	if (!height || !width || !line_count || !expected_len)
		exit(EXIT_ERROR);
	*height = 0;
	*width = 0;
	*line_count = 0;
	*expected_len = -1;
}

void	validate_dimensions_or_exit(int line_count, int expected_len)
{
	if (line_count == 0 || expected_len <= 0)
	{
		write(2, "Map Error: Empty or invalid map\n", 33);
		exit(EXIT_ERROR);
	}
}

void	scan_dimensions(int fd, int *expected_len, int *line_count)
{
	char	*tmp;
	int		len;

	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		len = get_clean_length(tmp);
		if (len == 0)
		{
			free(tmp);
			continue ;
		}
		if (*expected_len == -1)
			*expected_len = len;
		else
			validate_line_length_and_cleanup(tmp, len, *expected_len, fd);
		(*line_count)++;
		free(tmp);
	}
}

int		open_or_exit_ro(char *filename);
int		read_and_process_line(int fd, int *expected_len, int *line_count);
char	**allocate_map_or_exit(int fd, int max_i);
void	handle_read_result(int result, char **map_fill, int max_i, int fd);
