/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 02:00:44 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include <math.h>

void	calculate_transform(t_engine *eng, t_sprite *sprite,
	t_sprite_render *render)
{
	render->sprite_x = sprite->x - eng->player.pos_x;
	render->sprite_y = sprite->y - eng->player.pos_y;
	render->inv_det = 1.0 / (eng->player.plane_x * eng->player.dir_y
			- eng->player.dir_x * eng->player.plane_y);
	render->transform_x = render->inv_det * (eng->player.dir_y
			* render->sprite_x - eng->player.dir_x * render->sprite_y);
	render->transform_y = render->inv_det * (-eng->player.plane_y
			* render->sprite_x + eng->player.plane_x * render->sprite_y);
	render->screen_x = (int)((eng->window_width / 2)
			* (1 + render->transform_x / render->transform_y));
}

void	calculate_height(t_engine *eng, t_sprite_render *render)
{
	int		height;
	int		base_horizon;
	double	adjusted_horizon;

	height = (int)fabs((eng->window_height / render->transform_y));
	base_horizon = eng->window_height / 2;
	adjusted_horizon = (double)base_horizon - eng->player.pitch
		* ((double)eng->window_height / 4.0);
	render->sprite_height = height;
	render->draw_start_y = (int)adjusted_horizon - height / 2;
	if (render->draw_start_y < 0)
		render->draw_start_y = 0;
	render->draw_end_y = (int)adjusted_horizon + height / 2;
	if (render->draw_end_y >= eng->window_height)
		render->draw_end_y = eng->window_height - 1;
}

void	calculate_width(t_engine *eng, t_sprite_render *render)
{
	int	width;

	width = (int)fabs((eng->window_height / render->transform_y));
	render->sprite_width = width;
	render->draw_start_x = -width / 2 + render->screen_x;
	if (render->draw_start_x < 0)
		render->draw_start_x = 0;
	render->draw_end_x = width / 2 + render->screen_x;
	if (render->draw_end_x >= eng->window_width)
		render->draw_end_x = eng->window_width - 1;
}

int	validate_depth(t_engine *eng, t_sprite_render *render, int x)
{
	if (!eng->z_buffer)
		return (1);
	if (x < 0 || x >= eng->window_width)
		return (0);
	if (render->transform_y >= eng->z_buffer[x])
		return (0);
	return (1);
}
