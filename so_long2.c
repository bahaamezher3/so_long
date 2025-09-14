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

void	init_and_validate_game(t_game *game, char **argv)
{
	int		max_i;
	int		max_j;

	map_dimensioner(argv[1], &max_i, &max_j);
	game->map = read_map_with_error_handle(argv[1]);
	if (!game->map)
		error_exit("Failed to load map");
	game->map_height = max_i;
	game->map_width = max_j;
	if (!check_path(game->map, max_i, max_j))
		cleanup_and_exit(game, EXIT_ERROR);
}

void	setup_game_graphics(t_game *game)
{
	init_game(game);
	load_images(game);
	find_player_position(game);
	count_collectibles(game);
	draw_map(game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error_exit("Usage: ./so_long map.ber");
	if (!check_file_access(argv[1]))
		return (EXIT_ERROR);
	init_and_validate_game(&game, argv);
	setup_game_graphics(&game);
	mlx_expose_hook(game.win, handle_expose, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 1L << 17, handle_close, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
