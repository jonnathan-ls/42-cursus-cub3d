/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "constants.h"

/**
 * Extracts a color channel from RGBA color integer.
 * @param color RGBA color value.
 * @param shift Bit shift amount for channel extraction.
 * @return Extracted 8-bit color channel value.
 */
uint8_t	extract_color_channel(uint32_t color, int shift)
{
	return ((uint8_t)((color >> shift) & COLOR_MASK));
}

/**
 * Constructs RGBA color from individual channels.
 * @param r Red channel (0-255).
 * @param g Green channel (0-255).
 * @param b Blue channel (0-255).
 * @param a Alpha channel (0-255).
 * @return Combined 32-bit RGBA color value.
 */
uint32_t	build_rgba_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << COLOR_SHIFT_RED) | (g << COLOR_SHIFT_GREEN)
		| (b << COLOR_SHIFT_BLUE) | a);
}
