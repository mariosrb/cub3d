#include "../../includes/cub3d.h"

void clear_image(t_game *game)
{
	int i;
	int	total;

	i = 0;
	total = WIDTH * HEIGHT * (game->bpp / 8);
	while (i < total)
	{
		game->data[i] = 0;
		i++;
	}
}

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
