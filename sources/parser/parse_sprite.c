/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 01:40:10 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shared.h"

static char	*skip_to_space(char *str)
{
	while (*str && *str != ' ' && *str != '\t' && *str != '\n')
		str++;
	return (str);
}

static int	extract_frame_count(char *space)
{
	int	frames;

	while (*space == ' ' || *space == '\t')
		space++;
	frames = ft_atoi(space);
	if (frames > 0)
		return (frames);
	return (1);
}

int	parse_sprite_texture(char *rest, t_config *cfg)
{
	char	*space;

	if (cfg->textures.sprite_path)
		return (parser_error("Duplicate texture"));
	space = skip_to_space(rest);
	if (*space)
	{
		*space = '\0';
		space++;
		cfg->textures.sprite_frames = extract_frame_count(space);
	}
	return (parse_texture(rest, &cfg->textures.sprite_path));
}
