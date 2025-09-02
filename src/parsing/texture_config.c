/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:52 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 14:20:53 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	skip_id(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]) == true)
		i++;
	i += 2;
	while (is_space(line[i]) == true)
		i++;
	return (i);
}

bool	is_texture_param(char *line)
{
	if (is_same_word(line, "NO") == true)
		return (true);
	if (is_same_word(line, "SO") == true)
		return (true);
	if (is_same_word(line, "WE") == true)
		return (true);
	if (is_same_word(line, "EA") == true)
		return (true);
	return (false);
}

int	check_full_textures(t_config *config)
{
	if (!config->north_texture)
		return (ERROR_CONFIG);
	if (!config->south_texture)
		return (ERROR_CONFIG);
	if (!config->east_texture)
		return (ERROR_CONFIG);
	if (!config->west_texture)
		return (ERROR_CONFIG);
	return (SUCCESS);
}

char	*ft_strdup_space(const char *s1)
{
	size_t	i;
	size_t	size;
	char	*dest;

	if (!s1)
		return (NULL);
	i = 0;
	size = ft_strlen_space(s1);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen_space(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}
