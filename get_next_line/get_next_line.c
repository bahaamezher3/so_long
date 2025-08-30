/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:14:25 by bmezher           #+#    #+#             */
/*   Updated: 2025/07/14 14:59:31 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*full;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	full = read_and_full(fd, full);
	if (!full)
		return (NULL);
	line = extract_line(full);
	full = new_full(full);
	return (line);
}

char	*read_and_full(int fd, char *full)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(full, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		full = ft_strjoin(full, buffer);
	}
	free(buffer);
	return (full);
}

char	*extract_line(char *full)
{
	int		i;
	char	*line;

	i = 0;
	if (!full[i])
		return (NULL);
	while (full[i] && full[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (full[i] && full[i] != '\n')
	{
		line[i] = full[i];
		i++;
	}
	if (full[i] == '\n')
	{
		line[i] = full[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_full(char *full)
{
	int		i;
	int		j;
	char	*new_full;

	i = 0;
	while (full[i] && full[i] != '\n')
		i++;
	if (!full[i])
	{
		free(full);
		return (NULL);
	}
	new_full = malloc(sizeof(char) * (ft_strlen(full) - i + 1));
	if (!new_full)
		return (NULL);
	i++;
	j = 0;
	while (full[i])
		new_full[j++] = full[i++];
	new_full[j] = '\0';
	free(full);
	return (new_full);
}
