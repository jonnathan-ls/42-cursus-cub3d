/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

/**
 * @brief Advances sprite animation frame (one-shot progression).
 *
 * @param sprite Sprite to advance frame for.
 * @param max_frame Maximum frame number.
 */
static void	advance_frame(t_sprite *sprite, int max_frame)
{
	sprite->current_frame++;
	if (sprite->current_frame >= max_frame)
		sprite->current_frame = max_frame - 1;
	sprite->anim_timer = 0.0;
}

/**
 * @brief Loops sprite animation frame (continuous cycle).
 *
 * @param sprite Sprite to loop frame for.
 * @param max_frame Maximum frame number.
 */
static void	loop_frame(t_sprite *sprite, int max_frame)
{
	sprite->current_frame++;
	if (sprite->current_frame >= max_frame)
		sprite->current_frame = 0;
	sprite->anim_timer = 0.0;
}

/**
 * @brief Updates sprite animation based on state and timer.
 *
 * @param eng Engine structure for death animation data.
 * @param spr Sprite to update animation for.
 * @param delta Delta time for animation timing.
 */
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

/**
 * @brief Updates death timer and marks sprite for removal.
 *
 * @param sprite Sprite to update death timer for.
 * @param delta Delta time for timer progression.
 */
static void	update_death_timer(t_sprite *sprite, double delta)
{
	if (!sprite->is_dying)
		return ;
	sprite->death_timer += delta;
	if (sprite->death_timer >= 1.5)
		sprite->collected = 1;
}

/**
 * @brief Updates animation and death timers for all sprites.
 *
 * @param param Engine structure cast from void pointer.
 * @param delta Delta time for frame-independent updates.
 */
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
