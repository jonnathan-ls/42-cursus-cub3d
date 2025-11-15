/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/15 20:03:43 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

/**
 * @brief Releases resources allocated during parsing.
 *
 * Clears GNL storage, closes the file descriptor, and frees the
 * configuration structure if provided.
 *
 * @param fd File descriptor to close.
 * @param cfg Configuration structure to free.
 */
void	parser_release_resources(int fd, t_config *cfg)
{
	gnl_clear_storage();
	close(fd);
	if (cfg)
		free_config(cfg);
}

/**
 * @brief Initializes configuration structure with default values.
 *
 * Sets all texture paths to NULL, colors to -1, and map dimensions to
 * zero, preparing the structure for parsing.
 *
 * @param cfg Configuration structure to initialize.
 */
void	init_config_values(t_config *cfg)
{
	cfg->textures.no_path = NULL;
	cfg->textures.so_path = NULL;
	cfg->textures.we_path = NULL;
	cfg->textures.ea_path = NULL;
	cfg->textures.floor_path = NULL;
	cfg->textures.ceiling_path = NULL;
	cfg->textures.door_path = NULL;
	cfg->textures.menu_path = NULL;
	cfg->textures.start_path = NULL;
	cfg->textures.win_path = NULL;
	cfg->textures.lose_path = NULL;
	cfg->textures.sprites = NULL;
	cfg->textures.sprite_count = 0;
	cfg->floor_color.rgba = -1;
	cfg->ceiling_color.rgba = -1;
	cfg->floor_color_set = 0;
	cfg->ceiling_color_set = 0;
	cfg->map.grid = NULL;
	cfg->map.width = 0;
	cfg->map.height = 0;
	cfg->map.player_x = -1;
	cfg->map.player_y = -1;
	cfg->map.player_dir = 0;
}
