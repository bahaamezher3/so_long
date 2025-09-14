/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cleanup_images_on_error(t_game *game)
{
	if (!game)
		return ;
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

void	load_single_image(t_game *game, t_img *img, char *path)
{
	int		width;
	int		height;

	if (!game || !img || !path)
		return ;
	init_img_struct(img);
	img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->img)
		handle_image_load_error(game, path, "Error: Failed to load image: ");
	img->width = width;
	img->height = height;
	validate_and_get_image_data(game, img, path);
}

void	load_images(t_game *game)
{
	if (!game)
		return ;
	load_single_image(game, &game->player, "assets/xpm_assets/player.xpm");
	load_single_image(game, &game->wall, "assets/xpm_assets/wall.xpm");
	load_single_image(game, &game->collectible, "assets/xpm_assets/collectible.xpm");
	load_single_image(game, &game->exit, "assets/xpm_assets/exit.xpm");
	load_single_image(game, &game->floor, "assets/xpm_assets/floor.xpm");
}

void	find_player_position(t_game *game)
{
	int		i;
	int		j;

	if (!game || !game->map)
		return ;
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
				return ;
			}
			j++;
		}
		i++;
	}
}

void	count_collectibles(t_game *game)
{
	int		i;
	int		j;

	if (!game || !game->map)
		return ;
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
