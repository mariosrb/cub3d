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
	if (game->map.grid)
		free(game->map.grid);
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

int	update_player_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->move_up = false;
	if (keycode == S)
		player->move_down = false;
	if (keycode == D)
		player->move_right = false;
	if (keycode == A)
		player->move_left = false;
	if (keycode == LEFT)
		player->rotate_left = false;
	if (keycode == RIGHT)
		player->rotate_right = false;
	return (0);
}
