#ifndef CONSTANTS_H
# define CONSTANTS_H

/* ************************************************************************** */
/*                               PARSING                                      */
/* ************************************************************************** */

# define FILE_EXTENSION		".cub"
# define MAX_LINE_LENGTH	1024
# define MAP_CHARS			"01NSEW "

/* ************************************************************************** */
/*                               KEYCODES                                     */
/* ************************************************************************** */

# define KEY_ESC			53
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_LEFT			123
# define KEY_RIGHT			124

/* ************************************************************************** */
/*                               MINIMAP                                      */
/* ************************************************************************** */

# define MINIMAP_SIZE		200
# define MINIMAP_SCALE		10
# define MINIMAP_MARGIN		20

/* ************************************************************************** */
/*                               ERRORS                                       */
/* ************************************************************************** */

# define ERROR_PREFIX		"Error\n"
# define ERR_ARGS			"Invalid arguments"
# define ERR_FILE_NOT_FOUND	"File not found"
# define ERR_INVALID_EXT	"Invalid file extension"
# define ERR_MALLOC			"Memory allocation failed"
# define ERR_MLX_INIT		"MLX initialization failed"
# define ERR_INVALID_MAP	"Invalid map"
# define ERR_INVALID_CONFIG	"Invalid configuration"

#endif
