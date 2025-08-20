#include "../../includes/cub3d.h"

void	player_move(t_player *player)
{
	int	speed;

	speed = 10;
	if (player->move_down)
		player->pos_y += speed;
	if (player->move_up)
		player->pos_y -= speed;
	if (player->move_left)
		player->pos_x -= speed;
	if (player->move_right)
		player->pos_x += speed;
}
