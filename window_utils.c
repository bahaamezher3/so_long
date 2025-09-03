#include "so_long.h"

void init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        write(2, "Error: Failed to initialize MLX\n", 33);
        exit(EXIT_ERROR);
    }
    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, 
                              game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
    {
        write(2, "Error: Failed to create window\n", 31);
        exit(EXIT_ERROR);
    }
    game->moves = 0;
    game->collectibles = 0;
}

static void load_single_image(t_game *game, t_img *img, char *path)
{
    img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
    if (!img->img)
    {
        write(2, "Error: Failed to load image: ", 29);
        write(2, path, ft_strlen_custom(path));
        write(2, "\n", 1);
        exit(EXIT_ERROR);
    }
}

void load_images(t_game *game)
{
    load_single_image(game, &game->player, "assets/wizard.xpm");
    load_single_image(game, &game->wall, "assets/tree_wall.xpm");
    load_single_image(game, &game->collectible, "assets/crystal.xpm");
    load_single_image(game, &game->exit, "assets/portal.xpm");
    load_single_image(game, &game->floor, "assets/forest_floor.xpm");
}

void find_player_position(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == 'P')
            {
                game->player_x = j;
                game->player_y = i;
                return;
            }
            j++;
        }
        i++;
    }
}

void count_collectibles(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == 'C')
                game->collectibles++;
            j++;
        }
        i++;
    }
}

void draw_tile(t_game *game, int x, int y)
{
    void *img;
    
    // First draw floor, then the object on top
    mlx_put_image_to_window(game->mlx, game->win, game->floor.img, 
                           x * TILE_SIZE, y * TILE_SIZE);
    
    if (game->map[y][x] == '1')
        img = game->wall.img;
    else if (game->map[y][x] == 'C')
        img = game->collectible.img;
    else if (game->map[y][x] == 'E')
        img = game->exit.img;
    else if (game->map[y][x] == 'P')
        img = game->player.img;
    else
        return; // Only floor, already drawn
    
    mlx_put_image_to_window(game->mlx, game->win, img, 
                           x * TILE_SIZE, y * TILE_SIZE);
}

void draw_map(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            draw_tile(game, j, i);
            j++;
        }
        i++;
    }
}

static int move_player(t_game *game, int new_x, int new_y)
{
    if (game->map[new_y][new_x] == 'C')
        game->collectibles--;
    else if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
    {
        write(1, "You won!\n", 9);
        handle_close(game);
    }
    else if (game->map[new_y][new_x] == 'E')
        return (0);

    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
    write(1, "Moves: ", 7);
    put_nbr(game->moves);
    write(1, "\n", 1);
    draw_map(game);
    return (1);
}

int handle_keypress(int keycode, t_game *game)
{
    int new_x;
    int new_y;

    new_x = game->player_x;
    new_y = game->player_y;

    if (keycode == ESC)
        handle_close(game);
    else if (keycode == W || keycode == 65362) // W or UP arrow
        new_y--;
    else if (keycode == S || keycode == 65364) // S or DOWN arrow
        new_y++;
    else if (keycode == A || keycode == 65361) // A or LEFT arrow
        new_x--;
    else if (keycode == D || keycode == 65363) // D or RIGHT arrow
        new_x++;
    else
        return (0);

    if (new_x >= 0 && new_x < game->map_width && 
        new_y >= 0 && new_y < game->map_height &&
        game->map[new_y][new_x] != '1')
        move_player(game, new_x, new_y);
    return (0);
}

int handle_close(t_game *game)
{
    // Clean up resources
    if (game->player.img)
        mlx_destroy_image(game->mlx, game->player.img);
    if (game->wall.img)
        mlx_destroy_image(game->mlx, game->wall.img);
    if (game->collectible.img)
        mlx_destroy_image(game->mlx, game->collectible.img);
    if (game->exit.img)
        mlx_destroy_image(game->mlx, game->exit.img);
    if (game->floor.img)
        mlx_destroy_image(game->mlx, game->floor.img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->map)
        freer(game->map, game->map_height);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    exit(EXIT_SUCCESS);
    return (0);
}