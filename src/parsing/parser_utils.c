#include "../includes/cub3d.h"

bool parser_is_valid_extension(const char *filename)
{
	int	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (false);
	if (filename[len - 5] == '/')
		return (false);
	return (true);
}


