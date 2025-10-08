/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/08 00:32:16 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "render.h"

/**
 * @brief Draws a pixel with alpha channel check.
 *
 * Only draws the pixel if its alpha value is greater than zero,
 * providing transparency support for sprites.
 *
 * @param eng Engine structure containing frame buffer.
 * @param x Screen X coordinate.
 * @param y Screen Y coordinate.
 * @param color RGBA color value to draw.
 */
void	put_pixel(t_engine *eng, int x, int y, uint32_t color)
{
	if ((color & 0xFF) > 0)
		mlx_put_pixel(eng->frame, x, y, color);
}

/**
 * @brief Calculates local X coordinate within a sprite frame.
 *
 * Computes the X position relative to the start of a single animation
 * frame, accounting for sprite width and screen position.
 *
 * @param eng Engine structure with frame width data.
 * @param r Render structure with sprite screen position.
 * @param x Screen X coordinate.
 * @param idx Sprite texture index.
 * @return Local X coordinate within the frame.
 */
static int	calc_local_x(t_engine *eng, t_sprite_render *r,
	int x, int idx)
{
	int	local_x;
	int	sprite_start;

	sprite_start = -r->sprite_width / 2 + r->screen_x;
	local_x = (x - sprite_start) * eng->sprites.frame_widths[idx];
	return (local_x / r->sprite_width);
}

/**
 * @brief Calculates texture X coordinate for the current animation frame.
 *
 * Determines the texture X position accounting for current animation
 * frame, frame width, and local X within the frame.
 *
 * @param eng Engine structure with sprite textures and frame data.
 * @param s Sprite being rendered.
 * @param r Render structure with sprite position.
 * @param x Screen X coordinate.
 * @return Texture X coordinate, or -1 if invalid.
 */
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

/**
 * @brief Draws all pixels in a vertical sprite column.
 *
 * Iterates through Y coordinates, calculates texture Y positions with
 * pitch adjustment, and draws pixels with transparency check.
 *
 * @param eng Engine structure with frame buffer and player pitch.
 * @param tex Texture to sample from.
 * @param r Render structure with draw bounds.
 * @param params Array containing screen X and texture X coordinates.
 */
static void	draw_column_pixels(t_engine *eng, mlx_texture_t *tex,
	t_sprite_render *r, int params[2])
{
	int		y;
	int		tex_y;

	y = r->draw_start_y;
	while (y < r->draw_end_y)
	{
		tex_y = (y - (int)eng->horizon_y + r->sprite_height / 2);
		tex_y = (tex_y * tex->height) / r->sprite_height;
		if (tex_y >= 0 && tex_y < (int)tex->height)
			put_pixel(eng, params[0], y,
				get_texture_pixel(tex, params[1], tex_y));
		y++;
	}
}

/**
 * @brief Draws a complete vertical column of a sprite.
 *
 * Validates depth and texture, calculates texture X, retrieves
 * appropriate texture, and draws all pixels in the column.
 *
 * @param eng Engine structure with sprite data and frame buffer.
 * @param s Sprite being rendered.
 * @param r Render structure with position and bounds.
 * @param x Screen X coordinate of the column.
 */
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
