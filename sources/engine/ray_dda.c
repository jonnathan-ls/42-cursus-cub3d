/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:22 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/15 20:30:31 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include <math.h>

/**
 * Returns safe reciprocal value avoiding division by zero.
 * @param v Value to invert.
 * @return Reciprocal or very large number if zero.
 */
static double	infinite(double v)
{
	if (v == 0)
		return (1e30);
	return (fabs(1.0 / v));
}

/**
 * Configures DDA algorithm parameters for ray traversal.
 * @param ray Pointer to ray structure.
 * @param pl Pointer to player structure.
 */
void	setup_dda(t_ray *ray, t_player *pl)
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

/**
 * Checks if door at position is closed or closing.
 * @param eng Pointer to engine structure.
 * @param x X coordinate of door.
 * @param y Y coordinate of door.
 * @return 1 if closed, 0 if open.
 */
static int	is_door_closed_at(t_engine *eng, int x, int y)
{
	int	door_idx;

	if (!eng || !eng->doors.list || !eng->doors.grid)
		return (1);
	if (y < 0 || y >= eng->map_height || x < 0 || x >= eng->map_width)
		return (1);
	door_idx = eng->doors.grid[y][x];
	if (door_idx < 0 || door_idx >= eng->doors.count)
		return (1);
	if (!eng->doors.list[door_idx].is_active)
		return (0);
	return (eng->doors.list[door_idx].offset < 1.0);
}

/**
 * Detects if ray hit wall or closed door.
 * @param eng Pointer to engine structure.
 * @param ray Pointer to ray structure.
 * @return 1 if collision detected, 0 otherwise.
 */
int	detect_collision(t_engine *eng, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= eng->map_width)
	{
		ray->hit_type = '1';
		return (1);
	}
	if (ray->map_y < 0 || ray->map_y >= eng->map_height)
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
		if (eng->ignore_doors)
			return (0);
		return (is_door_closed_at(eng, ray->map_x, ray->map_y));
	}
	return (0);
}

/**
 * Executes DDA algorithm to traverse grid until hit.
 * @param eng Pointer to engine structure.
 * @param ray Pointer to ray structure.
 */
void	perform_dda(t_engine *eng, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x;
			ray->map_x = ray->map_x + ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;
			ray->map_y = ray->map_y + ray->step_y;
			ray->side = 1;
		}
		if (detect_collision(eng, ray))
			ray->hit = 1;
	}
}
