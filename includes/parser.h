/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_parser.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <username@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/XX/XX XX:XX:XX by username         #+#    #+#             */
/*   Updated: 2024/XX/XX XX:XX:XX by username        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

/* ************************************************************************** */
/*                            PARSER MAIN	                                  */
/* ************************************************************************** */

/**
 * @brief init the variables to NULL/0/-1
 * @param final_map final variable containing the map
 * @param map first map
 * @param config variable containing the config info
 * @return nothing
 */
void	init_parser(char ***map, t_config *config, t_map *final_map);

/**
 * @brief main parsing function, regroups all the error check/map allocation
 * @param filename Path to the .cub file
 * @param config variable with all the config info
 * @param final_map map to allocate and fill
 * @return 0 if success, or other if error
 */
int		parser_main(const char *filename, t_config *config, t_map *final_map);

/**
 * @brief allocate the map and fill it with the lines
 * @param filename Path to the .cub file
 * @param line_count number of lines to allocate
 * @return the map full of lines
 */
char	**parser_second_step_read(const char *filename, int line_count);

/**
 * @brief Reads the .cub file
 * @param filename Path to the .cub file
 * @return The lines of the file to put in the map
 */
char	**parser_read_file_lines(const char *filename);

/* ************************************************************************** */
/*                            PARSER UTILS                                    */
/* ************************************************************************** */

/**
 * @brief Checks if the file has .cub extension
 * @param filename Path to the file to check
 * @return true(1) or false(0)
 */
bool	parser_is_valid_extension(const char *filename);

/**
 * @brief prints a char **
 * @param strs tab to print
 * @return nothing
 */
void	print_strs(char **strs);

/**
 * @brief removes the unecessary newline at the end of each lines
 * @param str the line to process
 * @return nothing
 */
void	remove_nline(char *str);

/* ************************************************************************** */
/*                            CONFIG                                          */
/* ************************************************************************** */

/**
 * @brief main function to get the configuration info
 * @param map the original file with the config + map
 * @param config the var to fill with the config info
 * @return ERROR or SUCCESS
 */
int		check_config(char **map, t_config *config);

/**
 * @brief get the config info out of the line
 * @param line the line to analyse
 * @param config the var to fill with the config info
 * @return ERROR or SUCCESS
 */
int		get_config(char *line, t_config *config);

/**
 * @brief function to get the texture (EA, WE, NO, SO)
 * @param line the line to analyse
 * @param config the var to fill with the config info
 * @return ERROR or SUCCESS
 */
int		get_texture(char *line, t_config *config);

/**
 * @brief function to get the colors config (F, C)
 * @param line the line to analyse
 * @param config the var to fill with the config info
 * @return ERROR or SUCCESS
 */
int		get_colors(char *line, t_config *config);

/* ************************************************************************** */
/*                             CONFIG COLORS                                  */
/* ************************************************************************** */

/**
 * @brief check if there is the proper syntax for color info (= 123,255,111)
 * @param line the line to analyse
 * @return ERROR or SUCCESS
 */
int		check_colors_syntax(char *line);

/**
 * @brief check if its a color config line (F or C)
 * @param line the line to analyse
 * @return true or false
 */
bool	is_color_param(char *line);

/**
 * @brief find the index where the info starts
 * @param line the line to analyse
 * @return the index of the character at which the info starts
 */
int		skip_id_color(char *line);

/**
 * @brief assign each number to its value
 * @param line the line to analyse
 * @param rgb the valued to fill
 * @return nothing
 */
void	assign_rgb(char *line, int *r, int *g, int *b);

/**
 * @brief checks if the rgb values are correct (between 0-255)
 * @param config the values to check
 * @return ERROR or SUCCESS
 */
int		check_rgb(t_config *config);

/* ************************************************************************** */
/*                             CONFIG TEXTURES                                */
/* ************************************************************************** */

/**
 * @brief check if its a texture config line (F or C)
 * @param line line to check
 * @return true(1) or false(0)
 */
bool	is_texture_param(char *line);

/**
 * @brief find the index where the info starts
 * @param line the line to analyse
 * @return the index of the character at which the info starts
 */
int		skip_id(char *line);

/**
 * @brief check if all texture config has been filled, otherwise error
 * @param config the config info to check
 * @return ERROR or SUCCESS
 */
int		check_full_textures(t_config *config);

/**
 * @brief same as strdup but stops at spaces
 * @param s1 string
 * @return the malloced char *
 */
char	*ft_strdup_space(const char *s1);

/**
 * @brief same as strlen but stops at spaces
 * @param str string
 * @return the length
 */
size_t	ft_strlen_space(const char *str);

/* ************************************************************************** */
/*                            CONFIG UTILS                                    */
/* ************************************************************************** */

/**
 * @brief checks if the first word in 2 strings are the same
 * @param str1 string you want to check
 * @param str2 word you want to compare it to
 * @return true(1) or false(0)
 */
bool	is_same_word(char *str1, char *str2);

/**
 * @brief checks the character is a space or tab
 * @param c char to check
 * @return true(1) or false(0)
 */
bool	is_space(char c);

/**
 * @brief checks if the line has config info
 * @param line line to check
 * @return true(1) or false(0)
 */
bool	is_config_param(char *line);

/**
 * @brief checks if the line is an empty line (spaces or newline)
 * @brief or if its some map content
 * @param line line of the file to check
 * @return true if there are characters, false if there is an 'empty' line
 */
bool	is_map(char *line);

/* ************************************************************************** */
/*                            MAP                                             */
/* ************************************************************************** */

/**
 * @brief main function to get the new and final map
 * @param old_map the old map
 * @param new_map the new map
 * @return ERROR or SUCCES
 */
int		get_map(char **old_map, t_map *new_map);

/**
 * @brief function to copy the old map into the new one
 * @param old_map the old map
 * @param new_map the new map
 * @return ERROR or SUCCES
 */
int		copy_map(char **old_map, t_map *new_map);

/**
 * @brief fill the correct empty spaces with 1s
 * @param new_map the map
 * @return ERROR or SUCCES
 */
int		fill_map(t_map *new_map);

/**
 * @brief check if map is surrounded by walls
 * @param map the map
 * @return 1 if error, 0 if not
 */
int		valid_walls(t_map *map);

/**
 * @brief check if map has valid characters
 * @param map the map
 * @return 1 if error, 0 if not
 */
int		valid_characters(t_map *map);

/* ************************************************************************** */
/*                            MAP UTILS                                      */
/* ************************************************************************** */

/**
 * @brief get the first line of the map
 * @param old_map the old map
 * @return the index of the start of the map
 */
int		get_start_line(char **old_map);

/**
 * @brief count the dimensions of the map
 * @param old_map the old map to count the dimensions of
 * @param new_map the new map to fill with the dimensions
 * @return nothing
 */
void	count_dimensions(char **old_map, t_map *new_map);

/**
 * @brief checks if the current space character should be filled with a 1 or not
 * @param map the map
 * @param pos1 map[here][]
 * @param pos2 map[][here]
 * @return true(1) if its a fillable space, or false(0) if not
 */
bool	is_fillable_space(t_map *map, int pos1, int pos2);

/**
 * @brief checks if this adjacent character is the right one or not
 * @param map the map
 * @param pos1 map[here][]
 * @param pos2 map[][here]
 * @return true(1) if its a good character, or false(0) if not
 */
bool	is_next_fill(t_map *map, int pos1, int pos2);

/**
 * @brief same as strdup but adds spaces until len reached
 * @param s1 string
 * @return the malloced char *
 */
char	*ft_strdup_fill(const char *s1, int len);

/**
 * @brief check on the current line of the map if walls are properly placed
 * @param str current line of the map
 * @param i index of the current character
 * @param height height of the map
 * @param width width of the map
 * @return 1 if error, 0 if not
 */
int		valid_line(char *str, int i, int height, int width);

/**
 * @brief check that the current character is allowed on the map
 * @param c current character
 * @return 1 if error, 0 if not
 */
int		ok_char(char c);

/**
 * @brief check if there is at least one '0' in the map
 * @param map the map
 * @return true(1) if theres a 0, or false(0) if not
 */
bool	check_zero(char **map);

/* ************************************************************************** */
/*                            ERRORS                                          */
/* ************************************************************************** */

/**
 * @brief function to call when an error has occured during the parsing
 * @param er_code the last error code
 * @param config the config data to free
 * @param map the map data to free
 * @return 1
 */
int		return_error_parsing(t_config *config, t_map *map, int er_code);

/**
 * @brief prints an error message depending on the error code
 * @param er_code the error code
 * @return 1
 */
int		print_error(int er_code);

/**
 * @brief free the allocated lines of the map (frees any char **)
 * @param lines lines to free
 * @return nothing
 */
void	parser_free_lines(char **lines);

/**
 * @brief frees all the variables of the parsing
 * @param config config data to free
 * @param map map data to free
 * @return nothing
 */
void	parser_free_all(t_config *config, t_map *map);

#endif
