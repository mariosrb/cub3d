#include "../../includes/cub3d.h"

void draw_minimap(t_game *game)
{
	int			scale;
	int			map_x;
	int			map_y;
	int i, j;
	t_square	square;

	scale = 8;
	map_x = 20;
	map_y = 20;
	i = 0;
	while (i < game->map.height && game->map.grid[i])
	{
		j = 0;
		while (j < game->map.width && game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == '1')
			{
				square.x = map_x + j * scale;
				square.y = map_y + i * scale;
				square.size = scale;
				square.color = BLACK;
				draw_square(square, game);
			}
			else if (game->map.grid[i][j] == '0')
			{
				square.x = map_x + j * scale;
				square.y = map_y + i * scale;
				square.size = scale;
				square.color = GREEN;
				draw_square(square, game);
			}
			j++;
		}
		i++;
	}
	square.x = map_x + (game->player.pos_x / TILE_SIZE) * scale - 2;
	square.y = map_y + (game->player.pos_y / TILE_SIZE) * scale - 2;
	square.size = 4;
	square.color = RED;
	draw_square(square, game);
}
