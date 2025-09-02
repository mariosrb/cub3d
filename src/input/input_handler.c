/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:30:09 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 14:32:15 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_program(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->config.textures[i].img)
			mlx_destroy_image(game->mlx, game->config.textures[i].img);
		i++;
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	parser_free_all(&game->config, &game->map);
	exit(0);
	return (0);
}

int	handle_close_button(t_game *game)
{
	close_program(game);
	return (0);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_program(game);
	update_player_press(keycode, &game->player);
	return (0);
}

int	handle_keyrelease(int keycode, t_game *game)
{
	update_player_release(keycode, &game->player);
	return (0);
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
	if (keycode == LEFT)
		player->rotate_left = true;
	if (keycode == RIGHT)
		player->rotate_right = true;
	return (0);
}
