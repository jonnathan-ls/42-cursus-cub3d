/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 17:04:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

static void	advance_frame(t_sprite *sprite, int max_frame)
{
	sprite->current_frame++;
	if (sprite->current_frame >= max_frame)
		sprite->current_frame = max_frame - 1;
	sprite->anim_timer = 0.0;
}

static void	loop_frame(t_sprite *sprite, int max_frame)
{
	sprite->current_frame++;
	if (sprite->current_frame >= max_frame)
		sprite->current_frame = 0;
	sprite->anim_timer = 0.0;
}

static void	update_animation(t_engine *eng, t_sprite *spr, double delta)
{
	int	max_frame;

	if (spr->frame_count <= 1)
		return ;
	spr->anim_timer += delta;
	if (spr->anim_timer < 0.15)
		return ;
	if (spr->is_dying)
	{
		max_frame = get_sprite_frame_count(eng, spr);
		advance_frame(spr, max_frame);
	}
	else
		loop_frame(spr, spr->frame_count);
}

static void	update_death_timer(t_sprite *sprite, double delta)
{
	if (!sprite->is_dying)
		return ;
	sprite->death_timer += delta;
	if (sprite->death_timer >= 1.5)
		sprite->collected = 1;
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
		update_animation(eng, &eng->sprites.list[i], delta);
		update_death_timer(&eng->sprites.list[i], delta);
		i++;
	}
}
