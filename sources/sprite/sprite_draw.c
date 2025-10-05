/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 10:52:35 by jlacerda         ###   ########.fr       */
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
	int		type_index;

	type_index = sprite->type_index;
	frame_width_exact = (double)eng->sprites.textures[type_index]->width
		/ (double)sprite->frame_count;
	local_x = (x - (-render->sprite_width / 2 + render->screen_x))
		* eng->sprites.frame_widths[type_index] / render->sprite_width;
	if (local_x < 0 || local_x >= eng->sprites.frame_widths[type_index])
		return (-1);
	texture_x = (int)(sprite->current_frame * frame_width_exact + local_x);
	if (texture_x >= (int)eng->sprites.textures[type_index]->width)
		texture_x = eng->sprites.textures[type_index]->width - 1;
	return (texture_x);
}

static void	render_pixel_column(t_engine *eng, t_sprite *sprite,
	t_sprite_render *render, int params[2])
{
	int				y;
	int				texture_y;
	double			adjusted_horizon;
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = eng->sprites.textures[sprite->type_index];
	adjusted_horizon = (double)(eng->window_height / 2)
		- eng->player.pitch * ((double)eng->window_height / 4.0);
	y = render->draw_start_y;
	while (y < render->draw_end_y)
	{
		texture_y = ((y - (int)adjusted_horizon + render->sprite_height / 2)
				* texture->height) / render->sprite_height;
		if (texture_y >= 0 && texture_y < (int)texture->height)
		{
			color = get_texture_pixel(texture, params[1], texture_y);
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

	if (!sprite || !validate_depth(eng, render, x))
		return ;
	if (!eng->sprites.textures[sprite->type_index])
		return ;
	texture_x = get_sprite_texture_x(eng, sprite, render, x);
	if (texture_x < 0)
		return ;
	params[0] = x;
	params[1] = texture_x;
	render_pixel_column(eng, sprite, render, params);
}
