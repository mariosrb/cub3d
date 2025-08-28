#include "../../includes/cub3d.h"

void parser_free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

int	print_error(int er_code)
{
	if (er_code == ERROR_EXTENSION)
		printf("Error: wrong file extension or file name\n");
	else if (er_code == ERROR_FILE)
		printf("Error: couldn't open or read the file\n");
	else if (er_code == ERROR_CONFIG)
		printf("Error: wrong configuration element(s)\n");
	else if (er_code == ERROR_MEMORY)
		printf("Error: a memory error has occured\n");
	else if (er_code == ERROR_WALLS)
		printf("Error: map not properly surrounded by walls\n");
	else if (er_code == ERROR_CHARACTERS)
		printf("Error: extra or missing characters on the map\n");
	else if (er_code == ERROR_MAP)
		printf("Error: incorrect map\n");
	else if (er_code == ERROR_ARGS)
		printf("Error: invalid arguments\n");
	return (1);
}

void	parser_free_all(t_config *config, t_map *map)
{
	if (map->grid)
		parser_free_lines(map->grid);
	map->grid = NULL;
	if (config->east_texture)
		free(config->east_texture);
	if (config->south_texture)
		free(config->south_texture);
	if (config->west_texture)
		free(config->west_texture);
	if (config->north_texture)
		free(config->north_texture);
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
}

int	return_error_parsing(t_config *config, t_map *map, int er_code)
{
	parser_free_all(config, map);
	print_error(er_code);
	return (1);
}
