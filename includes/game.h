#ifndef GAME_H
# define GAME_H

# define TILE_SIZE 64
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
# define LEFT 65361
# define RIGHT 65363
# define DEBUG 0

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_EAST 2
# define TEX_WEST 3

# define PI 3.14159265359

#include "../lib/minilibx-linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "types.h"

char	**init_map(void);
void	init_game(t_game *g);
int 	load_texture(t_game *game, char *path, int texture_index);
int		get_texture_pixel(t_game *game, int texture_index, int x, int y);

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
void	draw_square(t_square square, t_game *game);

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
