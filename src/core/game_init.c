#include "../../includes/cub3d.h"

void init_config(t_config *config)
{
	ft_memset(config, 0, sizeof(t_config));
	config->floor_r = -1;
	config->floor_g = -1;
	config->floor_b = -1;
	config->ceiling_r = -1;
	config->ceiling_g = -1;
	config->ceiling_b = -1;
}

void init_game(t_game *g, t_config *config, t_map *map)
{
	g->config = *config;
	g->map = *map;
	init_player(&g->player, g);
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	if (!load_texture(g, g->config.north_texture, 0) ||
		!load_texture(g, g->config.south_texture, 1) ||
		!load_texture(g, g->config.east_texture, 2) ||
		!load_texture(g, g->config.west_texture, 3))
	{
		printf("Error\nTexture loading failed\n");
		exit(1);
	}
	g->config.floor_color = create_rgb(g->config.floor_r, g->config.floor_g, g->config.floor_b);
	g->config.ceiling_color = create_rgb(g->config.ceiling_r, g->config.ceiling_g, g->config.ceiling_b);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}
