#include "../../includes/cub3d.h"

// Fonction qui met des pixels
void put_pixel(t_game *game, int x, int y, int color)
{
	int pixel;

	if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
		return;
	pixel = (y * game->size_line) + (x * (game->bpp / 8));
	game->data[pixel + 0] = (color) & 0xFF;
	game->data[pixel + 1] = (color >> 8) & 0xFF;
	game->data[pixel + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j <= size)
	{
		i = 0;
		while (i <= size)
		{
			if (i == 0 || i == size || j == 0 || j == size)
				put_pixel(game, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void clear_image(t_game *game)
{
	int i = 0;
	int total = WIDTH * HEIGHT * (game->bpp / 8);

	while (i < total)
	{
		game->data[i] = 0;
		i++;
	}
}

void	draw_map(t_game *game)
{
	char	**map;

	map = game->map;
	for(int i = 0; map[i]; i++)
		for(int j = 0; map[i][j]; j++)
			if(map[i][j] == '1')
				draw_square(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, BLUE, game);
}

char	**init_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);

	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100010000000001";
	map[3] = "100000000001001";
	map[4] = "100000100000001";
	map[5] = "100000100000001";
	map[6] = "100000100000001";
	map[7] = "100000100000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;

	return (map);
}

void init_game(t_game *g)
{
	init_player(&g->player);
	g->map = init_map();
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

bool	is_touching(float px, float py, t_game *game)
{
	int x = px / TILE_SIZE;
	int y = py / TILE_SIZE;

	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fishey_fix(t_game *game, float x2, float y2)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	dist_fix;

	delta_x = x2 - game->player.pos_x;
	delta_y = y2 - game->player.pos_y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	dist_fix = distance(delta_x, delta_y) * cos(angle);
	return (dist_fix);
}

void	draw_ray(t_player *player, t_game *game, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = player->pos_x;
	ray_y = player->pos_y;
	while (!is_touching(ray_x, ray_y, game))
	{
		if (DEBUG)
			put_pixel(game, ray_x, ray_y, RED);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!DEBUG)
	{
		float	dist = fishey_fix(game, ray_x, ray_y);
		float	height = (TILE_SIZE / dist) * (WIDTH / 2);
		int		start_y = (HEIGHT - height) / 2;
		int		end = start_y + height;
		while (start_y < end)
		{
			put_pixel(game, i, start_y, 225);
			start_y++;
		}
	}
}


int draw_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clear_image(game);
	player_move(&game->player);
	if (DEBUG)
	{
		draw_square(game->player.pos_x, game->player.pos_y, 25, GREEN, game);
		draw_map(game);
	}
	float	fraction = PI / 3 / WIDTH;
	float	start_x = game->player.angle - PI / 6;
	int		i = 0;
	while (i < WIDTH)
	{
		draw_ray(&game->player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int main(void)
{
	t_game game;

	init_game(&game);

	mlx_hook(game.win, 2, 1L << 0, update_player_press, &game.player);
	mlx_hook(game.win, 3, 1L << 1, update_player_release, &game.player);

	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	return (0);
}
