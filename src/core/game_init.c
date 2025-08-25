#include "../../includes/cub3d.h"

void init_game(t_game *g)
{
	init_player(&g->player);
	g->map = init_map();
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
	printf("Texture dimensions: %ls x %ls\n", g->tex_width, g->tex_height);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}
