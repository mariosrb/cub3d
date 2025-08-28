#include "../../includes/cub3d.h"

void	count_dimensions(char **old_map, t_map *new_map)
{
	int	i;
	int	height;
	int	width;
	int	temp;

	temp = 0;
	width = 0;
	height = 0;
	i = get_start_line(old_map);
	while (old_map[i] && is_map(old_map[i]) == true)
	{
		height++;
		temp = ft_strlen(old_map[i]);
		if (temp > width)
			width = temp;
		i++;
	}
	new_map->height = height;
	new_map->width = width;
}

int	get_start_line(char **old_map)
{
	int	i;

	i = 0;
	while (old_map[i]
		&& (is_config_param(old_map[i]) == true || is_map(old_map[i]) == false))
		i++;
	return (i);
}

bool	is_fillable_space(t_map *map, int pos1, int pos2)
{
	if (map->grid[pos1][pos2] != ' ')
		return (false);
	if (is_next_fill(map, pos1, pos2 + 1) == false)
		return (false);
	if (is_next_fill(map, pos1, pos2 - 1) == false)
		return (false);
	if (is_next_fill(map, pos1 + 1, pos2) == false)
		return (false);
	if (is_next_fill(map, pos1 - 1, pos2) == false)
		return (false);
	return (true);
}

bool	is_next_fill(t_map *map, int pos1, int pos2)
{
	if (pos1 < 0 || pos1 >= map->height)
		return (true);
	if (!map->grid[pos1][pos2])
		return (true);
	if (map->grid[pos1][pos2] != ' ' && map->grid[pos1][pos2] != '1')
		return (false);
	return (true);
}
