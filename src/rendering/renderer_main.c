#include "../../includes/cub3d.h"

void	draw_map(t_game *game)
{
	char	**map;
	int		i;
	int		j;

	map = game->map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, BLUE, game);
			j++;
		}
		i++;
	}
}

int	draw_loop(void *param)
{
    t_game *game = (t_game *)param;
	int		x;

	x = 0;
    clear_image(game);
    player_move(&game->player);

    if (DEBUG)
    {
        draw_square(game->player.pos_x, game->player.pos_y, 25, GREEN, game);
        draw_map(game);
    }
    while (x < WIDTH)
    {
        double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        double rayDirX = game->player.dirX + game->player.planeX * cameraX;
        double rayDirY = game->player.dirY + game->player.planeY * cameraX;
        cast_dda_ray(game, rayDirX, rayDirY, x);
		x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}
