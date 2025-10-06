/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:51:39 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "constants.h"

uint8_t	extract_color_channel(uint32_t color, int shift)
{
	return ((uint8_t)((color >> shift) & COLOR_MASK));
}

uint32_t	build_rgba_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << COLOR_SHIFT_RED) | (g << COLOR_SHIFT_GREEN)
		| (b << COLOR_SHIFT_BLUE) | a);
}
