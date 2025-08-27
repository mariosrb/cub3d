#include "../../includes/cub3d.h"

void	draw_map(t_game *game)
{
	t_square	square;
	int			i;
	int			j;

	i = 0;
	while (i < game->mapp.height && game->mapp.grid[i])
	{
		j = 0;
		while (j < game->mapp.width && game->mapp.grid[i][j])
		{
			if (game->mapp.grid[i][j] == '1')
			{
				square.x = j * TILE_SIZE;
				square.y = i * TILE_SIZE;
				square.size = TILE_SIZE;
				square.color = BLUE;
				draw_square(square, game);
			}
			j++;
		}
		i++;
	}
}

int	draw_loop(void *param)
{
	t_square	player_square;
    t_game *game = (t_game *)param;
	int		x;

	x = 0;
    clear_image(game);
	player_move(&game->player, game);
    // player_move(&game->player, game);
	// player_move_strafe(&game->player, game);
    if (DEBUG)
    {
		player_square.x = game->player.pos_x;
		player_square.y = game->player.pos_y;
		player_square.size = 25;
		player_square.color = GREEN;
        draw_square(player_square, game);
        draw_map(game);
    }
    while (x < WIDTH)
    {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = game->player.dirX + game->player.planeX * cameraX;
        double rayDirY = game->player.dirY + game->player.planeY * cameraX;
        cast_dda_ray(game, rayDirX, rayDirY, x);
		x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}
