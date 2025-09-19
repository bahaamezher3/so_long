/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:11:13 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 14:11:13 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen_custom(filename);
	if (len < 4)
		return (0);
	if (filename[len - 4] != '.' || filename[len - 3] != 'b'
		|| filename[len - 2] != 'e' || filename[len - 1] != 'r')
		return (0);
	return (1);
}

int	check_file_access(char *filename)
{
	int	fd;

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

int	get_clean_length(char *line)
{
	int	len;
	int	orig_len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	orig_len = len;
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'
			|| line[len - 1] == ' ' || line[len - 1] == '\t'))
	{
		line[len - 1] = '\0';
		len--;
	}
	if (len == 0 && orig_len > 0)
		return (0);
	return (len);
}

void	freer(char **map, int i)
{
	int	k;

	k = 0;
	if (!map)
		return ;
	while (k < i)
	{
		if (map[k])
			free(map[k]);
		k++;
	}
	free(map);
}
