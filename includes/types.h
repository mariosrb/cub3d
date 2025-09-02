/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:29:44 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/09/02 16:16:20 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	SUCCESS,
	ERROR_ARGS,
	ERROR_FILE,
	ERROR_MEMORY,
	ERROR_CONFIG,
	ERROR_MAP,
	ERROR_MLX,
	ERROR_EXTENSION,
	ERROR_WALLS,
	ERROR_CHARACTERS
}	t_error_code;

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

typedef struct s_textures
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
}	t_texture;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
}	t_map;

typedef struct s_config
{
	char			*north_texture;
	char			*south_texture;
	char			*east_texture;
	char			*west_texture;
	int				floor_r;
	int				floor_g;
	int				floor_b;
	int				ceiling_r;
	int				ceiling_g;
	int				ceiling_b;
	t_texture		textures[4];
	int				floor_color;
	int				ceiling_color;
}	t_config;

typedef struct s_player
{
	float			pos_x;
	float			pos_y;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	bool			move_up;
	bool			move_down;
	bool			move_left;
	bool			move_right;
	bool			rotate_left;
	bool			rotate_right;
}	t_player;

typedef struct s_game
{
	t_config		config;
	t_map			map;
	t_player		player;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}	t_game;

typedef struct s_square
{
	int				x;
	int				y;
	int				size;
	int				color;
}	t_square;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	int				rgb;
}	t_color;

// Stock les informations de depart du joueur
typedef struct s_start_pos
{
	int				x;
	int				y;
	t_direction		dir;
}	t_start_pos;

typedef struct s_ray_data
{
	int				map_x;
	int				map_y;
	double			side_distx;
	double			side_disty;
	double			delta_distx;
	double			delta_disty;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	double			wall_x;
}	t_ray_data;

typedef struct s_text_data
{
	int				tex_num;
	int				tex_x;
	int				tex_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			step;
	double			tex_pos;
}	t_text_data;

typedef struct s_ray_dir
{
	double			x;
	double			y;
}	t_ray_dir;

typedef struct s_minimap
{
	double			x;
	double			y;
	int				i;
}	t_minimap;

#endif
