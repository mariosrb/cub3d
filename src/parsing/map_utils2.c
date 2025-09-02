/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:33 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 14:20:34 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strdup_fill(const char *s1, int len)
{
	size_t	i;
	size_t	size;
	char	*dest;

	if (!s1)
		return (NULL);
	i = 0;
	size = ft_strlen(s1);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = s1[i];
		i++;
	}
	while (i < (size_t)len)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	valid_line(char *str, int i, int height, int width)
{
	int	j;

	j = 0;
	if (i == 0 || i == height - 1)
	{
		while (str[j])
		{
			if (str[j] != '1')
				return (1);
			j++;
		}
	}
	else
	{
		if (str[0] != '1' || str[width - 1] != '1')
		{
			return (1);
		}
	}
	return (0);
}

int	ok_char(char c)
{
	if (c == '1')
		return (SUCCESS);
	else if (c == 'N')
		return (SUCCESS);
	else if (c == 'E')
		return (SUCCESS);
	else if (c == '0')
		return (SUCCESS);
	else if (c == 'S')
		return (SUCCESS);
	else if (c == 'W')
		return (SUCCESS);
	else
		return (1);
}

bool	check_zero(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	if (count < 1)
		return (false);
	return (true);
}
