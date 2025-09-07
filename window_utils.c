#include "so_long.h"

void init_game(t_game *game)
{
    if (!game)
        return;

    // Initialize all game structure members to safe values
    game->moves = 0;
    game->collectibles = 0;
    game->player_x = 0;
    game->player_y = 0;
    game->mlx = NULL;
    game->win = NULL;

    // Initialize all image structures with explicit initialization
    game->player = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
    game->wall = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
    game->collectible = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
    game->exit = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
    game->floor = (t_img){NULL, NULL, 0, 0, 0, 0, 0};
    
    // Initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        write(2, "Error: Failed to initialize MLX\n", 33);
        if (game->map)
            freer(game->map, game->map_height);
        exit(EXIT_ERROR);
    }
    
    // Create window
    game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE, 
                              game->map_height * TILE_SIZE, "so_long");
    if (!game->win)
    {
        write(2, "Error: Failed to create window\n", 31);
        if (game->mlx)
        {
            mlx_destroy_display(game->mlx);
            free(game->mlx);
        }
        if (game->map)
            freer(game->map, game->map_height);
        exit(EXIT_ERROR);
    }
}

static void cleanup_images_on_error(t_game *game)
{
    if (!game)
        return;
        
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
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    if (game->map)
        freer(game->map, game->map_height);
}

static void load_single_image(t_game *game, t_img *img, char *path)
{
    int width;
    int height;

    if (!game || !img || !path)
        return;

    // Initialize image structure
    img->img = NULL;
    img->addr = NULL;
    img->bits_per_pixel = 0;
    img->line_length = 0;
    img->endian = 0;
    img->width = 0;
    img->height = 0;

    // Initialize local variables
    width = 0;
    height = 0;
    
    img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);

    if (!img->img)
    {
        write(2, "Error: Failed to load image: ", 29);
        write(2, path, ft_strlen_custom(path));
        write(2, "\n", 1);
        cleanup_images_on_error(game);
        exit(EXIT_ERROR);
    }
    
    img->width = width;
    img->height = height;
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, 
                                 &img->line_length, &img->endian);
    
    if (!img->addr)
    {
        write(2, "Error: Failed to get image data: ", 32);
        write(2, path, ft_strlen_custom(path));
        write(2, "\n", 1);
        cleanup_images_on_error(game);
        exit(EXIT_ERROR);
    }
}

void load_images(t_game *game)
{
    if (!game)
        return;
        
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

    if (!game || !game->map)
        return;

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

    if (!game || !game->map)
        return;

    // Initialize collectibles counter
    game->collectibles = 0;
    
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
    
    if (!game || !game->map || !game->mlx || !game->win)
        return;
        
    // Initialize img pointer
    img = NULL;
    
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
    
    if (img)
        mlx_put_image_to_window(game->mlx, game->win, img, 
                               x * TILE_SIZE, y * TILE_SIZE);
}

void draw_map(t_game *game)
{
    int i;
    int j;

    if (!game || !game->map)
        return;

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

// New function: only redraw specific tiles that changed
static void redraw_player_move(t_game *game, int old_x, int old_y, int new_x, int new_y)
{
    if (!game || !game->map)
        return;

    // Redraw the old position (now floor or collectible was removed)
    draw_tile(game, old_x, old_y);
    
    // Redraw the new position (now has player)
    draw_tile(game, new_x, new_y);
}

static int move_player(t_game *game, int new_x, int new_y)
{
    int old_x;
    int old_y;

    if (!game || !game->map)
        return (0);

    // Store old position
    old_x = game->player_x;
    old_y = game->player_y;

    if (game->map[new_y][new_x] == 'C')
        game->collectibles--;
    else if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
    {
        write(1, "You won!\n", 9);
        handle_close(game);
    }
    else if (game->map[new_y][new_x] == 'E')
        return (0);

    // Update map
    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;
    game->moves++;
    
    write(1, "Moves: ", 7);
    put_nbr(game->moves);
    write(1, "\n", 1);
    
    // Instead of redrawing entire map, only redraw changed tiles
    redraw_player_move(game, old_x, old_y, new_x, new_y);
    
    return (1);
}

int handle_keypress(int keycode, t_game *game)
{
    int new_x;
    int new_y;

    if (!game)
        return (0);

    // Initialize new position with current position
    new_x = game->player_x;
    new_y = game->player_y;

    if (keycode == ESC)
        handle_close(game);
    else if (keycode == W || keycode == 65362) // W or UP arrow
        new_y--;
    else if (keycode == S || keycode == 65364) // S or DOWN arrow
        new_y++;
    else if (keycode == A || keycode == 65361)
        new_x--;
    else if (keycode == D || keycode == 65363)
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
    if (!game)
        exit(EXIT_SUCCESS);
        
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