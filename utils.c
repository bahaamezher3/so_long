/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:11:48 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 15:11:48 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_nbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		if (n == -2147483648)
		{
			write(1, "2147483648", 10);
			return ;
		}
		n = -n;
	}
	if (n >= 10)
		put_nbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

int	ft_strlen_custom(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	error_exit(char *message)
{
	write(2, "Error\n", 6);
	if (message)
	{
		write(2, message, ft_strlen_custom(message));
		write(2, "\n", 1);
	}
	exit(EXIT_ERROR);
}

void	error_exit_with_cleanup(char *message, char **map, int max_i)
{
	write(2, "Error\n", 6);
	if (message)
	{
		write(2, message, ft_strlen_custom(message));
		write(2, "\n", 1);
	}
	if (map)
		freer(map, max_i);
	exit(EXIT_ERROR);
}

void	cleanup_and_exit(t_game *game, int exit_code)
{
	if (game && game->map)
		freer(game->map, game->map_height);
	exit(exit_code);
}
