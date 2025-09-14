/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:28 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 19:06:27 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include "raycast.h"
#include <math.h>

void	ft_calculate_distances(t_ray *ray, t_player *pl)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - pl->pos_x + (1 - ray->step_x) / 2.0)
			/ ray->ray_dir_x;
	else
		ray->perp_dist = (ray->map_y - pl->pos_y + (1 - ray->step_y) / 2.0)
			/ ray->ray_dir_y;
	if (ray->perp_dist < DIST_EPS)
		ray->perp_dist = DIST_EPS;
}
