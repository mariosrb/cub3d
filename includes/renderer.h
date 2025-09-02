#ifndef RENDERER_H
# define RENDERER_H

typedef struct s_game t_game;

void	cast_dda_ray(t_game *game, t_ray_dir ray_dir, int x);
int		draw_loop(void *param);
void	draw_map(t_game *game);

/**
 * @brief Réinitialise l'image en remplissant le buffer de 0 (noir).
 *
 * @param game Structure principale du jeu contenant le buffer d'image.
 */
void	clear_image(t_game *game);
int		create_rgb(int r, int g, int b);
void	draw_minimap(t_game *game);

/**
 * @brief Initialise les variables de pos en convertissant la pos du joueur en pixels
 * vers les coordonnes de la grille de la carte
 *
 * @param ray Structure a initialser contenant les donnees du rayon a calculer
 * @param game Structure principale du jeu
 * @param ray_dirx Direction X du rayon
 * @param ray_diry Direction Y du rayon
 */
void	init_ray_data(t_ray_data *r, t_game *g, t_ray_dir ray_dir);

/**
 * @brief Calcule la direction (step) et les distances initiale aux premeirs murs
 *
 * @param r Structure contenant les données du rayon
 * @param g Structure principale du jeu contenant notamment la position du joueur.
 * @param ray_dirx Composante X de la direction du rayon.
 * @param ray_diry Composante Y de la direction du rayon.
 */
void	step_and_side(t_ray_data *r, t_game *g, t_ray_dir ray_dir);

/**
 * @brief Exécute l'algorithme DDA (Digital Differential Analyzer)
 * pour détecter la première collision du rayon avec un mur.
 *
 * Cette fonction incrémente progressivement les coordonnées de la grille
 * (map_x, map_y) en fonction des distances et des pas calculés.
 * À chaque étape, elle détermine si le rayon a touché un mur ou
 * est sorti des limites de la carte.
 *
 * @param ray Structure contenant les données du rayon
 * @param game Structure principale du jeu contenant notamment la pos du joueur.
 */
void	perform_dda(t_ray_data *ray, t_game *game);

/**
 * @brief Calcule la distance perpendiculaire au mur et la position exacte
 * de l'impact du rayon sur le mur.
 *
 * Cette fonction utilise les distances calculées par l'algorithme DDA
 * pour déterminer la distance entre le joueur et le mur touché par le rayon.
 * Elle calcule également la position exacte (fractionnelle) sur le mur
 * où le rayon frappe, utile pour le texturing.
 *
 * @param ray Structure contenant les données du rayon
 * @param game Structure principale du jeu contenant notamment la pos du joueur.
 * @param r_dirx Direction X du rayon.
 * @param r_diry Direction Y du rayon.
 */
void	wall_dist_pos(t_ray_data *r, t_game *g, t_ray_dir ray_dir);

/**
 * @brief Calcule les données nécessaires pour texturer une colonne de mur.
 *
 * Cette fonction détermine :
 *   - quel mur (texture) afficher selon la face touchée et la direction du rayon,
 *   - la position horizontale dans la texture (tex_x),
 *   - la hauteur de la ligne à dessiner à l'écran (line_height),
 *   - les positions de début et de fin de dessin vertical (draw_start, draw_end),
 *   - le pas et la position initiale pour parcourir la texture verticalement.
 *
 * @param t Pointeur vers la structure contenant les informations de texturing à remplir.
 * @param r Pointeur vers la structure du rayon contenant les informations de collision.
 * @param g Pointeur vers la structure principale du jeu, nécessaire pour accéder aux textures.
 * @param r_dir  Structure contenant les composantes x et y de la direction du rayon.
 */
void	cal_text_data(t_text_data *t, t_ray_data *r, t_game *g, t_ray_dir r_dir);

#endif
