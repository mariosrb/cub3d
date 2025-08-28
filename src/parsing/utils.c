#include "../../includes/cub3d.h"

bool	parser_is_valid_extension(const char *filename)
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

void	remove_nline(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && i > 0)
			str[i] = '\0';
		i++;
	}
}

void	print_strs(char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] != NULL)
	{
		while (strs[i][j])
		{
			write (1, &strs[i][j], 1);
			j++;
		}
		write (1, "\n", 1);
		i++;
		j = 0;
	}
}
