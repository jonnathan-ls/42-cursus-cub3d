/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_optional_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/09 23:16:44 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Parses optional texture identifiers (FT, CT, DR, MN, ST, WN, LS).
 *
 * Identifies and processes optional texture paths based on the two-character
 * identifier, delegating to parse_texture for actual path parsing.
 *
 * @param id Pointer to identifier string.
 * @param cfg Configuration structure to update.
 * @param rest Pointer to path string after identifier.
 * @return 0 on success, -1 on failure.
 */
int	handle_optional_texture(char *id, t_config *cfg, char *rest)
{
	if (id[0] == 'F' && id[1] == 'T')
		return (parse_single_texture(rest, &cfg->textures.floor_path, "FT"));
	if (id[0] == 'C' && id[1] == 'T')
		return (parse_single_texture(rest, &cfg->textures.ceiling_path, "CT"));
	if (id[0] == 'D' && id[1] == 'R')
		return (parse_single_texture(rest, &cfg->textures.door_path, "DR"));
	if (id[0] == 'M' && id[1] == 'N')
		return (parse_single_texture(rest, &cfg->textures.menu_path, "MN"));
	if (id[0] == 'S' && id[1] == 'T')
		return (parse_single_texture(rest, &cfg->textures.start_path, "ST"));
	if (id[0] == 'W' && id[1] == 'N')
		return (parse_single_texture(rest, &cfg->textures.win_path, "WN"));
	if (id[0] == 'L' && id[1] == 'S')
		return (parse_single_texture(rest, &cfg->textures.lose_path, "LS"));
	if (id[0] == 'S' && id[1] == 'P')
		return (parse_sprite_texture(rest, cfg));
	return (parser_error("invalid texture identifier"));
}
