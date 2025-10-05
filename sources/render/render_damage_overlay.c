/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_damage_overlay.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 17:04:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "render.h"
#include <math.h>

static uint32_t	apply_red_tint(uint32_t base, double alpha)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (base >> 24) & 0xFF;
	g = (base >> 16) & 0xFF;
	b = (base >> 8) & 0xFF;
	a = base & 0xFF;
	r = (uint8_t)(r * (1.0 - alpha) + 255 * alpha);
	g = (uint8_t)(g * (1.0 - alpha));
	b = (uint8_t)(b * (1.0 - alpha));
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static double	get_flash_intensity(double time)
{
	double	wave;

	wave = fabs(sin(time * 3.14159 * 5.0));
	return (wave * 0.3);
}

static void	apply_overlay(uint32_t *pixels, int size, double alpha)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pixels[i] = apply_red_tint(pixels[i], alpha);
		i++;
	}
}

void	render_damage_overlay(t_engine *eng)
{
	uint32_t	*pixels;
	double		alpha;
	int			total;

	if (!eng->player.is_taking_damage)
		return ;
	pixels = (uint32_t *)eng->frame->pixels;
	alpha = get_flash_intensity(eng->mlx->delta_time * 10.0);
	total = eng->window_width * eng->window_height;
	apply_overlay(pixels, total, alpha);
}
