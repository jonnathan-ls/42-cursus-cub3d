/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:34 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 19:19:16 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include <math.h>

int	ft_calculate_wall_height(t_ray *ray, int win_h)
{
	int	h;

	h = (int)(win_h / ray->perp_dist);
	return (h);
}

mlx_texture_t	*ft_get_wall_texture(t_engine *eng, t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (eng->tex.west);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (eng->tex.east);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		return (eng->tex.north);
	return (eng->tex.south);
}

int	ft_calculate_texture_x(t_ray *ray, mlx_texture_t *tex, double wall_x)
{
	int	tex_x;

	if (!tex)
		return (0);
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - 1;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
