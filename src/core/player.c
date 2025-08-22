#include "../../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->pos_x = WIDTH / 2;
	player->pos_y = HEIGHT / 2;
	player->dirX = -1.0;
	player->dirY = 0.0;
	player->planeX = 0.0;
	player->planeY = 0.66;
	player->move_down = false;
	player->move_up = false;
	player->move_left = false;
	player->move_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}


