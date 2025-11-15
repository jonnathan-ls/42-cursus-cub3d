/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:28 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/15 20:03:43 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

/**
 * @brief Checks if a line contains only whitespace characters.
 *
 * Iterates through the string to determine if it consists entirely of
 * spaces, tabs, or a newline character.
 *
 * @param s String to check.
 * @return 1 if line is empty or whitespace-only, 0 otherwise.
 */
static int	is_empty_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		if (!(s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\v'
				|| s[i] == '\f'))
			return (0);
		i = i + 1;
	}
	return (1);
}

/**
 * @brief Fetches the first non-empty line that represents the map.
 *
 * Reads lines from the file descriptor, skipping empty lines, until a
 * non-empty line is found, which is returned as the first map line.
 *
 * @param fd File descriptor to read from.
 * @param out Pointer to store the first map line.
 * @return 0 on success, -1 on failure.
 */
static int	fetch_first_map_line(int fd, char **out)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (parser_error("empty map"));
		if (!is_empty_line(line))
		{
			*out = line;
			return (0);
		}
		free(line);
	}
	return (0);
}

/**
 * @brief Processes a single header line and updates configuration.
 *
 * Skips empty lines, parses header lines to extract texture paths or
 * colors. Returns -2 if the line is the start of the map.
 *
 * @param line Line to process.
 * @param cfg Configuration structure to update.
 * @param count Pointer to header count.
 * @return 0 on success, -1 on failure, -2 if map start detected.
 */
static int	process_header_line(char *line, t_config *cfg, int *count)
{
	int	parse_result;

	if (is_empty_line(line))
		return (0);
	parse_result = parse_header_line(line, cfg, count);
	if (parse_result == -2)
		return (-2);
	if (parse_result < 0)
		return (-1);
	return (0);
}

/**
 * @brief Reads and processes header lines until map section begins.
 *
 * Continues reading lines until 6 required headers are parsed or a map
 * line is detected. Returns the first map line for further processing.
 *
 * @param fd File descriptor to read from.
 * @param cfg Configuration structure to update.
 * @param first_map_line Pointer to store first map line.
 * @return 0 on success, -1 on failure.
 */
static int	read_header_block(int fd, t_config *cfg, char **first_map_line)
{
	char	*line;
	int		count;
	int		result;

	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		result = process_header_line(line, cfg, &count);
		if (result == -2)
		{
			free(line);
			return (0);
		}
		if (result < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (fetch_first_map_line(fd, first_map_line));
}

/**
 * @brief Parses configuration headers and locates first map line.
 *
 * Reads and validates all required texture paths and color definitions
 * from the file header section. Ensures all mandatory fields are present.
 *
 * @param fd File descriptor to read from.
 * @param cfg Configuration structure to populate.
 * @param line_after_headers Pointer to store first map line.
 * @return 0 on success, -1 on failure.
 */
int	parse_headers(int fd, t_config *cfg, char **line_after_headers)
{
	if (read_header_block(fd, cfg, line_after_headers) < 0)
		return (-1);
	if (!cfg->textures.no_path)
		return (parser_error("missing NO texture"));
	if (!cfg->textures.so_path)
		return (parser_error("missing SO texture"));
	if (!cfg->textures.we_path)
		return (parser_error("missing WE texture"));
	if (!cfg->textures.ea_path)
		return (parser_error("missing EA texture"));
	if (!cfg->floor_color_set)
		return (parser_error("missing F color"));
	if (!cfg->ceiling_color_set)
		return (parser_error("missing C color"));
	return (0);
}
