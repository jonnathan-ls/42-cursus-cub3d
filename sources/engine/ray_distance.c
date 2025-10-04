/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:28 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 20:41:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "engine.h"
#include "raycast.h"
#include <math.h>

void	calculate_distances(t_ray *ray, t_player *pl)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - pl->pos_x + (1 - ray->step_x) / 2.0)
			/ ray->ray_dir_x;
	else
		ray->perp_dist = (ray->map_y - pl->pos_y + (1 - ray->step_y) / 2.0)
			/ ray->ray_dir_y;
	if (ray->perp_dist < EPSILON)
		ray->perp_dist = EPSILON;
}
