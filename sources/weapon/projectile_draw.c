/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_draw.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 17:17:02 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"

void	calc_tex_coords(int pos[2], int start[2], int screen, int *tex)
{
	tex[0] = (pos[0] - start[0]) * screen;
	tex[1] = (pos[1] - start[1]) * screen;
}

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
