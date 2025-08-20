#include "../../includes/cub3d.h"

// int	main (int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	printf("map.cub: %d\n", parser_is_valid_extension("map.cub"));        // 1 ✅
// 	printf("map.cubewrewr: %d\n", parser_is_valid_extension("map.cubewrewr")); // 0 ❌
// 	printf("map.cub.txt: %d\n", parser_is_valid_extension("map.cub.txt"));    // 0 ❌
// 	printf("a.cub: %d\n", parser_is_valid_extension("a.cub"));               // 1 ✅
// 	printf(".cub: %d\n", parser_is_valid_extension(".cub"));                 // 0 ❌
// 	return (0);
// }

// Fonction qui met des pixels
void	put_pixel(t_game *game, int x, int y, int color)
{
	int	pixel;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return ;
	pixel = (y * game->size_line) + (x * (game->bpp / 8));
	game->data[pixel + 0] = (color) & 0xFF;
	game->data[pixel + 1] = (color >> 8) & 0xFF;
	game->data[pixel + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_game *game, int size, int color)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = (int)game->player.pos_x;
	y = (int)game->player.pos_y;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			if (i == 0 || i == size - 1 || j == 0 || j == size - 1)
				put_pixel(game, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void clear_image(t_game *game)
{
    int i = 0;
    int total = WIDTH * HEIGHT * (game->bpp / 8);

    while (i < total)
    {
        game->data[i] = 0;
        i++;
    }
}

void	init_game(t_game *g)
{
	init_player(&g->player);
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

int draw_loop(void *param)
{
    t_game *game = (t_game *)param;

    clear_image(game);
    player_move(&game->player);
    draw_square(game, 25, 0x00FF00);  // Carré vert de 25px
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

int	main(void)
{
	t_game	game;

	init_game(&game);

	mlx_hook(game.win, 2, 1L<<0, update_player_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, update_player_release, &game.player);

	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	return (0);
}
