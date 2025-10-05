/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 01:00:45 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"

int	count_sprites_in_map(t_engine *eng)
{
	int	count;
	int	pos_y;
	int	pos_x;

	count = 0;
	pos_y = 0;
	while (pos_y < eng->map_height)
	{
		pos_x = 0;
		while (pos_x < eng->map_width)
		{
			if (eng->map[pos_y][pos_x] == 'P')
				count = count + 1;
			pos_x = pos_x + 1;
		}
		pos_y = pos_y + 1;
	}
	return (count);
}

void	add_sprite(t_engine *eng, int *index, int pos_x, int pos_y)
{
	eng->sprites.list[*index].x = (double)pos_x + 0.5;
	eng->sprites.list[*index].y = (double)pos_y + 0.5;
	eng->sprites.list[*index].distance = 0.0;
	eng->sprites.list[*index].texture = eng->sprites.textures[0];
	eng->sprites.list[*index].frame_count = eng->sprites.frame_count;
	eng->sprites.list[*index].current_frame = 0;
	eng->sprites.list[*index].anim_timer = 0.0;
	*index = *index + 1;
}

int	allocate_sprites(t_engine *eng)
{
	eng->sprites.list = mm_alloc(eng->sprites.count, sizeof(t_sprite));
	if (!eng->sprites.list)
		return (-1);
	eng->sprites.order = mm_alloc(eng->sprites.count, sizeof(int));
	if (!eng->sprites.order)
		return (-1);
	return (0);
}

void	fill_sprites(t_engine *eng)
{
	int	pos_y;
	int	pos_x;
	int	index;

	index = 0;
	pos_y = 0;
	while (pos_y < eng->map_height)
	{
		pos_x = 0;
		while (pos_x < eng->map_width)
		{
			if (eng->map[pos_y][pos_x] == 'P')
				add_sprite(eng, &index, pos_x, pos_y);
			pos_x = pos_x + 1;
		}
		pos_y = pos_y + 1;
	}
}

int	collect_sprites_from_map(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng || !eng->map)
		return (-1);
	eng->sprites.count = count_sprites_in_map(eng);
	if (eng->sprites.count == 0)
		return (0);
	if (allocate_sprites(eng) != 0)
		return (-1);
	fill_sprites(eng);
	return (0);
}
