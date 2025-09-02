/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:18:14 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 12:18:15 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray_data(t_ray_data *r, t_game *g, t_ray_dir ray_dir)
{
	r->map_x = (int)(g->player.pos_x / TILE_SIZE);
	r->map_y = (int)(g->player.pos_y / TILE_SIZE);
	r->hit = 0;
	if (ray_dir.x == 0)
		r->delta_distx = 1e30;
	else
		r->delta_distx = fabs(1 / ray_dir.x);
	if (ray_dir.y == 0)
		r->delta_disty = 1e30;
	else
		r->delta_disty = fabs(1 / ray_dir.y);
}

void	step_and_side(t_ray_data *r, t_game *g, t_ray_dir ray_dir)
{
	double	posx;
	double	posy;

	posx = g->player.pos_x / TILE_SIZE;
	posy = g->player.pos_y / TILE_SIZE;
	if (ray_dir.x < 0)
	{
		r->step_x = -1;
		r->side_distx = (posx - r->map_x) * r->delta_distx;
	}
	else
	{
		r->step_x = 1;
		r->side_distx = (r->map_x + 1.0 - posx) * r->delta_distx;
	}
	if (ray_dir.y < 0)
	{
		r->step_y = -1;
		r->side_disty = (posy - r->map_y) * r->delta_disty;
	}
	else
	{
		r->step_y = 1;
		r->side_disty = (r->map_y + 1.0 - posy) * r->delta_disty;
	}
}

void	perform_dda(t_ray_data *ray, t_game *game)
{
	while (ray->hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= game->map.height \
			|| ray->map_x >= game->map.width \
			|| game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	wall_dist_pos(t_ray_data *r, t_game *g, t_ray_dir ray_dir)
{
	double	pos_x;
	double	pos_y;

	pos_x = g->player.pos_x / TILE_SIZE;
	pos_y = g->player.pos_y / TILE_SIZE;
	if (r->side == 0)
		r->perp_wall_dist = (r->side_distx - r->delta_distx);
	else
		r->perp_wall_dist = (r->side_disty - r->delta_disty);
	if (r->perp_wall_dist <= 0.001)
		r->perp_wall_dist = 0.001;
	if (r->side == 0)
		r->wall_x = pos_y + r->perp_wall_dist * ray_dir.y;
	else
		r->wall_x = pos_x + r->perp_wall_dist * ray_dir.x;
	r->wall_x -= floor(r->wall_x);
}
