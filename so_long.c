#include "so_long.h"

static void cleanup_and_exit(t_game *game, int exit_code)
{
    if (game && game->map)
        freer(game->map, game->map_height);
    exit(exit_code);
}

static void error_exit(char *message)
{
    write(2, "Error\n", 6);
    if (message)
    {
        write(2, message, ft_strlen_custom(message));
        write(2, "\n", 1);
    }
    exit(EXIT_ERROR);
}

static int check_file_extension(char *filename)
{
    int len;
    
    if (!filename)
        return (0);
    len = ft_strlen_custom(filename);
    if (len < 4)
        return (0);
    if (filename[len - 4] != '.' || filename[len - 3] != 'b' ||
        filename[len - 2] != 'e' || filename[len - 1] != 'r')
        return (0);
    return (1);
}

int check_file_access(char *filename)
{
    int fd;
    
    if (!filename)
        error_exit("No filename provided");
    
    if (!check_file_extension(filename))
        error_exit("Invalid file extension (must be .ber)");
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        error_exit("Cannot open file");
    close(fd);
    return (1);
}

int get_clean_length(char *line)
{
    int len;
    
    len = ft_strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' 
                      || line[len - 1] == ' ' || line[len - 1] == '\t'))
    {
        line[len - 1] = '\0';
        len--;
    }
    return (len);
}

static void validate_line_length_and_cleanup(char *tmp, int len, int expected_len, int fd)
{
    if (expected_len == -1)
        return;
    if (len != expected_len)
    {
        write(2, "Map Error: Inconsistent line length\n", 37);
        free(tmp);
        close(fd);
        exit(EXIT_ERROR);
    }
}

void map_dimensioner(char *filename, int *height, int *width)
{
    int     fd;
    int     len;
    int     expected_len;
    int     line_count;
    char    *tmp;

    line_count = 0;
    expected_len = -1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit(EXIT_ERROR);
    
    while (1)
    {
        tmp = get_next_line(fd);
        if (!tmp)
            break;
        len = get_clean_length(tmp);
        if (len == 0)
        {
            free(tmp);
            continue;
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

void freer(char **map, int i)
{
    int k = 0;
    if (!map)
        return;
    while (k < i)
    {
        if (map[k])
            free(map[k]);
        k++;
    }
    free(map);
}

static char **allocate_map(int max_i)
{
    char **map_fill;
    int i;

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

static int read_map_lines(int fd, char **map_fill, int max_i)
{
    int     i;
    char    *tmp;
    int     len;

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
            continue;
        }
        map_fill[i] = tmp;
        i++;
    }
    return (i);
}

char **read_map_with_error_handle(char *filename)
{
    int     fd;
    char    **map_fill;
    int     max_i;
    int     max_j;
    int     result;

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

int main(int argc, char **argv)
{
    t_game  game;
    int     max_i;
    int     max_j;

    // Initialize entire game structure to zero
    ft_memset(&game, 0, sizeof(t_game));

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
    {
        cleanup_and_exit(&game, EXIT_ERROR);
    }

    init_game(&game);
    load_images(&game);
    find_player_position(&game);
    count_collectibles(&game);
    draw_map(&game);

    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
    mlx_hook(game.win, 17, 1L<<17, handle_close, &game);
    mlx_loop(game.mlx);

    return (EXIT_SUCCESS);
}