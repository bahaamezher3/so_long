#include "so_long.h"

void	map_dimensioner(char *filename, int *height, int *width)
{
	int		fd;
	int		len;
	int		expected_len;
	int		line_count;
	char	*tmp;

	if (!filename || !height || !width)
		exit(EXIT_ERROR);
	*height = 0;
	*width = 0;
	line_count = 0;
	expected_len = -1;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(EXIT_ERROR);
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
		if (expected_len == -1)
			expected_len = len;
		else
			validate_line_length_and_cleanup(tmp, len, expected_len, fd);
		line_count++;
		free(tmp);
	}
	close(fd);
	if (line_count == 0 || expected_len <= 0)
	{
		write(2, "Map Error: Empty or invalid map\n", 33);
		exit(EXIT_ERROR);
	}
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
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(EXIT_ERROR);
	map_fill = allocate_map(max_i);
	if (!map_fill)
	{
		close(fd);
		exit(EXIT_MALLOC_ERROR);
	}
	result = read_map_lines(fd, map_fill, max_i);
	if (result == -1)
	{
		freer(map_fill, max_i);
		close(fd);
		exit(EXIT_MAP_ERROR);
	}
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
