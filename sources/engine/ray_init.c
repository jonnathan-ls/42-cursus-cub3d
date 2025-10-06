/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:17 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 21:43:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "constants.h"
#include <math.h>

void	configure_raycast_initialization(t_engine *eng, t_ray *ray, int x)
{
	double	width;

	ray->x = x;
	width = eng->window_width - TEXTURE_CLAMP_ONE;
	ray->cam_x = CAMERA_X_FACTOR * x / width - CAMERA_X_OFFSET;
	ray->map_x = (int)eng->player.pos_x;
	ray->map_y = (int)eng->player.pos_y;
	ray->hit = 0;
	ray->side = 0;
	ray->perp_dist = 0;
	ray->hit_type = '0';
}

void	calculate_raycast_direction(t_ray *ray, t_player *pl)
{
	ray->ray_dir_x = pl->dir_x + pl->plane_x * ray->cam_x;
	ray->ray_dir_y = pl->dir_y + pl->plane_y * ray->cam_x;
}
