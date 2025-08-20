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
/*                            PARSER INTERFACE                               */
/* ************************************************************************** */

/**
 * @brief Parse the entire .cub file
 * @param filename Path to the .cub file
 * @param game Game structure to populate
 * @return Error code (SUCCESS or error type)
 */
t_error_code	parser_parse_file(const char *filename, t_game *game);

/**
 * @brief Parse configuration elements (textures and colors)
 * @param line Current line being parsed
 * @param config Configuration structure to populate
 * @return Error code
 */
t_error_code	parser_parse_config_line(char *line, t_config *config);

/**
 * @brief Parse map data
 * @param lines Array of map lines
 * @param map Map structure to populate
 * @param player Player structure to populate with starting position
 * @return Error code
 */
t_error_code	parser_parse_map(char **lines, t_map *map, t_player *player);

/**
 * @brief Validate parsed configuration
 * @param config Configuration to validate
 * @return Error code
 */
t_error_code	parser_validate_config(t_config *config);

/**
 * @brief Validate parsed map
 * @param map Map to validate
 * @return Error code
 */
t_error_code	parser_validate_map(t_map *map);

/**
 * @brief Parse RGB color string "R,G,B"
 * @param color_str String containing RGB values
 * @param color Color structure to populate
 * @return Error code
 */
t_error_code	parser_parse_color(char *color_str, t_color *color);

/**
 * @brief Check if file has valid extension
 * @param filename File to check
 * @return true if valid, false otherwise
 */
bool 			parser_is_valid_extension(const char *filename);

/**
 * @brief Free parser resources
 * @param lines Array of strings to free
 */
void			parser_free_lines(char **lines);

/**
 * @brief Read all lines from a .cub file into memory
 * @param filename Path to the file to read
 * @return Array of strings (lines) terminated by NULL, or NULL on error
 * @note Boucle twice, first to calculate second to allocate
 * @note Uses get_next_line() internally to read line by line
 */
char			**parser_read_file_lines(const char *filename);

#endif
