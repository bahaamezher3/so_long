/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:11:55 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 15:11:58 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	int		first_line;
	int		map_ended;

	first_line = 1;
	map_ended = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		len = get_clean_length(tmp);
		check_first_line(first_line, len, tmp, fd);
		first_line = 0;
		if (len == 0)
			map_ended = 1;
		check_map_continuity(map_ended, len, tmp, fd);
		check_line_length(expected_len, len, tmp, fd);
		if (len > 0)
			(*line_count)++;
		free(tmp);
	}
}

static int	handle_empty_line(char *line, t_mapread *mr)
{
	static int	trailing_count = 0;

	trailing_count++;
	if (trailing_count > 1)
	{
		write(2, "Map Error: Too many trailing empty lines\n", 42);
		free(line);
		cleanup_remaining_lines(mr->fd);
		return (-1);
	}
	mr->map_ended = 1;
	free(line);
	return (0);
}

static int	handle_content_line(char *line, t_mapread *mr)
{
	if (mr->map_ended)
	{
		write(2, "Map Error: Empty lines in middle of map\n", 41);
		free(line);
		cleanup_remaining_lines(mr->fd);
		return (-1);
	}
	if (mr->i >= mr->max_i)
	{
		free(line);
		cleanup_remaining_lines(mr->fd);
		return (-1);
	}
	mr->map_fill[mr->i++] = line;
	return (0);
}

int	read_map_loop(t_mapread *mr)
{
	char	*tmp;
	int		ret;

	while (1)
	{
		tmp = get_next_line(mr->fd);
		if (!tmp)
			break ;
		if (get_clean_length(tmp) == 0)
		{
			ret = handle_empty_line(tmp, mr);
			if (ret < 0)
				return (-1);
			continue ;
		}
		ret = handle_content_line(tmp, mr);
		if (ret < 0)
			return (-1);
	}
	return (mr->i);
}

int		open_or_exit_ro(char *filename);
int		read_and_process_line(int fd, int *expected_len, int *line_count);
char	**allocate_map_or_exit(int fd, int max_i);
void	handle_read_result(int result, char **map_fill, int max_i, int fd);
