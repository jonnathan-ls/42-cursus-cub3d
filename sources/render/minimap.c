/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:57:43 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/20 16:15:37 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "minimap.h"
#include "constants.h"
#include <MLX42/MLX42.h>
#include <stdint.h>

void	ft_minimap_zoom(t_engine *eng, int zoom_in, int zoom_out)
{
	int	scale;

	if (!eng)
		return ;
	scale = eng->minimap_scale;
	if (zoom_in && scale < MINIMAP_MAX_SCALE)
		scale = scale + 1;
	if (zoom_out && scale > MINIMAP_MIN_SCALE)
		scale = scale - 1;
	eng->minimap_scale = scale;
}

void	ft_minimap_draw(t_engine *eng)
{
	int	reserved_width;
	int	reserved_height;
	int	fit_w;
	int	fit_h;
	int	final_scale;

	if (!eng || !eng->img.frame || !eng->map || !eng->minimap_visible)
		return ;
	reserved_width = eng->win_w / MINIMAP_RESERVED_DIV;
	reserved_height = eng->win_h / MINIMAP_RESERVED_DIV;
	fit_w = reserved_width / eng->map_w;
	fit_h = reserved_height / eng->map_h;
	final_scale = fit_w;
	if (fit_h < final_scale)
		final_scale = fit_h;
	if (final_scale < MINIMAP_MIN_SCALE)
		final_scale = MINIMAP_MIN_SCALE;
	if (eng->minimap_scale >= MINIMAP_MIN_SCALE
		&& eng->minimap_scale < final_scale)
		final_scale = eng->minimap_scale;
	ft_minimap_render_cells(eng, final_scale);
	mlx_put_pixel(eng->img.frame,
		(int)(eng->player.pos_x * final_scale) + MINIMAP_OFFSET,
		(int)(eng->player.pos_y * final_scale) + MINIMAP_OFFSET,
		MINIMAP_PLAYER_COLOR);
}
