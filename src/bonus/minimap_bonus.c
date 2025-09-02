/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:37:21 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 15:44:41 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_minimap(t_game *game)
{
	int			scale;
	t_minimap	map;
	t_square	square;

	init_numbers(&map.i, &map.x, &map.y, &scale);
	while (map.i < game->map.height && game->map.grid[map.i])
	{
		minimap_loop(game, &square, &map, &scale);
		map.i++;
	}
	square.x = map.x + (game->player.pos_x / TILE_SIZE) * scale - 2;
	square.y = map.y + (game->player.pos_y / TILE_SIZE) * scale - 2;
	square.size = 4;
	square.color = RED;
	draw_square(square, game);
}

void	init_numbers(int *i, double *x, double *y, int *scale)
{
	*scale = 8;
	*x = 20;
	*y = 20;
	*i = 0;
}

void	minimap_loop(t_game *game, t_square *sqr, t_minimap *map, int *scale)
{
	int	j;

	j = 0;
	while (j < game->map.width && game->map.grid[map->i][j])
	{
		if (game->map.grid[map->i][j] == '1')
		{
			sqr->x = map->x + j * *scale;
			sqr->y = map->y + map->i * *scale;
			sqr->size = *scale;
			sqr->color = BLACK;
			draw_square(*sqr, game);
		}
		else if (game->map.grid[map->i][j] == '0')
		{
			sqr->x = map->x + j * *scale;
			sqr->y = map->y + map->i * *scale;
			sqr->size = *scale;
			sqr->color = GREEN;
			draw_square(*sqr, game);
		}
		j++;
	}
}
