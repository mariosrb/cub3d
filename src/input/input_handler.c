#include "../../includes/cub3d.h"

int	update_player_press(int keycode, t_player *player)
{
	if (keycode == W)
		player->move_up = true;
	if (keycode == S)
		player->move_down = true;
	if (keycode == D)
		player->move_right = true;
	if (keycode == A)
		player->move_left = true;
	return (0);
}

int	update_player_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->move_up = false;
	if (keycode == S)
		player->move_down = false;
	if (keycode == D)
		player->move_right = false;
	if (keycode == A)
		player->move_left = false;
	return (0);
}
