/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/08 00:46:01 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <unistd.h>
# include <stdint.h>

typedef struct s_engine	t_engine;

void		mm_garbage_collector(void);
size_t		mm_nodes_alloc_length(void);
void		*mm_alloc(size_t count, size_t size);

double		calc_euclidean_dist(double x1, double y1, double x2, double y2);
int			is_in_radius(double x1, double y1, double x2, double y2);
double		clamp_double(double value, double min, double max);
int			is_within_bounds(int value, int min, int max);

/**
 * Extracts a color channel from RGBA color (inline for performance).
 * @param color RGBA color value.
 * @param shift Bit shift amount for channel extraction.
 * @return Extracted 8-bit color channel value.
 */
static inline uint8_t	extract_color_channel(uint32_t color, int shift)
{
	return ((uint8_t)((color >> shift) & 0xFF));
}

/**
 * Constructs RGBA color from individual channels (inline for performance).
 * @param r Red channel (0-255).
 * @param g Green channel (0-255).
 * @param b Blue channel (0-255).
 * @param a Alpha channel (0-255).
 * @return Combined 32-bit RGBA color value.
 */
static inline uint32_t	build_rgba_color(uint8_t r, uint8_t g,
	uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

#endif
