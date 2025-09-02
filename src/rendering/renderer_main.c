/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:19:43 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 16:09:32 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map(t_game *game)
{
	t_square	square;
	int			i;
	int			j;

	i = 0;
	while (i < game->map.height && game->map.grid[i])
	{
		j = 0;
		while (j < game->map.width && game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == '1')
			{
				square.x = j * TILE_SIZE;
				square.y = i * TILE_SIZE;
				square.size = TILE_SIZE;
				square.color = BLUE;
				draw_square(square, game);
			}
			j++;
		}
		i++;
	}
}

int	draw_loop(void *param)
{
	t_game		*game;
	int			x;
	double		camera_x;
	t_ray_dir	ray_dir;

	game = (t_game *)param;
	x = 0;
	clear_image(game);
	player_move(&game->player, game);
	while (x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		ray_dir.x = game->player.dirx + game->player.planex * camera_x;
		ray_dir.y = game->player.diry + game->player.planey * camera_x;
		cast_dda_ray(game, ray_dir, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
