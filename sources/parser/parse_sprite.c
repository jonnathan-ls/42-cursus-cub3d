/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:09:57 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shared.h"

/**
 * @brief Adds a new sprite configuration to the config structure.
 *
 * Creates a new array with increased capacity, copies existing sprite
 * configurations, and appends the new sprite with its parameters.
 *
 * @param cfg Configuration structure to update.
 * @param id Sprite identifier character.
 * @param path Path to sprite texture.
 * @param p Array containing frame count and animation time.
 * @return 0 on success, -1 on failure.
 */
static int	add_sprite_config(t_config *cfg, char id, char *path, int p[2])
{
	t_sprite_config	*new_array;
	int				count;
	int				i;

	if (check_duplicate_identifier(cfg, id))
		return (parser_error("duplicate sprite identifier"));
	count = cfg->textures.sprite_count;
	new_array = mm_alloc(count + 1, sizeof(t_sprite_config));
	if (!new_array)
		return (-1);
	i = 0;
	while (i < count)
	{
		new_array[i] = cfg->textures.sprites[i];
		i = i + 1;
	}
	new_array[count].identifier = id;
	new_array[count].path = path;
	set_sprite_data(&new_array[count], p);
	cfg->textures.sprites = new_array;
	cfg->textures.sprite_count = count + 1;
	return (0);
}

/**
 * @brief Extracts sprite animation parameters from a string.
 *
 * Parses frame count and animation time from the input string, skipping
 * whitespace and positioning correctly to extract each numeric value.
 *
 * @param space Pointer to string containing sprite parameters.
 * @param params Array to store extracted frame count and animation time.
 */
static void	parse_sprite_params(char *space, int params[2])
{
	params[0] = extract_frame_count(space);
	while (*space && (*space == ' ' || *space == '\t'))
		space++;
	while (*space >= '0' && *space <= '9')
		space++;
	while (*space && (*space == ' ' || *space == '\t'))
		space++;
	params[1] = extract_number(space);
}

/**
 * @brief Parses a sprite texture line from the configuration file.
 *
 * Extracts sprite identifier, texture path, and optional animation
 * parameters (frame count and animation time) from the input line.
 *
 * @param rest String containing sprite configuration data.
 * @param cfg Configuration structure to update.
 * @return 0 on success, -1 on failure.
 */
int	parse_sprite_texture(char *rest, t_config *cfg)
{
	char	identifier;
	char	*space;
	char	*path;
	int		params[2];

	identifier = extract_identifier(rest);
	if (!identifier)
		return (parser_error("invalid sprite identifier"));
	rest = skip_to_space(rest);
	while (*rest == ' ' || *rest == '\t')
		rest++;
	space = skip_to_space(rest);
	init_params(params);
	if (*space)
	{
		*space = '\0';
		space++;
		parse_sprite_params(space, params);
	}
	path = NULL;
	if (parse_texture(rest, &path) < 0)
		return (-1);
	return (add_sprite_config(cfg, identifier, path, params));
}
