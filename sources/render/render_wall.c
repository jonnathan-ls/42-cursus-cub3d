/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:34 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 21:43:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "raycast.h"
#include "render.h"
#include "constants.h"
#include <math.h>

int	calculate_wall_height(t_ray *ray, int win_h)
{
	int	height;

	height = (int)(win_h / ray->perp_dist);
	return (height);
}

mlx_texture_t	*get_wall_texture(t_engine *eng, t_ray *ray)
{
	if (ray->hit_type == 'D')
		return (eng->tex.door);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (eng->tex.west);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (eng->tex.east);
	if (ray->side == 1 && ray->ray_dir_y > 0)
		return (eng->tex.north);
	return (eng->tex.south);
}

int	calculate_texture_x(t_ray *ray, mlx_texture_t *tex, double wall_x)
{
	int	tex_x;

	if (!tex)
		return (TEXTURE_CLAMP_MIN);
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < TEXTURE_CLAMP_MIN)
		tex_x = TEXTURE_CLAMP_MIN;
	if (tex_x >= (int)tex->width)
		tex_x = tex->width - TEXTURE_CLAMP_ONE;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - TEXTURE_CLAMP_ONE;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - TEXTURE_CLAMP_ONE;
	return (tex_x);
}
