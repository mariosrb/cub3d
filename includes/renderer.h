/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:29:23 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 15:50:42 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

typedef struct s_game	t_game;

/**
 * @brief Boucle principale de rendu du jeu (appelée à chaque frame).
 *
 * Cette fonction gère :
 * - le nettoyage de l’image précédente,
 * - le mouvement du joueur (bonus et strafe),
 * - l’affichage en mode DEBUG de la position du joueur et de la carte,
 * - le raycasting pour chaque colonne de l’écran via `cast_dda_ray`,
 * - l’affichage de la mini-map,
 * - et enfin le rendu de l’image complète dans la fenêtre.
 *
 * @param param Pointeur vers la structure `t_game` (casté depuis void* par mlx).
 * @return Toujours 0 (convention pour la boucle d’affichage MLX).
 */
int		draw_loop(void *param);

/**
 * @brief Dessine la carte en affichant les murs sous forme de carrés.
 *
 * Cette fonction parcourt la grille de la carte. Pour chaque case contenant '1'
 * (mur), elle calcule les coordonnées du carré correspondant dans l’espace
 * graphique et l’affiche avec la couleur définie (ici BLUE).
 *
 * @param game Structure principale du jeu contenant la carte et ses dimensions.
 */
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
 * @brief Initialise les variables de pos en convertissant la pos du
 * joueur en pixels
 * vers les coordonnes de la grille de la carte
 *
 * @param ray Structure a initialser contenant les donnees du rayon a
 * calculer
 * @param game Structure principale du jeu
 * @param ray_dirx Direction X du rayon
 * @param ray_diry Direction Y du rayon
 */
void	init_ray_data(t_ray_data *r, t_game *g, t_ray_dir ray_dir);

/**
 * @brief Calcule la direction (step) et les distances initiale aux
 * premeirs murs
 *
 * @param r Structure contenant les données du rayon
 * @param g Structure principale du jeu contenant notamment la position
 * du joueur.
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
 * @param game Structure principale du jeu contenant notamment la pos
 * du joueur.
 */
void	perform_dda(t_ray_data *ray, t_game *game);

/**
 * @brief Calcule la distance perpendiculaire au mur et la position exacte
 * de l'impact du rayon sur le mur.
 *
 * Cette fonction utilise les distances calculées par l'algorithme DDA
 * pour déterminer la distance entre le joueur et le mur touché par
 * le rayon.
 * Elle calcule également la position exacte (fractionnelle) sur le mur
 * où le rayon frappe, utile pour le texturing.
 *
 * @param ray Structure contenant les données du rayon
 * @param game Structure principale du jeu contenant notamment la pos
 * du joueur.
 * @param r_dirx Direction X du rayon.
 * @param r_diry Direction Y du rayon.
 */
void	wall_dist_pos(t_ray_data *r, t_game *g, t_ray_dir ray_dir);

/**
 * @brief Calcule les données nécessaires pour texturer une colonne de mur.
 *
 * Cette fonction détermine :
 *   - quel mur (texture) afficher selon la face touchée et la direction
 * du rayon,
 *   - la position horizontale dans la texture (tex_x),
 *   - la hauteur de la ligne à dessiner à l'écran (line_height),
 *   - les positions de début et de fin de dessin vertical (draw_start,
 * draw_end),
 *   - le pas et la position initiale pour parcourir la texture
 * verticalement.
 *
 * @param t Pointeur vers la structure contenant les informations de
 * texturing à remplir.
 * @param r Pointeur vers la structure du rayon contenant les informations
 *  de collision.
 * @param g Pointeur vers la structure principale du jeu, nécessaire pour
 * accéder aux textures.
 * @param r_dir  Structure contenant les composantes x et y de la direction
 *  du rayon.
 */
void	cal_txt_dta(t_text_data *t, t_ray_data *r, t_game *g, t_ray_dir r_dir);

/**
 * @brief Dessine une portion verticale de mur (slice) sur l'écran à partir
 *  de la texture.
 *
 * Prend les données calculées par le raycasting (hauteur du mur,
 * coordonnées dans la texture, position de départ et fin à l'écran), puis
 * parcourt
 * chaque pixel vertical pour le remplir avec la couleur correspondante
 * extraite de
 * la texture. Les murs verticaux (side == 1) sont assombris pour créer
 * un effet
 * de profondeur.
 *
 * @param game Structure principale contenant les données du jeu et les
 * textures.
 * @param t Structure contenant les informations de texturing (coordonnées,
 * hauteur, etc.).
 * @param ray Données du rayon courant (utilisé pour déterminer le côté du
 * mur).
 * @param x Position horizontale sur l'écran (colonne) où dessiner la ligne
 *
 * verticale.
 */
void	draw_wall(t_game *game, t_text_data *t, t_ray_data *ray, int x);

/**
 * @brief Dessine le plafond et le sol pour une colonne donnée de l'écran.
 *
 * Cette fonction remplit les pixels situés au-dessus du mur détecté avec
 * la couleur
 * du plafond, puis les pixels situés en dessous du mur avec la couleur du
 *  sol.
 * Les coordonnées verticales de début et de fin du mur sont contenues dans
 * la structure de texturing.
 *
 * @param game Structure principale contenant les données du jeu et les
 *  couleurs.
 * @param tex Données de texturing contenant draw_start et draw_end
 * (limites du mur).
 * @param x Position horizontale de la colonne à dessiner sur l'écran.
 */
void	draw_ceiling_and_floor(t_game *game, t_text_data *tex, int x);

/**
 * @brief Lance un rayon avec l'algorithme DDA et
 * dessine la colonne correspondante.
 *
 * Cette fonction initialise les données du rayon, calcule les
 * étapes et distances
 * pour l'algorithme DDA, effectue le parcours de la grille
 * jusqu'à une collision,
 * calcule la distance perpendiculaire au mur, détermine
 * les coordonnées de texture,
 * puis dessine le mur ainsi que le plafond et le sol pour
 * une colonne donnée.
 *
 * @param game Structure principale contenant les données du jeu et la carte.
 * @param ray_dir Direction du rayon en coordonnées X et Y.
 * @param x Position horizontale de la colonne à dessiner sur l'écran.
 */
void	cast_dda_ray(t_game *game, t_ray_dir ray_dir, int x);

void	init_numbers(int *i, double *x, double *y, int *scale);

void	minimap_loop(t_game *game, t_square *sqr, t_minimap *map, int *scale);

void	draw_loop_while(int *x, double *camx, t_ray_dir *ray_dir, t_game *game);

#endif
