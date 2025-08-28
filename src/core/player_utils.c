#include "../../includes/cub3d.h"

// Verifie si le char correspond a une dir valide
bool	is_direction_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

// Convertir um caractere de direction en enum t_direction
t_direction	char_to_direction(char c)
{
	if (c == 'N')
		return (NORTH);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'W')
		return (WEST);
	else if (c == 'E')
		return (EAST);
	return (NORTH);
}

// Retourne la position que tu as trouve
t_start_pos	init_start_pos(t_game *game, int x, int y)
{
	t_start_pos	start;

	start.x = x;
	start.y = y;
	start.dir = char_to_direction(game->map.grid[y][x]);
	return (start);
}

// Initialise la position du joueur en pixels
void	set_player_position(t_player *player, t_start_pos start)
{
	player->pos_x = start.x * TILE_SIZE + TILE_SIZE / 2;
	player->pos_y = start.y * TILE_SIZE + TILE_SIZE / 2;
}
