/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 01:48:06 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "render.h"

void	put_pixel(t_engine *eng, int x, int y, uint32_t color)
{
	if ((color & 0xFF) > 0)
		mlx_put_pixel(eng->frame, x, y, color);
}

static int	get_sprite_texture_x(t_engine *eng, t_sprite *sprite,
	t_sprite_render *render, int x)
{
	double	frame_width_exact;
	int		local_x;
	int		texture_x;

	frame_width_exact = (double)sprite->texture->width
		/ (double)sprite->frame_count;
	local_x = (x - (-render->sprite_width / 2 + render->screen_x))
		* eng->sprites.frame_width / render->sprite_width;
	if (local_x < 0 || local_x >= eng->sprites.frame_width)
		return (-1);
	texture_x = (int)(sprite->current_frame * frame_width_exact + local_x);
	if (texture_x >= (int)sprite->texture->width)
		texture_x = sprite->texture->width - 1;
	return (texture_x);
}

static void	render_pixel_column(t_engine *eng, t_sprite *sprite,
	t_sprite_render *render, int params[2])
{
	int			y;
	int			texture_y;
	int			horizon;
	uint32_t	color;

	horizon = eng->window_height / 2;
	y = render->draw_start_y;
	while (y < render->draw_end_y)
	{
		texture_y = ((y - horizon + render->sprite_height / 2)
				* sprite->texture->height) / render->sprite_height;
		if (texture_y >= 0 && texture_y < (int)sprite->texture->height)
		{
			color = get_texture_pixel(sprite->texture, params[1], texture_y);
			put_pixel(eng, params[0], y, color);
		}
		y = y + 1;
	}
}

void	draw_column(t_engine *eng, t_sprite *sprite,
	t_sprite_render *render, int x)
{
	int	texture_x;
	int	params[2];

	if (!sprite || !sprite->texture || !validate_depth(eng, render, x))
		return ;
	texture_x = get_sprite_texture_x(eng, sprite, render, x);
	if (texture_x < 0)
		return ;
	params[0] = x;
	params[1] = texture_x;
	render_pixel_column(eng, sprite, render, params);
}
