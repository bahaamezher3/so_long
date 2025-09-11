/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_dimensioner(char *filename, int *height, int *width)
{
	int		fd;
	int		expected_len;
	int		line_count;

	init_dimension_counters(height, width, &line_count, &expected_len);
	fd = open_or_exit_ro(filename);
	scan_dimensions(fd, &expected_len, &line_count);
	close(fd);
	validate_dimensions_or_exit(line_count, expected_len);
	*height = line_count;
	*width = expected_len;
}

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

char	**read_map_with_error_handle(char *filename)
{
	int		fd;
	char	**map_fill;
	int		max_i;
	int		max_j;
	int		result;

	if (!filename)
		exit(EXIT_ERROR);
	map_dimensioner(filename, &max_i, &max_j);
	fd = open_or_exit_ro(filename);
	map_fill = allocate_map_or_exit(fd, max_i);
	result = read_map_lines(fd, map_fill, max_i);
	handle_read_result(result, map_fill, max_i, fd);
	map_fill[result] = NULL;
	close(fd);
	return (map_fill);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		max_i;
	int		max_j;

	if (argc != 2)
		error_exit("Usage: ./so_long map.ber");
	if (!check_file_access(argv[1]))
		return (EXIT_ERROR);
	map_dimensioner(argv[1], &max_i, &max_j);
	game.map = read_map_with_error_handle(argv[1]);
	if (!game.map)
		error_exit("Failed to load map");
	game.map_height = max_i;
	game.map_width = max_j;
	if (!check_path(game.map, max_i, max_j))
		cleanup_and_exit(&game, EXIT_ERROR);
	init_game(&game);
	load_images(&game);
	find_player_position(&game);
	count_collectibles(&game);
	draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 1L << 17, handle_close, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
