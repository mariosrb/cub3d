#include "../../includes/cub3d.h"

int	load_texture(t_game *game, char *path)
{
	// Charger l'image XPM
	game->texture = mlx_xpm_file_to_image(game->mlx, path,
		&game->tex_width, &game->tex_height);

	if (!game->texture)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}

	// Récupérer les données de l'image
	game->tex_data = mlx_get_data_addr(game->texture,
		&game->tex_bpp, &game->tex_line_len, &game->tex_endian);

	if (!game->tex_data)
	{
		printf("Error\nFailed to get texture data\n");
		return (0);
	}

	printf("Texture loaded: %dx%d from %s\n",
		game->tex_width, game->tex_height, path);
	return (1);
}

int	get_texture_pixel(t_game *game, int x, int y)
{
	int	pixel_index;
	int	color;

	// Vérifier les limites
	if (x < 0 || x >= game->tex_width || y < 0 || y >= game->tex_height)
		return (0);

	// Calculer l'index du pixel dans la data
	pixel_index = (y * game->tex_line_len) + (x * (game->tex_bpp / 8));

	// Récupérer la couleur (format BGR dans MLX)
	color = *(int*)(game->tex_data + pixel_index);

	return (color);
}
