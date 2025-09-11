/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:00:00 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/11 00:00:00 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_player(t_game *game, int new_x, int new_y)
{
	int		old_x;
	int		old_y;
	t_move	move;

	if (!game || !game->map)
		return (0);
	old_x = game->player_x;
	old_y = game->player_y;
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	else if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
		handle_win_condition(game);
	else if (game->map[new_y][new_x] == 'E')
		return (0);
	update_player_position(game, new_x, new_y);
	move.old_x = old_x;
	move.old_y = old_y;
	move.new_x = new_x;
	move.new_y = new_y;
	redraw_player_move(game, move);
	return (1);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	if (!game)
		return (0);
	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == ESC)
		handle_close(game);
	else if (keycode == W || keycode == 65362)
		new_y--;
	else if (keycode == S || keycode == 65364)
		new_y++;
	else if (keycode == A || keycode == 65361)
		new_x--;
	else if (keycode == D || keycode == 65363)
		new_x++;
	else
		return (0);
	if (new_x >= 0 && new_x < game->map_width
		&& new_y >= 0 && new_y < game->map_height
		&& game->map[new_y][new_x] != '1')
		move_player(game, new_x, new_y);
	return (0);
}

int	handle_close(t_game *game)
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
