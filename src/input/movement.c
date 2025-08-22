#include "../../includes/cub3d.h"

static void rotate_left(t_player *p, double angle_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dirX;
	p->dirX = p->dirX * cos(angle_speed) - p->dirY * sin(angle_speed);
	p->dirY = old_dir_x * sin(angle_speed) + p->dirY * cos(angle_speed);
	old_plane_x = p->planeX;
	p->planeX = p->planeX * cos(angle_speed) - p->planeY * sin(angle_speed);
	p->planeY = old_plane_x * sin(angle_speed) + p->planeY * cos(angle_speed);
}

static void rotate_right(t_player *p, double angle_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dirX;
	p->dirX = p->dirX * cos(-angle_speed) - p->dirY * sin(-angle_speed);
	p->dirY = old_dir_x * sin(-angle_speed) + p->dirY * cos(-angle_speed);
	old_plane_x = p->planeX;
	p->planeX = p->planeX * cos(-angle_speed) - p->planeY * sin(-angle_speed);
	p->planeY = old_plane_x * sin(-angle_speed) + p->planeY * cos(-angle_speed);
}

static void	move_player(t_player *p, double vec_x, double vec_y, double speed)
{
	p->pos_x += vec_x * speed;
	p->pos_y += vec_y * speed;
}

void player_move(t_player *player)
{
	double	speed;
	double	angle_speed;

	speed = 3.0;
	angle_speed = 0.01;
	if (player->rotate_left)
		rotate_left(player, angle_speed);
	if (player->rotate_right)
		rotate_right(player, angle_speed);
	if (player->move_up)
		move_player(player, player->dirX, player->dirY, speed);
	if (player->move_down)
		move_player(player, -player->dirX, -player->dirY, speed);
	if (player->move_left)
		move_player(player, -player->planeX, -player->planeY, speed);
	if (player->move_right)
		move_player(player, player->planeX, player->planeY, speed);
}
