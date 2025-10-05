/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 01:53:04 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

static void	render_single_sprite(t_engine *eng, t_sprite *sprite)
{
	t_sprite_render	render;
	int				x;

	if (!sprite || !sprite->texture)
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
