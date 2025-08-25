#include "../../includes/cub3d.h"

void	init_player(t_player *player)
{
	player->pos_x = WIDTH / 2;
	player->pos_y = HEIGHT / 2;
	player->dirX = -1.0;
	player->dirY = 0.0;
	player->planeX = 0.0;
	player->planeY = 0.66;
	player->move_down = false;
	player->move_up = false;
	player->move_left = false;
	player->move_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}

// // Verifie si le char correspond a une dir valide
// static bool	is_direction_char(char c)
// {
// 	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
// }

// // Convertir um caractere de direction en enum t_direction
// static t_direction	char_to_direction(char c)
// {
// 	if (c == 'N')
// 		return (NORTH);
// 	else if (c == 'S')
// 		return (SOUTH);
// 	else if (c == "W")
// 		return (WEST);
// 	else if (c == 'E')
// 		return (EAST);
// 	return (NORTH);
// }

// // Retourne la position que tu as trouve
// static t_start_pos	init_start_pos(t_game *game, int x, int y)
// {
// 	t_start_pos	start;

// 	start.x = x;
// 	start.y = y;
// 	start.dir = char_to_direction(game->mapp.grid[y][x]);
// 	game->mapp.grid[y][x] = '0';
// 	return (start);
// }

// // Trouve la position de depart du joueur dans la map
// static t_start_pos	find_player_position(t_game *game)
// {
// 	t_start_pos	start;
// 	int			x;
// 	int			y;

// 	start.x = -1;
// 	start.y = -1;
// 	start.dir = NORTH;
// 	y = 0;
// 	while (game->mapp.grid[y])
// 	{
// 		x = 0;
// 		while (game->mapp.grid[y][x])
// 		{
// 			if (is_direction_char(game->mapp.grid[y][x]))
// 				return (init_start_pos(game, x, y));
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (start);
// }

// // Initialise la position du joueur en pixels
// static void	set_player_position(t_player *player, t_start_pos start)
// {
// 	player->pos_x = start.x * TILE_SIZE + TILE_SIZE / 2;
// 	player->pos_y = start.y * TILE_SIZE + TILE_SIZE / 2;
// }

// // Initialise la direction du joueur selon l'enum t_direction
// static void	set_player_direction(t_player *player, t_direction dir)
// {
// 	if (dir == NORTH)
// 	{
// 		player->dirX = 0.0;
// 		player->dirY = -1.0;
// 	}
// 	else if (dir == SOUTH)
// 	{
// 		player->dirX = 0.0;
// 		player->dirY = 1.0;
// 	}
// 	else if (dir == EAST)
// 	{
// 		player->dirX = 1.0;
// 		player->dirY = 0.0;
// 	}
// 	else if (dir == WEST)
// 	{
// 		player->dirX = -1.0;
// 		player->dirY = 0.0;
// 	}
// }

// // Initialise le plan de camera perpendiculaire a la direction
// static void	set_camera_plane(t_player *player, t_direction dir)
// {
// 	if (dir == NORTH)
// 	{
// 		player->planeX = 0.66;
// 		player->planeY = 0.0;
// 	}
// 	else if (dir == SOUTH)
// 	{
// 		player->planeX = -0.66;
// 		player->planeY = 0.0;
// 	}
// 	else if (dir == EAST)
// 	{
// 		player->planeX = 0.0;
// 		player->planeY = 0.66;
// 	}
// 	else if (dir == WEST)
// 	{
// 		player->planeX = 0.0;
// 		player->planeY = -0.66;
// 	}
// }

// // Initialise les flags a faux
// static void	init_movement_flags(t_player *player)
// {
// 	player->move_down = false;
// 	player->move_up = false;
// 	player->move_left = false;
// 	player->move_right = false;
// 	player->rotate_left = false;
// 	player->rotate_right = false;
// }

// // Initialise le joueur avec sa position de depart et ses param
// void	init_player(t_player *player, t_game *game)
// {
// 	t_start_pos	start;

// 	start = find_player_position(game);
// 	set_player_position(player, start);
// 	set_player_direction(player, start.dir);
// 	set_camera_plane(player, start.dir);
// 	init_movement_flags(player);
// }
