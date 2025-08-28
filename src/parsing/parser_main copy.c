#include "../../includes/cub3d.h"

int	parser_main(const char *filename, t_config *config, t_map *final_map)
{
	int		er_code;
	char	**map;

	er_code = 0;
	init_parser(&map, config, final_map);
	if (parser_is_valid_extension(filename) == false)
		return (ERROR_EXTENSION);
	map = parser_read_file_lines(filename);
	if (!map)
		return (ERROR_FILE);
	er_code = check_config(map, config);
	if (er_code != SUCCESS)
	{
		parser_free_lines(map);
		return (er_code);
	}
	er_code = get_map(map, final_map);
	parser_free_lines(map);
	return (er_code);
}

void	init_parser(char ***map, t_config *config, t_map *final_map)
{
	*map = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->floor_b = -1;
	config->floor_g = -1;
	config->floor_r = -1;
	config->ceiling_b = -1;
	config->ceiling_g = -1;
	config->ceiling_r = -1;
	final_map->grid = 0;
	final_map->height = 0;
	final_map->grid = NULL;
}

char	**parser_second_step_read(const char *filename, int line_count)
{
	int		i;
	char	**lines;
	char	*line;
	int		fd;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	line = get_next_line(fd);
	while (i < line_count)
	{
		remove_nline(line);
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

char	**parser_read_file_lines(const char *filename)
{
	int		fd;
	int		line_count;
	char	*line;
	char	**map;

	if (!filename)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	if (line_count <= 0)
		return (NULL);
	map = parser_second_step_read(filename, line_count);
	return (map);
}
