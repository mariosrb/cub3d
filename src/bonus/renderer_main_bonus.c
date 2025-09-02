#include "../../includes/cub3d.h"

void	draw_map(t_game *game)
{
	t_square	square;
	int			i;
	int			j;

	i = 0;
	while (i < game->map.height && game->map.grid[i])
	{
		j = 0;
		while (j < game->map.width && game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == '1')
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
	player_move_bonus(&game->player, game);
	player_move_strafe(&game->player, game);
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
		t_ray_dir	ray_dir;
		ray_dir.x = game->player.dirX + game->player.planeX * cameraX;
		ray_dir.y = game->player.dirY + game->player.planeY * cameraX;
		cast_dda_ray(game, ray_dir, x);
		x++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
