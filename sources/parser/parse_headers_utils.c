/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 09:01:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 01:27:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shared.h"

/**
 * @brief Parses a single texture path and stores it in the destination.
 *
 * Checks for duplicate texture definitions and delegates parsing to
 * the parse_texture function.
 *
 * @param rest String containing texture path.
 * @param dst Pointer to store the texture path.
 * @param name Name of the texture for error reporting.
 * @return 0 on success, -1 on failure.
 */
int	parse_single_texture(char *rest, char **dst, char *name)
{
	if (*dst)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" ", 1);
		return (parser_error("Duplicate texture"));
	}
	return (parse_texture(rest, dst));
}

/**
 * @brief Handles parsing of texture lines based on identifier.
 *
 * Identifies the texture type from the two-character identifier and
 * delegates to parse_single_texture or parse_sprite_texture.
 *
 * @param id Pointer to identifier string.
 * @param cfg Configuration structure to update.
 * @return 0 on success, -1 on failure.
 */
static int	handle_texture_line(char *id, t_config *cfg)
{
	char	*rest;

	rest = id + 2;
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if (id[0] == 'N' && id[1] == 'O')
		return (parse_single_texture(rest, &cfg->textures.no_path, "NO"));
	if (id[0] == 'S' && id[1] == 'O')
		return (parse_single_texture(rest, &cfg->textures.so_path, "SO"));
	if (id[0] == 'W' && id[1] == 'E')
		return (parse_single_texture(rest, &cfg->textures.we_path, "WE"));
	if (id[0] == 'E' && id[1] == 'A')
		return (parse_single_texture(rest, &cfg->textures.ea_path, "EA"));
	if (id[0] == 'S' && id[1] == 'P')
		return (parse_sprite_texture(rest, cfg));
	return (handle_optional_texture(id, cfg, rest));
}

/**
 * @brief Handles parsing of color lines (F or C).
 *
 * Extracts and parses RGB values for floor or ceiling colors, checking
 * for duplicates before storing in the configuration structure.
 *
 * @param id Pointer to identifier string.
 * @param cfg Configuration structure to update.
 * @return 0 on success, -1 on failure.
 */
static int	handle_color_line(char *id, t_config *cfg)
{
	char	*rest;

	if (!(id[1] == ' ' || id[1] == '\t'))
		return (parser_error("invalid texture line format"));
	rest = id + 1;
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if (id[0] == 'F')
	{
		if (cfg->floor_color.rgba != -1)
			return (parser_error("duplicate color identifier"));
		if (parse_color(rest, &cfg->floor_color) < 0)
			return (-1);
	}
	else if (id[0] == 'C')
	{
		if (cfg->ceiling_color.rgba != -1)
			return (parser_error("duplicate color identifier"));
		if (parse_color(rest, &cfg->ceiling_color) < 0)
			return (-1);
	}
	return (0);
}

/**
 * @brief Parses texture path lines for mandatory and optional textures.
 *
 * Identifies whether the line represents a mandatory texture (NO, SO,
 * WE, EA) or optional texture (FT, CT, DR, MN, SP) and processes it.
 *
 * @param id Pointer to identifier string.
 * @param cfg Configuration structure to update.
 * @param count_done Pointer to mandatory texture count.
 * @return 0 if processed, 1 if not a texture line, -1 on failure.
 */
static int	parse_texture_paths(char *id, t_config *cfg, int *count_done)
{
	if ((id[0] == 'N' && id[1] == 'O') || (id[0] == 'S' && id[1] == 'O')
		|| (id[0] == 'W' && id[1] == 'E') || (id[0] == 'E' && id[1] == 'A'))
	{
		if (handle_texture_line(id, cfg) < 0)
			return (-1);
		(*count_done)++;
		return (0);
	}
	if ((id[0] == 'F' && id[1] == 'T') || (id[0] == 'C' && id[1] == 'T')
		|| (id[0] == 'D' && id[1] == 'R') || (id[0] == 'M' && id[1] == 'N')
		|| (id[0] == 'S' && id[1] == 'T') || (id[0] == 'W' && id[1] == 'N')
		|| (id[0] == 'L' && id[1] == 'S') || (id[0] == 'S' && id[1] == 'P'))
	{
		if (handle_texture_line(id, cfg) < 0)
			return (-1);
		return (0);
	}
	return (1);
}

/**
 * @brief Parses a single header line (texture or color).
 *
 * Identifies the line type and delegates to the appropriate parser.
 * Returns -2 if the line does not match any known header format,
 * indicating the start of the map section.
 *
 * @param line Line to parse.
 * @param cfg Configuration structure to update.
 * @param count_done Pointer to mandatory header count.
 * @return 0 on success, -1 on error, -2 if map section detected.
 */
int	parse_header_line(char *line, t_config *cfg, int *count_done)
{
	char	*id;
	int		result;

	if (!line || !cfg)
		return (parser_error("incomplete header set"));
	id = line;
	while (*id == ' ' || *id == '\t')
		id++;
	if (*id == '\n' || *id == '\0')
		return (0);
	result = parse_texture_paths(id, cfg, count_done);
	if (result != 1)
		return (result);
	if (id[0] == 'F' || id[0] == 'C')
	{
		if (handle_color_line(id, cfg) < 0)
			return (-1);
		(*count_done)++;
		return (0);
	}
	return (-2);
}
