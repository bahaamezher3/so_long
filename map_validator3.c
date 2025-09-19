/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmezher <bmezher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:10:16 by bmezher           #+#    #+#             */
/*   Updated: 2025/09/16 15:12:29 by bmezher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	update_counts_and_validate_cell(char cell, int *count_p,
		int *count_e, int *count_c)
{
	if (cell == 'P')
		(*count_p)++;
	else if (cell == 'E')
		(*count_e)++;
	else if (cell == 'C')
		(*count_c)++;
	else if (cell != '0' && cell != '1')
		return (0);
	return (1);
}
