#include "../includes/game.h"

void	init_player(t_player *player)
{
	player->pos_x = WIDTH / 2;
	player->pos_y = HEIGHT / 2;
	player->move_down = false;
	player->move_up = false;
	player->move_left = false;
	player->move_right = false;
}

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

void	player_move(t_player *player)
{
	int	speed;

	speed = 3;
	if (player->move_down)
		player->pos_y += speed;
	if (player->move_up)
		player->pos_y -= speed;
	if (player->move_left)
		player->pos_x -= speed;
	if (player->move_right)
		player->pos_x += speed;
}
