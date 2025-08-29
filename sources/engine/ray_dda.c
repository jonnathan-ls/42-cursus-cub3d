/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:22 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/28 21:40:37 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include <math.h>

static double	infinite(double v)
{
	if (v == 0)
		return (1e30);
	return (fabs(1.0 / v));
}

void	ft_setup_dda(t_ray *ray, t_player *pl)
{
	ray->delta_dist_x = infinite(ray->ray_dir_x);
	ray->delta_dist_y = infinite(ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pl->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - pl->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pl->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - pl->pos_y) * ray->delta_dist_y;
	}
}

int	ft_detect_wall_hit(t_engine *eng, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= eng->map_w)
		return (1);
	if (ray->map_y < 0 || ray->map_y >= eng->map_h)
		return (1);
	if (eng->map[ray->map_y][ray->map_x] == '1')
		return (1);
	return (0);
}

void	ft_perform_dda(t_engine *eng, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ft_detect_wall_hit(eng, ray))
			ray->hit = 1;
	}
}
