/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"

/**
 * @brief Extracts RGBA pixel from texture at specified coordinates.
 *
 * @param tex Texture to extract pixel from.
 * @param x X coordinate of pixel.
 * @param y Y coordinate of pixel.
 * @return Packed RGBA color value.
 */
static uint32_t	extract_pixel(mlx_texture_t *tex, int x, int y)
{
	int			idx;
	uint32_t	color;

	if (x < 0 || x >= (int)tex->width)
		return (0);
	if (y < 0 || y >= (int)tex->height)
		return (0);
	idx = (y * tex->width + x) * 4;
	color = (tex->pixels[idx] << 24) | (tex->pixels[idx + 1] << 16);
	color |= (tex->pixels[idx + 2] << 8) | tex->pixels[idx + 3];
	return (color);
}

/**
 * @brief Gets pixel from current weapon animation frame.
 *
 * @param eng Engine structure containing weapon data.
 * @param x X coordinate within frame.
 * @param y Y coordinate within frame.
 * @return Packed RGBA color value.
 */
static uint32_t	get_weapon_pixel(t_engine *eng, int x, int y)
{
	mlx_texture_t	*tex;
	int				frame_x;

	tex = eng->weapon.weapon_texture;
	if (!tex)
		return (0);
	frame_x = eng->weapon.current_weapon_frame * eng->weapon.weapon_frame_width;
	return (extract_pixel(tex, frame_x + x, y));
}

/**
 * @brief Draws weapon pixel to frame buffer with transparency check.
 *
 * @param eng Engine structure containing frame buffer.
 * @param x Screen X coordinate.
 * @param y Screen Y coordinate.
 * @param color RGBA color to draw.
 */
static void	put_weapon_pixel(t_engine *eng, int x, int y, uint32_t color)
{
	int	idx;

	if (x < 0 || y < 0)
		return ;
	if (x >= eng->window_width || y >= eng->window_height)
		return ;
	if ((color & 0xFF) < 10)
		return ;
	idx = y * eng->window_width + x;
	((uint32_t *)eng->frame->pixels)[idx] = color;
}

/**
 * @brief Draws one horizontal row of weapon sprite.
 *
 * @param eng Engine structure containing weapon data.
 * @param screen_x Screen X coordinate to start drawing.
 * @param screen_y Screen Y coordinate to start drawing.
 * @param row Row index in weapon texture.
 */
static void	draw_weapon_row(t_engine *eng, int screen_x, int screen_y, int row)
{
	int			col;
	uint32_t	color;

	col = 0;
	while (col < eng->weapon.weapon_frame_width)
	{
		color = get_weapon_pixel(eng, col, row);
		put_weapon_pixel(eng, screen_x + col, screen_y + row, color);
		col++;
	}
}

/**
 * @brief Renders weapon sprite at bottom center of screen.
 *
 * @param param Engine structure cast from void pointer.
 */
void	render_weapon(void *param)
{
	t_engine	*eng;
	int			start_x;
	int			start_y;
	int			row;

	eng = (t_engine *)param;
	if (!eng || !eng->weapon.weapon_texture)
		return ;
	start_x = eng->window_width / 2 - eng->weapon.weapon_frame_width / 2;
	start_y = eng->window_height - eng->weapon.weapon_texture->height - 20;
	row = 0;
	while (row < (int)eng->weapon.weapon_texture->height)
	{
		draw_weapon_row(eng, start_x, start_y, row);
		row++;
	}
}
