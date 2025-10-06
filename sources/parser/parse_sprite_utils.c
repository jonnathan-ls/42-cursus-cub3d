/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:59:04 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/**
 * Checks if sprite identifier is already in use.
 * @param cfg Pointer to configuration structure.
 * @param id Identifier character to check.
 * @return 1 if duplicate, 0 otherwise.
 */
int	check_duplicate_identifier(t_config *cfg, char id)
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

/**
 * Extracts numeric value from string after whitespace.
 * @param space Pointer to string.
 * @return Extracted number or 0 if invalid.
 */
int	extract_number(char *space)
{
	while (*space == ' ' || *space == '\t')
		space++;
	if (*space >= '0' && *space <= '9')
		return (ft_atoi(space));
	return (0);
}

/**
 * Sets sprite configuration data from parameters.
 * @param sprite Pointer to sprite configuration.
 * @param params Array with frames and type values.
 */
void	set_sprite_data(t_sprite_config *sprite, int params[2])
{
	sprite->frames = params[0];
	sprite->type = params[1];
}

/**
 * Initializes parameters array with default values.
 * @param params Array to initialize.
 */
void	init_params(int params[2])
{
	params[0] = 1;
	params[1] = 0;
}
