/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 18:13:01 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

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

int	extract_number(char *space)
{
	while (*space == ' ' || *space == '\t')
		space++;
	if (*space >= '0' && *space <= '9')
		return (ft_atoi(space));
	return (0);
}

void	set_sprite_data(t_sprite_config *sprite, int params[3])
{
	sprite->frames = params[0];
	sprite->type = params[1];
	sprite->category = params[2];
}

void	init_params(int params[3])
{
	params[0] = 1;
	params[1] = 0;
	params[2] = 0;
}
