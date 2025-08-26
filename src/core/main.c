#include "../../includes/cub3d.h"

// Fonction qui met des pixels
void put_pixel(t_game *game, int x, int y, int color)
{
	int pixel;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return;
	pixel = (y * game->size_line) + (x * (game->bpp / 8));
	game->data[pixel + 0] = (color) & 0xFF;
	game->data[pixel + 1] = (color >> 8) & 0xFF;
	game->data[pixel + 2] = (color >> 16) & 0xFF;
}

void draw_square(t_square square, t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j <= square.size)
	{
		i = 0;
		while (i <= square.size)
		{
			if (i == 0 || i == square.size || j == 0 || j == square.size)
				put_pixel(game, square.x + i, square.y + j, square.color);
			i++;
		}
		j++;
	}
}

bool	is_touching(float px, float py, t_game *game)
{
	int x;
	int y;

	x = px / TILE_SIZE;
	y = py / TILE_SIZE;
	if (x < 0 || y < 0 || y >= game->mapp.height || x >= game->mapp.width)
		return (true);
	if (game->mapp.grid[y][x] == '1')
		return (true);
	return (false);
}

int main(void)
{
	t_game game;

	init_game(&game);

	mlx_hook(game.win, 2, 1L << 0, update_player_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, update_player_release, &game.player);

	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	return (0);
}
