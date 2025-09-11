/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *game, int x, int y)
{
	void	*img;

	if (!game || !game->map || !game->mlx || !game->win)
		return ;
	mlx_put_image_to_window(game->mlx, game->win, game->floor.img,
		x * TILE_SIZE, y * TILE_SIZE);
	img = NULL;
	if (game->map[y][x] == '1')
		img = game->wall.img;
	else if (game->map[y][x] == 'C')
		img = game->collectible.img;
	else if (game->map[y][x] == 'E')
		img = game->exit.img;
	else if (game->map[y][x] == 'P')
		img = game->player.img;
	else
		return ;
	if (img)
		mlx_put_image_to_window(game->mlx, game->win, img,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->map)
		return ;
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

void	redraw_player_move(t_game *game, t_move move)
{
	if (!game || !game->map)
		return ;
	draw_tile(game, move.old_x, move.old_y);
	draw_tile(game, move.new_x, move.new_y);
}

void	handle_win_condition(t_game *game)
{
	write(1, "You won!\n", 9);
	handle_close(game);
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	write(1, "Moves: ", 7);
	put_nbr(game->moves);
	write(1, "\n", 1);
}
