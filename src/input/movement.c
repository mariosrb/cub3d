/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:29:29 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 16:07:44 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_left(t_player *p, double angle_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dirx;
	p->dirx = p->dirx * cos(angle_speed) - p->diry * sin(angle_speed);
	p->diry = old_dir_x * sin(angle_speed) + p->diry * cos(angle_speed);
	old_plane_x = p->planex;
	p->planex = p->planex * cos(angle_speed) - p->planey * sin(angle_speed);
	p->planey = old_plane_x * sin(angle_speed) + p->planey * cos(angle_speed);
}

static void	rotate_right(t_player *p, double angle_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dirx;
	p->dirx = p->dirx * cos(-angle_speed) - p->diry * sin(-angle_speed);
	p->diry = old_dir_x * sin(-angle_speed) + p->diry * cos(-angle_speed);
	old_plane_x = p->planex;
	p->planex = p->planex * cos(-angle_speed) - p->planey * sin(-angle_speed);
	p->planey = old_plane_x * sin(-angle_speed) + p->planey * cos(-angle_speed);
}

static void	move_player(t_player *p, double vec_x, double vec_y, double speed)
{
	p->pos_x += vec_x * speed;
	p->pos_y += vec_y * speed;
}

void	player_move(t_player *player, t_game *game)
{
	double	speed;
	double	angle_speed;

	(void)game;
	speed = 2.0;
	angle_speed = 0.05;
	if (player->rotate_left)
		rotate_left(player, angle_speed);
	if (player->rotate_right)
		rotate_right(player, angle_speed);
	if (player->move_up)
		move_player(player, player->dirx, player->diry, speed);
	if (player->move_down)
		move_player(player, -player->dirx, -player->diry, speed);
	if (player->move_left)
		move_player(player, -player->planex, -player->planey, speed);
	if (player->move_right)
		move_player(player, player->planex, player->planey, speed);
}
