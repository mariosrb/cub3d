#include "../../includes/cub3d.h"

bool	is_same_word(char *str1, char *str2)
{
	while (is_space(*str1) == true)
		str1++;
	while (*str1 && is_space(*str1) == false)
	{
		if (*str1 != *str2)
			return (false);
		str1++;
		str2++;
	}
	if (*str2)
		return (false);
	return (true);
}

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_config_param(char *line)
{
	if (is_same_word(line, "NO") == true)
		return (true);
	if (is_same_word(line, "SO") == true)
		return (true);
	if (is_same_word(line, "WE") == true)
		return (true);
	if (is_same_word(line, "EA") == true)
		return (true);
	if (is_same_word(line, "F") == true)
		return (true);
	if (is_same_word(line, "C") == true)
		return (true);
	return (false);
}

bool	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]) == false && line[i] != '\n')
			return (true);
		i++;
	}
	return (false);
}
