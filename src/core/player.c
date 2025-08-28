#include "../../includes/cub3d.h"

// Trouve la position de depart du joueur dans la map
static	t_start_pos	find_player_position(t_game *game)
{
	t_start_pos	start;
	int			x;
	int			y;

	start.x = -1;
	start.y = -1;
	start.dir = NORTH;
	y = 0;
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (x < game->map.width && game->map.grid[y][x])
		{
			if (is_direction_char(game->map.grid[y][x]))
				return (init_start_pos(game, x, y));
			x++;
		}
		y++;
	}
	return (start);
}

// Initialise la direction du joueur selon l'enum t_direction
static void	set_player_direction(t_player *player, t_direction dir)
{
	if (dir == NORTH)
	{
		player->dirX = 0.0;
		player->dirY = -1.0;
	}
	else if (dir == SOUTH)
	{
		player->dirX = 0.0;
		player->dirY = 1.0;
	}
	else if (dir == EAST)
	{
		player->dirX = 1.0;
		player->dirY = 0.0;
	}
	else if (dir == WEST)
	{
		player->dirX = -1.0;
		player->dirY = 0.0;
	}
}

// Initialise le plan de camera perpendiculaire a la direction
static void	set_camera_plane(t_player *player, t_direction dir)
{
	if (dir == NORTH)
	{
		player->planeX = -0.66;
		player->planeY = 0.0;
	}
	else if (dir == SOUTH)
	{
		player->planeX = 0.66;
		player->planeY = 0.0;
	}
	else if (dir == EAST)
	{
		player->planeX = 0.0;
		player->planeY = -0.66;
	}
	else if (dir == WEST)
	{
		player->planeX = 0.0;
		player->planeY = 0.66;
	}
}

// Initialise les flags a faux
static void	init_movement_flags(t_player *player)
{
	player->move_down = false;
	player->move_up = false;
	player->move_left = false;
	player->move_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}

// Initialise le joueur avec sa position de depart et ses param
void	init_player(t_player *player, t_game *game)
{
	t_start_pos	start;

	start = find_player_position(game);
	set_player_position(player, start);
	set_player_direction(player, start.dir);
	set_camera_plane(player, start.dir);
	init_movement_flags(player);
}
