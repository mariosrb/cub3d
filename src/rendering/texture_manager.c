/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:21:31 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 14:27:35 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	load_texture(t_game *game, char *path, int texture_index)
{
	game->config.textures[texture_index].img = mlx_xpm_file_to_image(
			game->mlx, path, &game->config.textures[texture_index].width,
			&game->config.textures[texture_index].height);
	if (!game->config.textures[texture_index].img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	game->config.textures[texture_index].addr = mlx_get_data_addr(
			game->config.textures[texture_index].img,
			&game->config.textures[texture_index].bits_per_pixel,
			&game->config.textures[texture_index].line_lenght,
			&game->config.textures[texture_index].endian);
	if (!game->config.textures[texture_index].addr)
	{
		printf("Error\nFailed to get texture data\n");
		return (0);
	}
	printf("Texture %d loaded: %dx%d from %s\n",
		texture_index, game->config.textures[texture_index].width,
		game->config.textures[texture_index].height, path);
	return (1);
}

int	get_texture_pixel(t_game *game, int texture_index, int x, int y)
{
	int			color;
	int			pixel_index;
	t_texture	*tex;

	tex = &game->config.textures[texture_index];
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel_index = (y * tex->line_lenght) + (x * (tex->bits_per_pixel / 8));
	color = *(int *)(tex->addr + pixel_index);
	return (color);
}
