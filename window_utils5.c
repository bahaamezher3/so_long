/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:12:30 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 15:11:23 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_image_load_error(t_game *game, char *path, char *prefix)
{
	write(2, prefix, ft_strlen_custom(prefix));
	write(2, path, ft_strlen_custom(path));
	write(2, "\n", 1);
	cleanup_images_on_error(game);
	exit(EXIT_ERROR);
}

void	validate_and_get_image_data(t_game *game, t_img *img, char *path)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		handle_image_load_error(game, path,
			"Error: Failed to get image data: ");
}
