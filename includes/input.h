#ifndef INPUT_H
# define INPUT_H

typedef struct s_player t_player;

/**
 * @brief Met à jour l'état du joueur lorsqu'une touche est pressée
 *
 * @param keycode Code de la touche pressée
 * @param player Pointeur vers la structure du joueur
 * @return int Toujours 0
 */
int		update_player_press(int keycode, t_player *player);

/**
 * @brief Met à jour l'état du joueur lorsqu'une touche est relâchée
 *
 * @param keycode Code de la touche relâchée
 * @param player Pointeur vers la structure du joueur
 * @return int Toujours 0
 */
int		update_player_release(int keycode, t_player *player);

/**
 * @brief Déplace le joueur selon son état actuel (touches pressées)
 *
 * @param player Pointeur vers la structure du joueur
 */
void	player_move(t_player *player);

#endif
