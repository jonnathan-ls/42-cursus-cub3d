/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/04 23:42:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

static void	update_sprite_animation(t_sprite *sprite, double delta)
{
	double	anim_speed;

	if (!sprite || sprite->frame_count <= 1)
		return ;
	anim_speed = 0.15;
	sprite->anim_timer = sprite->anim_timer + delta;
	if (sprite->anim_timer >= anim_speed)
	{
		sprite->current_frame = sprite->current_frame + 1;
		if (sprite->current_frame >= sprite->frame_count)
			sprite->current_frame = 0;
		sprite->anim_timer = 0.0;
	}
}

void	update_sprites(void *param, double delta)
{
	t_engine	*eng;
	int			i;

	eng = (t_engine *)param;
	if (!eng || !eng->sprites.list)
		return ;
	i = 0;
	while (i < eng->sprites.count)
	{
		update_sprite_animation(&eng->sprites.list[i], delta);
		i = i + 1;
	}
}
