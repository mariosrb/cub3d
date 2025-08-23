#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

/* ************************************************************************** */
/*                                 ENUMS                                      */
/* ************************************************************************** */

typedef enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
}	t_direction;

typedef enum e_error_code
{
	SUCCESS = 0,
	ERROR_ARGS = 1,
	ERROR_FILE = 2,
	ERROR_MEMORY = 3,
	ERROR_CONFIG = 4,
	ERROR_MAP = 5,
	ERROR_MLX = 6
}	t_error_code;

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

typedef	struct s_textures
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_lenght;
	int			endian;
}	t_texture;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}	t_map;

typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	int			floor_r;
	int			floor_g;
	int			floor_b;
	int			ceiling_r;
	int			ceiling_g;
	int			ceiling_b;
	t_texture	textures[4];
}	t_config;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;

	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;

	bool	move_up;
	bool	move_down;
	bool	move_left;
	bool	move_right;
	bool	rotate_left;
	bool	rotate_right;
}	t_player;

typedef struct s_game
{
	t_config	config;
	t_map		mapp;
	t_player	player;
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int 		bpp;
	int 		size_line;
	int 		endian;

	char		**map;
	
	// UNE SEULE TEXTURE pour commencer
	void		*texture;        // Une seule image MLX
	char		*tex_data;       // Pointeur vers data texture
	int			tex_width;       // Largeur texture
	int			tex_height;      // Hauteur texture
	int			tex_bpp;         // Bits per pixel
	int			tex_line_len;    // Line length
	int			tex_endian;      // Endian
}	t_game;

typedef struct s_square
{
	int			x;
	int			y;
	int			size;
	int			color;
}	t_square;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			rgb;
}	t_color;

#endif
