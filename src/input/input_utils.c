/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:31:08 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 14:32:04 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	if (keycode == LEFT)
		player->rotate_left = false;
	if (keycode == RIGHT)
		player->rotate_right = false;
	return (0);
}
