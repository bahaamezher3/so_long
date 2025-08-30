/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 09:14:19 by bmezher           #+#    #+#             */
/*   Updated: 2025/07/14 14:59:29 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_and_full(int fd, char *full);
char	*extract_line(char *full);
char	*new_full(char *full);
int		ft_strlen(char *str);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif