/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:37 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/20 07:38:44 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Opens .cub file and parses metadata headers.
 *
 * Opens the file at the specified path and delegates header parsing to
 * parse_headers, which extracts texture paths and color definitions.
 *
 * @param path Path to .cub file.
 * @param cfg Configuration structure to populate.
 * @param fd Pointer to store file descriptor.
 * @param first_map_line Pointer to store first map line.
 * @return 0 on success, -1 on failure.
 */
static int	config_metadata(const char *path, t_config *cfg, int *fd,
		char **first_map_line)
{
	*first_map_line = NULL;
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (system_error(path));
	if (parse_headers(*fd, cfg, first_map_line) < 0)
		return (-1);
	return (0);
}

/**
 * @brief Collects and normalizes map data from file.
 *
 * Reads all map lines from the file descriptor, constructs the grid,
 * and normalizes it to ensure all rows have equal width.
 *
 * @param fd File descriptor.
 * @param first_map_line First line of map.
 * @param cfg Configuration structure to populate.
 * @return 0 on success, -1 on failure.
 */
static int	config_map(int fd, char *first_map_line, t_config *cfg)
{
	if (collect_map(fd, first_map_line, &cfg->map) < 0)
		return (-1);
	if (normalize_map(&cfg->map) < 0)
		return (-1);
	return (0);
}

/**
 * @brief Validates map characters, player position, and enclosure.
 *
 * Ensures all map characters are valid, locates the player, and verifies
 * that the map is properly enclosed by walls.
 *
 * @param cfg Configuration structure to validate.
 * @return 0 on success, -1 on failure.
 */
static int	validate_configutarions(t_config *cfg)
{
	if (validate_map_chars(&cfg->map) < 0)
		return (-1);
	if (locate_player(&cfg->map) < 0)
		return (-1);
	if (check_map_closed(&cfg->map) < 0)
		return (-1);
	return (0);
}

/**
 * @brief Parses a .cub configuration file.
 *
 * Opens the file, initializes the configuration structure, parses headers
 * and map, validates all components, and returns the populated config.
 *
 * @param path Path to .cub file.
 * @param cfg Configuration structure to populate.
 * @return 0 on success, -1 on failure.
 */
int	parse_cub(const char *path, t_config *cfg)
{
	int		fd;
	char	*first_line;

	if (config_metadata(path, cfg, &fd, &first_line) < 0)
	{
		parser_release_resources(fd, cfg);
		return (-1);
	}
	if (config_map(fd, first_line, cfg) < 0)
	{
		parser_release_resources(fd, cfg);
		return (-1);
	}
	if (validate_configutarions(cfg) < 0)
	{
		parser_release_resources(fd, cfg);
		return (-1);
	}
	parser_release_resources(fd, NULL);
	return (0);
}
