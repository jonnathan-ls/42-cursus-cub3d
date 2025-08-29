/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:17 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/28 21:40:39 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include <math.h>

void	ft_init_ray(t_engine *eng, t_ray *ray, int x)
{
	double	w;

	ray->x = x;
	w = eng->win_w - 1;
	ray->cam_x = 2.0 * x / w - 1.0;
	ray->map_x = (int)eng->player.pos_x;
	ray->map_y = (int)eng->player.pos_y;
	ray->hit = 0;
	ray->side = 0;
	ray->perp_dist = 0;
}

void	ft_calculate_ray_dir(t_ray *ray, t_player *pl)
{
	ray->ray_dir_x = pl->dir_x + pl->plane_x * ray->cam_x;
	ray->ray_dir_y = pl->dir_y + pl->plane_y * ray->cam_x;
}
