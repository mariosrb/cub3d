/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_main_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:40:27 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 16:04:34 by mdodevsk         ###   ########.fr       */
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
	t_square	player_square;
	t_game		*game;
	int			x;
	double		camera_x;
	t_ray_dir	ray_dir;

	game = (t_game *)param;
	x = 0;
	clear_image(game);
	player_move_bonus(&game->player, game);
	player_move_strafe(&game->player, game);
	if (DEBUG)
	{
		player_square.x = game->player.pos_x;
		player_square.y = game->player.pos_y;
		player_square.size = 25;
		player_square.color = GREEN;
		draw_square(player_square, game);
		draw_map(game);
	}
	draw_loop_while(&x, &camera_x, &ray_dir, game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

void	draw_loop_while(int *x, double *camx, t_ray_dir *ray_dir, t_game *game)
{
	while (*x < WIDTH)
	{
		*camx = 2 * *x / (double)WIDTH - 1;
		ray_dir->x = game->player.dirx + game->player.planex * *camx;
		ray_dir->y = game->player.diry + game->player.planey * *camx;
		cast_dda_ray(game, *ray_dir, *x);
		(*x)++;
	}
}
