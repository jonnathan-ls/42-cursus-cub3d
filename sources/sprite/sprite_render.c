/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

/**
 * @brief Renders a single sprite to the frame buffer.
 *
 * @param eng Engine structure containing rendering data.
 * @param sprite Sprite to render.
 */
static void	render_single_sprite(t_engine *eng, t_sprite *sprite)
{
	t_sprite_render	render;
	int				x;

	if (!sprite || sprite->collected)
		return ;
	if (!eng->sprites.textures[sprite->type_index])
		return ;
	calculate_transform(eng, sprite, &render);
	if (render.transform_y <= 0)
		return ;
	calculate_height(eng, &render);
	calculate_width(eng, &render);
	x = render.draw_start_x;
	while (x < render.draw_end_x)
	{
		if (render.transform_y > 0 && x > 0 && x < eng->window_width)
			draw_column(eng, sprite, &render, x);
		x = x + 1;
	}
}

/**
 * @brief Renders all sprites in depth-sorted order.
 *
 * @param param Engine structure cast from void pointer.
 */
void	render_sprites(void *param)
{
	t_engine	*eng;
	int			i;
	int			sprite_index;

	eng = (t_engine *)param;
	if (!eng || !eng->sprites.list || eng->sprites.count == 0)
		return ;
	sprite_sorting(eng);
	i = 0;
	while (i < eng->sprites.count)
	{
		sprite_index = eng->sprites.order[i];
		render_single_sprite(eng, &eng->sprites.list[sprite_index]);
		i = i + 1;
	}
}
