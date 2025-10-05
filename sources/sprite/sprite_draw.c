/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 17:17:02 by jlacerda         ###   ########.fr       */
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

static int	calc_local_x(t_engine *eng, t_sprite_render *r,
	int x, int idx)
{
	int	local_x;
	int	sprite_start;

	sprite_start = -r->sprite_width / 2 + r->screen_x;
	local_x = (x - sprite_start) * eng->sprites.frame_widths[idx];
	return (local_x / r->sprite_width);
}

static int	calc_texture_x(t_engine *eng, t_sprite *s,
	t_sprite_render *r, int x)
{
	double	frame_w;
	int		local_x;
	int		tex_x;
	int		idx;
	int		frames;

	idx = get_sprite_texture_index(eng, s);
	frames = get_sprite_frame_count(eng, s);
	local_x = calc_local_x(eng, r, x, idx);
	if (local_x < 0 || local_x >= eng->sprites.frame_widths[idx])
		return (-1);
	frame_w = (double)eng->sprites.textures[idx]->width;
	frame_w = frame_w / (double)frames;
	tex_x = (int)(s->current_frame * frame_w + local_x);
	if (tex_x >= (int)eng->sprites.textures[idx]->width)
		tex_x = eng->sprites.textures[idx]->width - 1;
	return (tex_x);
}

static void	draw_column_pixels(t_engine *eng, mlx_texture_t *tex,
	t_sprite_render *r, int params[2])
{
	int		y;
	int		tex_y;
	double	horizon;

	horizon = (double)(eng->window_height / 2);
	horizon -= eng->player.pitch * ((double)eng->window_height / 4.0);
	y = r->draw_start_y;
	while (y < r->draw_end_y)
	{
		tex_y = (y - (int)horizon + r->sprite_height / 2);
		tex_y = (tex_y * tex->height) / r->sprite_height;
		if (tex_y >= 0 && tex_y < (int)tex->height)
			put_pixel(eng, params[0], y,
				get_texture_pixel(tex, params[1], tex_y));
		y++;
	}
}

void	draw_column(t_engine *eng, t_sprite *s, t_sprite_render *r, int x)
{
	mlx_texture_t	*tex;
	int				params[2];

	if (!s || !validate_depth(eng, r, x))
		return ;
	if (!eng->sprites.textures[s->type_index])
		return ;
	params[1] = calc_texture_x(eng, s, r, x);
	if (params[1] < 0)
		return ;
	tex = get_sprite_texture(eng, s);
	if (!tex)
		return ;
	params[0] = x;
	draw_column_pixels(eng, tex, r, params);
}
