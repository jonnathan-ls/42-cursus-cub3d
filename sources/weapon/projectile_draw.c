/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"

/**
 * @brief Calculates texture coordinates from screen and start positions.
 *
 * @param pos Screen position [x, y].
 * @param start Start position [x, y].
 * @param screen Screen size.
 * @param tex Output texture coordinates [x, y].
 */
void	calc_tex_coords(int pos[2], int start[2], int screen, int *tex)
{
	tex[0] = (pos[0] - start[0]) * screen;
	tex[1] = (pos[1] - start[1]) * screen;
}

/**
 * @brief Draws pixel to frame buffer if valid and not transparent.
 *
 * @param eng Engine structure containing frame buffer.
 * @param pos Screen position [x, y].
 * @param color RGBA color to draw.
 */
void	draw_pixel_if_valid(t_engine *eng, int pos[2], uint32_t color)
{
	int	idx;

	if (pos[0] < 0 || pos[1] < 0)
		return ;
	if ((color & 0xFF) <= 10)
		return ;
	idx = pos[1] * eng->window_width + pos[0];
	((uint32_t *)eng->frame->pixels)[idx] = color;
}
