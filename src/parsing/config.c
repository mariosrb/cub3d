#include "../../includes/cub3d.h"

int	check_config(char **map, t_config *config)
{
	int		i;
	int		er_code;

	i = 0;
	er_code = 0;
	while (map[i])
	{
		if (is_config_param(map[i]) == true)
		{
			er_code = get_config(map[i], config);
			if (er_code != SUCCESS)
				return (er_code);
		}
		else if (is_map(map[i]) == true)
			break ;
		i++;
	}
	if (check_rgb(config) != SUCCESS)
		return (ERROR_CONFIG);
	if (check_full_textures(config) != SUCCESS)
		return (ERROR_CONFIG);
	return (0);
}

int	get_config(char *line, t_config *config)
{
	int	er_code;

	er_code = 0;
	if (count_word(line, ' ') != 2)
		return (ERROR_CONFIG);
	if (is_texture_param(line) == true)
		er_code = get_texture(line, config);
	if (is_color_param(line) == true)
		er_code = get_colors(line, config);
	return (er_code);
}

int	get_texture(char *line, t_config *config)
{
	int		i;
	int		fd;
	char	*file;

	fd = 0;
	i = skip_id(line);
	file = ft_strdup_space(&line[i]);
	if (!file)
		return (ERROR_MEMORY);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(file);
		return (ERROR_FILE);
	}
	close(fd);
	if (is_same_word(line, "NO") == true)
		config->north_texture = file;
	if (is_same_word(line, "SO") == true)
		config->south_texture = file;
	if (is_same_word(line, "WE") == true)
		config->west_texture = file;
	if (is_same_word(line, "EA") == true)
		config->east_texture = file;
	return (SUCCESS);
}

int	get_colors(char *line, t_config *config)
{
	int	i;

	i = skip_id_color(line);
	if (check_colors_syntax(&line[i]) != SUCCESS)
		return (ERROR_CONFIG);
	if (is_same_word(line, "F") == true)
		assign_rgb(&line[i], &config->floor_r, &config->floor_g,
			&config->floor_b);
	if (is_same_word(line, "C") == true)
		assign_rgb(&line[i], &config->ceiling_r, &config->ceiling_g,
			&config->ceiling_b);
	return (SUCCESS);
}
