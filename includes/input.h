#ifndef INPUT_H
# define INPUT_H

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define DEBUG 0

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
void player_move(t_player *player, t_game *game);

/**
 * @brief Ferme proprement le programme en libérant toutes les ressources allouées.
 *
 * Cette fonction détruit les textures, l'image principale, la fenêtre,
 * libère la mémoire de la carte, puis termine le processus.
 *
 * @param game Structure principale du jeu contenant les ressources à libérer.
 * @return Toujours 0 (même si la fonction appelle exit(0)).
 */
int		close_program(t_game *game);

/**
 * @brief Gère la fermeture de la fenêtre via le bouton de fermeture (croix rouge).
 *
 * @param game Structure principale du jeu contenant les ressources à libérer.
 * @return Toujours 0.
 */
int	handle_close_button(t_game *game);

/**
 * @brief Gère l'événement d'appui sur une touche du clavier.
 *
 * Si la touche appuyée est la touche Échap (ESC), le programme se ferme.
 * Sinon, la fonction met à jour l'état des touches du joueur.
 *
 * @param keycode Code de la touche pressée.
 * @param game Structure principale du jeu.
 * @return Toujours 0.
 */
int	handle_keypress(int keycode, t_game *game);

/**
 * @brief Gère l'événement de relâchement d'une touche du clavier.
 *
 * Met à jour l'état des touches du joueur pour signaler qu'une touche
 * n'est plus active.
 *
 * @param keycode Code de la touche relâchée.
 * @param game Structure principale du jeu.
 * @return Toujours 0.
 */
int	handle_keyrelease(int keycode, t_game *game);

void		player_move_bonus(t_player *player, t_game *game);
void		player_move_strafe(t_player *player, t_game *game);
bool		is_direction_char(char c);
t_direction	char_to_direction(char c);
t_start_pos	init_start_pos(t_game *game, int x, int y);
void		set_player_position(t_player *player, t_start_pos start);
bool		is_touching(float px, float py, t_game *game);

#endif
