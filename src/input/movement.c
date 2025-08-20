#include "../../includes/cub3d.h"

void	player_move(t_player *player)
{
	int		speed;
	float	angle_speed;
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	angle_speed = 0.1;
	speed = 5;

	// Rotation
	if (player->rotate_left)
		player->angle -= angle_speed;
	if (player->rotate_right)
		player->angle += angle_speed;

	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->move_down)
	{
		player->pos_x -= cos_angle * speed;
		player->pos_y -= sin_angle * speed;
	}
	if (player->move_up)
	{
		player->pos_x += cos_angle * speed;
		player->pos_y += sin_angle * speed;
	}
	if (player->move_left)
	{
		player->pos_x += cos(player->angle - PI/2) * speed;
		player->pos_y += sin(player->angle - PI/2) * speed;
	}
	if (player->move_right)
	{
		player->pos_x += cos(player->angle + PI/2) * speed;
		player->pos_y += sin(player->angle + PI/2) * speed;
	}
}
