/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_death.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:25:14 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "constants.h"

int	get_death_texture_index(t_engine *eng)
{
	int	i;

	i = 0;
	while (i < eng->sprites.texture_count)
	{
		if (eng->sprites.configs[i].type == SPRITE_TYPE_ENEMY_DEAD)
			return (i);
		i++;
	}
	return (-1);
}

mlx_texture_t	*get_sprite_texture(t_engine *eng, t_sprite *sprite)
{
	int	death_idx;

	if (!sprite->is_dying)
		return (eng->sprites.textures[sprite->type_index]);
	death_idx = get_death_texture_index(eng);
	if (death_idx < 0)
		return (eng->sprites.textures[sprite->type_index]);
	return (eng->sprites.textures[death_idx]);
}

int	get_sprite_frame_count(t_engine *eng, t_sprite *sprite)
{
	int	death_idx;

	if (!sprite->is_dying)
		return (sprite->frame_count);
	death_idx = get_death_texture_index(eng);
	if (death_idx < 0)
		return (sprite->frame_count);
	return (eng->sprites.configs[death_idx].frames);
}

int	get_sprite_texture_index(t_engine *eng, t_sprite *sprite)
{
	int	death_idx;

	if (!sprite->is_dying)
		return (sprite->type_index);
	death_idx = get_death_texture_index(eng);
	if (death_idx < 0)
		return (sprite->type_index);
	return (death_idx);
}
