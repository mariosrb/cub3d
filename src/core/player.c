#include "../../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->pos_x = WIDTH / 2;
	player->pos_y = HEIGHT / 2;
	player->move_down = false;
	player->move_up = false;
	player->move_left = false;
	player->move_right = false;
}


