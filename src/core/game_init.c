#include "../../includes/cub3d.h"

static void	init_map_structure(t_map *mapp)
{
	mapp->grid = malloc(sizeof(char *) * 11);
	if (!mapp->grid)
		return ;

	mapp->grid[0] = "111111111111111";
	mapp->grid[1] = "100000000000001";
	mapp->grid[2] = "100010000100001";
	mapp->grid[3] = "100010000001001";
	mapp->grid[4] = "100000101000001";
	mapp->grid[5] = "1001001W1000001";
	mapp->grid[6] = "100000111000001";
	mapp->grid[7] = "100000000000001";
	mapp->grid[8] = "100000000000001";
	mapp->grid[9] = "111111111111111";
	mapp->grid[10] = NULL;

	mapp->width = 15;
	mapp->height = 10;
}

void init_game(t_game *g)
{
	init_map_structure(&g->mapp);
	init_player(&g->player, g);
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	if (!load_texture(g, "assets/north.xpm", 0) ||
		!load_texture(g, "assets/south.xpm", 1) ||
    	!load_texture(g, "assets/east.xpm", 2) ||
    	!load_texture(g, "assets/west.xpm", 3))
	{
		printf("Error\nTexture loading failed\n");
		exit(1);
	}
	g->config.floor_b = 128;
	g->config.floor_g = 128;
	g->config.floor_r = 128;
	g->config.ceiling_b = 235;
	g->config.ceiling_r = 135;
	g->config.ceiling_g = 206;
	g->config.floor_color = create_rgb(g->config.floor_r, g->config.floor_g, g->config.floor_b);
	g->config.ceiling_color = create_rgb(g->config.ceiling_r, g->config.ceiling_g, g->config.ceiling_b);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}
