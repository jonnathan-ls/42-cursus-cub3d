/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:22 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/21 11:09:42 by jlacerda         ###   ########.fr       */
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

static int	is_door_closed_at(t_engine *eng, int x, int y)
{
	int	i;

	if (!eng || !eng->doors.list)
		return (1);
	i = 0;
	while (i < eng->doors.count)
	{
		if (eng->doors.list[i].x == x && eng->doors.list[i].y == y)
			return (!eng->doors.list[i].is_open);
		i++;
	}
	return (1);
}

int	ft_detect_collision(t_engine *eng, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= eng->map_w)
	{
		ray->hit_type = '1';
		return (1);
	}
	if (ray->map_y < 0 || ray->map_y >= eng->map_h)
	{
		ray->hit_type = '1';
		return (1);
	}
	if (eng->map[ray->map_y][ray->map_x] == '1')
	{
		ray->hit_type = '1';
		return (1);
	}
	if (eng->map[ray->map_y][ray->map_x] == 'D')
	{
		ray->hit_type = 'D';
		return (is_door_closed_at(eng, ray->map_x, ray->map_y));
	}
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
		if (ft_detect_collision(eng, ray))
			ray->hit = 1;
	}
}
