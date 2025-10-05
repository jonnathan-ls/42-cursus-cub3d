/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 13:52:01 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shared.h"

static int	check_duplicate_identifier(t_config *cfg, char id)
{
	int	i;

	i = 0;
	while (i < cfg->textures.sprite_count)
	{
		if (cfg->textures.sprites[i].identifier == id)
			return (1);
		i = i + 1;
	}
	return (0);
}

static int	get_sprite_type(char *space)
{
	while (*space == ' ' || *space == '\t')
		space++;
	if (*space >= '0' && *space <= '9')
		return (ft_atoi(space));
	return (0);
}

static int	add_sprite_config(t_config *cfg, char id, char *path, int params[2])
{
	t_sprite_config	*new_array;
	int				i;

	if (check_duplicate_identifier(cfg, id))
		return (parser_error("duplicate sprite identifier"));
	i = cfg->textures.sprite_count;
	new_array = mm_alloc(i + 1, sizeof(t_sprite_config));
	if (!new_array)
		return (-1);
	while (i > 0)
	{
		i = i - 1;
		new_array[i] = cfg->textures.sprites[i];
	}
	new_array[cfg->textures.sprite_count].identifier = id;
	new_array[cfg->textures.sprite_count].path = path;
	new_array[cfg->textures.sprite_count].frames = params[0];
	new_array[cfg->textures.sprite_count].type = params[1];
	cfg->textures.sprites = new_array;
	cfg->textures.sprite_count = cfg->textures.sprite_count + 1;
	return (0);
}

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
	params[0] = 1;
	params[1] = 0;
	if (*space)
	{
		*space = '\0';
		space++;
		params[0] = extract_frame_count(space);
		params[1] = get_sprite_type(skip_to_space(space));
	}
	path = NULL;
	if (parse_texture(rest, &path) < 0)
		return (-1);
	return (add_sprite_config(cfg, identifier, path, params));
}
