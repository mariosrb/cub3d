/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:38 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 14:20:39 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_map(char **old_map, t_map *new_map)
{
	int	er_code;

	er_code = 0;
	er_code = copy_map(old_map, new_map);
	if (er_code != SUCCESS)
		return (er_code);
	fill_map(new_map);
	if (valid_walls(new_map) != 0)
		return (ERROR_WALLS);
	er_code = valid_characters(new_map);
	return (er_code);
}

int	copy_map(char **old_map, t_map *new_map)
{
	int	i;
	int	j;

	i = get_start_line(old_map);
	j = 0;
	count_dimensions(old_map, new_map);
	if (new_map->height < 1 || new_map->width < 1)
		return (ERROR_MAP);
	new_map->grid = malloc(sizeof(char *) * (new_map->height + 1));
	if (!new_map->grid)
		return (ERROR_MEMORY);
	while (old_map[i] && is_map(old_map[i]) == true)
	{
		new_map->grid[j] = ft_strdup_fill(old_map[i], new_map->width);
		if (!new_map->grid[j])
			return (ERROR_MEMORY);
		i++;
		j++;
	}
	new_map->grid[j] = NULL;
	return (SUCCESS);
}

int	fill_map(t_map *new_map)
{
	int	i;
	int	j;

	i = 0;
	while (new_map->grid[i])
	{
		j = 0;
		while (new_map->grid[i][j])
		{
			if (is_fillable_space(new_map, i, j) == true)
				new_map->grid[i][j] = '1';
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	valid_walls(t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i])
	{
		if (valid_line(map->grid[i], i, map->height, map->width) != 0)
		{
			return (1);
		}
		i++;
	}
	return (SUCCESS);
}

int	valid_characters(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == ' ')
				return (ERROR_WALLS);
			if (ok_char(map->grid[i][j]) != 0)
				return (ERROR_CHARACTERS);
			if (map->grid[i][j] == 'E' || map->grid[i][j] == 'S'
			|| map->grid[i][j] == 'N' || map->grid[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1 || check_zero(map->grid) == false)
		return (ERROR_CHARACTERS);
	return (SUCCESS);
}
