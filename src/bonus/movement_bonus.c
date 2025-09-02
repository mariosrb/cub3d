/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:39:27 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 16:03:48 by mdodevsk         ###   ########.fr       */
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

void	player_move_strafe(t_player *player, t_game *game)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = 2.0;
	if (player->move_left)
	{
		new_x = player->pos_x - player->planex * speed;
		new_y = player->pos_y - player->planey * speed;
		if (!is_touching(new_x, player->pos_y, game))
			player->pos_x = new_x;
		if (!is_touching(player->pos_x, new_y, game))
			player->pos_y = new_y;
	}
	if (player->move_right)
	{
		new_x = player->pos_x + player->planex * speed;
		new_y = player->pos_y + player->planey * speed;
		if (!is_touching(new_x, player->pos_y, game))
			player->pos_x = new_x;
		if (!is_touching(player->pos_x, new_y, game))
			player->pos_y = new_y;
	}
}

static void	move_forward_back(t_player *player, t_game *game)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = 2.0;
	if (player->move_up)
	{
		new_x = player->pos_x + player->dirx * speed;
		new_y = player->pos_y + player->diry * speed;
		if (!is_touching(new_x, player->pos_y, game))
			player->pos_x = new_x;
		if (!is_touching(player->pos_x, new_y, game))
			player->pos_y = new_y;
	}
	if (player->move_down)
	{
		new_x = player->pos_x - player->dirx * speed;
		new_y = player->pos_y - player->diry * speed;
		if (!is_touching(new_x, player->pos_y, game))
			player->pos_x = new_x;
		if (!is_touching(player->pos_x, new_y, game))
			player->pos_y = new_y;
	}
}

void	player_move_bonus(t_player *player, t_game *game)
{
	double	angle_speed;

	angle_speed = 0.05;
	if (player->rotate_left)
		rotate_left(player, angle_speed);
	if (player->rotate_right)
		rotate_right(player, angle_speed);
	move_forward_back(player, game);
}
