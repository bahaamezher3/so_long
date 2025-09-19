/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:12:10 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 14:12:10 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_img_struct(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	init_game_values(t_game *game)
{
	game->moves = 0;
	game->collectibles = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->mlx = NULL;
	game->win = NULL;
	init_img_struct(&game->player);
	init_img_struct(&game->wall);
	init_img_struct(&game->collectible);
	init_img_struct(&game->exit);
	init_img_struct(&game->floor);
}

void	cleanup_on_init_error(t_game *game)
{
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		freer(game->map, game->map_height);
	exit(EXIT_ERROR);
}

void	init_game(t_game *game)
{
	if (!game)
		return ;
	init_game_values(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		write(2, "Error: Failed to initialize MLX\n", 33);
		cleanup_on_init_error(game);
	}
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		write(2, "Error: Failed to create window\n", 31);
		cleanup_on_init_error(game);
	}
}
