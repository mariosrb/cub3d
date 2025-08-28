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

typedef struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*east_texture;
	char	*west_texture;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
}	t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	rgb;
}	t_color;

#endif
