/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:16:14 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 16:09:15 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_tex_num(int r_side, t_ray_dir r_dir)
{
	if (r_side == 0)
	{
		if (r_dir.x > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (r_dir.y > 0)
			return (1);
		else
			return (0);
	}
}

void	cal_txt_dta(t_text_data *t, t_ray_data *r, t_game *g, t_ray_dir r_dir)
{
	t->tex_num = get_tex_num(r->side, r_dir);
	t->tex_x = (int)(r->wall_x * g->config.textures[t->tex_num].width);
	if (r->side == 0 && r_dir.x > 0)
		t->tex_x = g->config.textures[t->tex_num].width - t->tex_x - 1;
	if (r->side == 1 && r_dir.y < 0)
		t->tex_x = g->config.textures[t->tex_num].width - t->tex_x - 1;
	t->line_height = (int)(HEIGHT / r->perp_wall_dist);
	t->draw_start = -t->line_height / 2 + HEIGHT / 2;
	if (t->draw_start < 0)
		t->draw_start = 0;
	t->draw_end = t->line_height / 2 + HEIGHT / 2;
	if (t->draw_end >= HEIGHT)
		t->draw_end = HEIGHT - 1;
	t->step = 1.0 * g->config.textures[t->tex_num].height / t->line_height;
	t->tex_pos = (t->draw_start - HEIGHT / 2 + t->line_height / 2) * t->step;
}

void	draw_wall(t_game *game, t_text_data *t, t_ray_data *ray, int x)
{
	int	y;
	int	color;

	y = t->draw_start;
	while (y < t->draw_end)
	{
		t->tex_y = (int)t->tex_pos;
		if (t->tex_y >= game->config.textures[t->tex_num].height)
			t->tex_y = game->config.textures[t->tex_num].height - 1;
		if (t->tex_y < 0)
			t->tex_y = 0;
		t->tex_pos += t->step;
		color = get_texture_pixel(game, t->tex_num, t->tex_x, t->tex_y);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		put_pixel(game, x, y, color);
		y++;
	}
}

void	draw_ceiling_and_floor(t_game *game, t_text_data *tex, int x)
{
	int	i;

	i = 0;
	while (i < tex->draw_start)
	{
		put_pixel(game, x, i, game->config.ceiling_color);
		i++;
	}
	i = tex->draw_end;
	while (i < HEIGHT)
	{
		put_pixel(game, x, i, game->config.floor_color);
		i++;
	}
}

void	cast_dda_ray(t_game *game, t_ray_dir ray_dir, int x)
{
	t_ray_data	ray;
	t_text_data	tex;

	init_ray_data(&ray, game, ray_dir);
	step_and_side(&ray, game, ray_dir);
	perform_dda(&ray, game);
	wall_dist_pos(&ray, game, ray_dir);
	cal_txt_dta(&tex, &ray, game, ray_dir);
	draw_wall(game, &tex, &ray, x);
	draw_ceiling_and_floor(game, &tex, x);
}
