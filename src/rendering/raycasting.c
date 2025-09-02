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
		if (ray->map_x < 0 || ray->map_y < 0 || ray->map_y >= game->map.height ||
			ray->map_x >= game->map.width || game->map.grid[ray->map_y][ray->map_x] == '1')
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

static int	get_tex_num(int r_side, t_ray_dir r_dir)
{
	if (r_side == 0)
	{
		if (r_dir.x > 0)
			return 2;
		else
			return 3;
	}
	else
	{
		if (r_dir.y > 0)
			return 1;
		else
			return 0;
	}
}

void	cal_text_data(t_text_data *t, t_ray_data *r, t_game *g, t_ray_dir r_dir)
{
	t->tex_num = get_tex_num(r->side, r_dir);
	t->tex_x = (int)(r->wall_x * g->config.textures[t->tex_num].width);
	if (r->side == 0 && r_dir.y > 0)
		t->tex_x = g->config.textures[t->tex_num].width - t->tex_x - 1;
	if (r->side == 1 && r_dir.x < 0)
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
	while ( y < t->draw_end)
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
	t_ray_data		ray;
	t_text_data		tex;

	init_ray_data(&ray, game, ray_dir);
	step_and_side(&ray, game, ray_dir);
	perform_dda(&ray, game);
	wall_dist_pos(&ray, game, ray_dir);
	cal_text_data(&tex, &ray, game, ray_dir);
	draw_wall(game, &tex, &ray, x);
	draw_ceiling_and_floor(game, &tex, x);
}

// void	cast_dda_ray(t_game *game, t_ray_dir ray_dir, int x)
// {
//     //which box of the map we're in
//     int mapX = (int)(game->player.pos_x / TILE_SIZE);
//     int mapY = (int)(game->player.pos_y / TILE_SIZE);

//     //length of ray from current position to next x or y-side
//     double sideDistX;
//     double sideDistY;

//     //length of ray from one x or y-side to next x or y-side
//     double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//     double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//     double perpWallDist;

//     //what direction to step in x or y-direction (either +1 or -1)
//     int stepX;
//     int stepY;

//     int hit = 0; //was there a wall hit?
//     int side; //was a NS or a EW wall hit?

//     //calculate step and initial sideDist
//     double posX = game->player.pos_x / TILE_SIZE;
//     double posY = game->player.pos_y / TILE_SIZE;

//     if (rayDirX < 0)
//     {
//         stepX = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//     }
//     else
//     {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//     }
//     if (rayDirY < 0)
//     {
//         stepY = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//     }
//     else
//     {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//     }

//     //perform DDA
//     while (hit == 0)
//     {
//         //jump to next map square, either in x-direction, or in y-direction
//         if (sideDistX < sideDistY)
//         {
//             sideDistX += deltaDistX;
//             mapX += stepX;
//             side = 0;
//         }
//         else
//         {
//             sideDistY += deltaDistY;
//             mapY += stepY;
//             side = 1;
//         }
//         //Check if ray has hit a wall
// 		if (mapX < 0 || mapY < 0 || mapY >= game->map.height ||
// 			mapX >= game->map.width || game->map.grid[mapY][mapX] == '1')
// 			hit = 1;
//     }

//     //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
//     if(side == 0)
//         perpWallDist = (sideDistX - deltaDistX);
//     else
// 	{
//         perpWallDist = (sideDistY - deltaDistY);
// 	}
// 	if (perpWallDist <= 0.001)
// 		perpWallDist = 0.001;
//     // Calculate wallX (où exactement le rayon touche le mur)
//     double wallX;
//     if (side == 0)
//         wallX = posY + perpWallDist * rayDirY;
//     else
//         wallX = posX + perpWallDist * rayDirX;
//     wallX -= floor(wallX);  // Garde seulement la partie décimale

// 	// Déterminer la texture selon la direction du mur touché
// 	int texNum;
// 	if (side == 0) // Mur vertical (Nord/Sud)
// 	{
// 		if (rayDirX > 0)
// 			texNum = 2; // East (on regarde vers l'est, mur est à l'est)
// 		else
// 			texNum = 3; // West (on regarde vers l'ouest, mur est à l'ouest)
// 	}
// 	else // Mur horizontal (Est/Ouest)
// 	{
// 		if (rayDirY > 0)
// 			texNum = 1; // South (on regarde vers le sud, mur est au sud)
// 		else
// 			texNum = 0; // North (on regarde vers le nord, mur est au nord)
// 	}
//     int texX = (int)(wallX * game->config.textures[texNum].width);
//     // Ajuster texX selon direction pour éviter les miroirs
//     if (side == 0 && rayDirX > 0)
//         texX = game->config.textures[texNum].width - texX - 1;
//     if (side == 1 && rayDirY < 0)
//         texX = game->config.textures[texNum].width - texX - 1;

//     //Calculate height of line to draw on screen
//     int lineHeight = (int)(HEIGHT / perpWallDist);

//     //calculate lowest and highest pixel to fill in current stripe
//     int drawStart = -lineHeight / 2 + HEIGHT / 2;
//     if(drawStart < 0)
// 		drawStart = 0;
//     int drawEnd = lineHeight / 2 + HEIGHT / 2;
//     if(drawEnd >= HEIGHT)
// 		drawEnd = HEIGHT - 1;

// 	// Calcul du pas de texture (step) et position de départ
// 	double step = 1.0 * game->config.textures[texNum].height / lineHeight;
// 	double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

// 	for(int y = drawStart; y < drawEnd; y++)
// 	{
// 		// Cast de la coordonnée de texture en entier
// 		int texY = (int)texPos;
// 		if (texY >= game->config.textures[texNum].height)
// 			texY = game->config.textures[texNum].height - 1;
// 		if (texY < 0)
// 			texY = 0;
// 		texPos += step;

// 		// Récupérer la couleur du pixel de texture
// 		int color = get_texture_pixel(game, texNum ,texX, texY);

// 		// Assombrir les côtés Y pour l'effet d'éclairage
// 		if(side == 1)
// 			color = (color >> 1) & 8355711; // Divise RGB par 2

// 		put_pixel(game, x, y, color);
// 	}
// 	for (int y = 0; y < drawStart; y++)
// 		put_pixel(game, x, y, game->config.ceiling_color);
// 	for (int y = drawEnd; y < HEIGHT; y++)
// 		put_pixel(game, x, y, game->config.floor_color);
// }
