#include "../../includes/cub3d.h"

void player_move(t_player *player)
{
    double speed;
    double angle_speed;

	speed = 3.0;
	angle_speed = 0.01;
    if (player->rotate_left)
    {
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(angle_speed) - player->dirY * sin(angle_speed);
        player->dirY = oldDirX * sin(angle_speed) + player->dirY * cos(angle_speed);

        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(angle_speed) - player->planeY * sin(angle_speed);
        player->planeY = oldPlaneX * sin(angle_speed) + player->planeY * cos(angle_speed);
    }

    if (player->rotate_right)
    {
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-angle_speed) - player->dirY * sin(-angle_speed);
        player->dirY = oldDirX * sin(-angle_speed) + player->dirY * cos(-angle_speed);

        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-angle_speed) - player->planeY * sin(-angle_speed);
        player->planeY = oldPlaneX * sin(-angle_speed) + player->planeY * cos(-angle_speed);
    }

	if (player->move_up)
    {
        player->pos_x += player->dirX * speed;
        player->pos_y += player->dirY * speed;
    }
    if (player->move_down)
    {
        player->pos_x -= player->dirX * speed;
        player->pos_y -= player->dirY * speed;
    }
    if (player->move_left)
    {
        player->pos_x -= player->planeX * speed;
        player->pos_y -= player->planeY * speed;
    }
    if (player->move_right)
    {
        player->pos_x += player->planeX * speed;
        player->pos_y += player->planeY * speed;
    }
}
