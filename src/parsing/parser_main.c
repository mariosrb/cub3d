#include "../includes/cub3d.h"

// t_error_code	parser_parse_file(const char *filename, t_game *game)
// {

// }

static char	**parser_second_step_read(const char *filename, int line_count)
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
	map = parser_second_step_read(filename, line_count);
	if (!map)
		return (NULL);
	close (fd);
	return (map);
}
