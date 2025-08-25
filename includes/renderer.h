#ifndef RENDERER_H
# define RENDERER_H

typedef struct s_game t_game;

void	cast_dda_ray(t_game *game, double rayDirX, double rayDirY, int x);
int		draw_loop(void *param);
void	draw_map(t_game *game);

/**
 * @brief Réinitialise l'image en remplissant le buffer de 0 (noir).
 *
 * @param game Structure principale du jeu contenant le buffer d'image.
 */
void	clear_image(t_game *game);
int		create_rgb(int r, int g, int b);

#endif
