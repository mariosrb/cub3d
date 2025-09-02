/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:20:07 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 14:20:08 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_colors_syntax(char *line)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	j = 0;
	while (line[i] && is_space(line[i]) == false)
	{
		if (ft_isdigit(line[i]) == 1)
			k++;
		if (k > 3)
			return (ERROR_CONFIG);
		if (ft_isdigit(line[i]) == 0)
		{
			if (line[i] != ',')
				return (ERROR_CONFIG);
			k = 0;
			j++;
		}
		i++;
	}
	if (j != 2 || (j == 2 && k == 0))
		return (ERROR_CONFIG);
	return (SUCCESS);
}

bool	is_color_param(char *line)
{
	if (is_same_word(line, "F") == true)
		return (true);
	if (is_same_word(line, "C") == true)
		return (true);
	return (false);
}

int	skip_id_color(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]) == true)
		i++;
	i += 1;
	while (is_space(line[i]) == true)
		i++;
	return (i);
}

void	assign_rgb(char *line, int *r, int *g, int *b)
{
	int	i;

	i = 0;
	*r = ft_atoi(line);
	while (line[i] && ft_isdigit(line[i]) == 1)
		i++;
	i++;
	*g = ft_atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]) == 1)
		i++;
	i++;
	*b = ft_atoi(&line[i]);
}

int	check_rgb(t_config *config)
{
	if (config->ceiling_r < 0 || config->ceiling_r > 255)
		return (ERROR_CONFIG);
	if (config->ceiling_g < 0 || config->ceiling_g > 255)
		return (ERROR_CONFIG);
	if (config->ceiling_b < 0 || config->ceiling_b > 255)
		return (ERROR_CONFIG);
	if (config->floor_r < 0 || config->floor_r > 255)
		return (ERROR_CONFIG);
	if (config->floor_g < 0 || config->floor_g > 255)
		return (ERROR_CONFIG);
	if (config->floor_b < 0 || config->floor_b > 255)
		return (ERROR_CONFIG);
	return (SUCCESS);
}
