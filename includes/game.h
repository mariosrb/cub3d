#ifndef GAME_H
# define GAME_H

# define WIDTH 1280
# define HEIGHT 720

# define RED     0x00FF0000
# define GREEN   0x0000FF00
# define BLUE    0x000000FF
# define WHITE   0x00FFFFFF
# define BLACK   0x00000000

# define W 119
# define A 97
# define S 115
# define D 100

# define PI 3.14159265359

#include "../lib/minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

typedef struct s_player
{
	float	pos_x;
	float	pos_y;

	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
}	t_player;

typedef struct s_game
{
	t_player	player;
	void	*mlx;
	void	*win;
	void	*img;

	char	*data;
	int 	bpp;
	int 	size_line;
	int 	endian;
}	t_game;

typedef struct s_rect
{
	int	size;
	int	color;
}	t_rect;

void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, int size, int color);
void	init_game(t_game *g);
void	init_player(t_player *player);
int		update_player_press(int keycode, t_player *player);
int		update_player_release(int keycode, t_player *player);
void	player_move(t_player *player);

#endif
