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

/**
 * @brief Place un pixel de couleur dans l'image à la position (x, y).
 *
 * @param game Structure principale du jeu contenant les informations de l'image.
 * @param x Coordonnée X du pixel.
 * @param y Coordonnée Y du pixel.
 * @param color Couleur du pixel (format 0xRRGGBB).
 */
void	put_pixel(t_game *game, int x, int y, int color);

/**
 * @brief Dessine un carré creux de taille donnée à la position du joueur.
 *
 * @param game Structure principale du jeu contenant les informations de rendu.
 * @param size Taille du carré en pixels.
 * @param color Couleur des bords du carré (format 0xRRGGBB).
 */
void	draw_square(t_game *game, int size, int color);

/**
 * @brief Réinitialise l'image en remplissant le buffer de 0 (noir).
 *
 * @param game Structure principale du jeu contenant le buffer d'image.
 */
void	clear_image(t_game *game);

/**
 * @brief Initialise le jeu : joueur, MLX, fenêtre et image.
 *
 * @param g Pointeur vers la structure principale du jeu.
 */
void	init_game(t_game *g);

/**
 * @brief Initialise la structure du joueur avec ses paramètres par défaut.
 *
 * @param player Pointeur vers la structure joueur à initialiser.
 */
void	init_player(t_player *player);

#endif
