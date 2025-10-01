/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:42 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/03 00:14:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "engine.h"
# include "raycast.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

typedef struct s_pixel
{
	mlx_texture_t	*tex;
	int				tx;
	double			pos;
	int				shift;
}	t_pixel;

float			calculate_distance_shade(double distance);
double			calculate_wall_x(t_engine *eng, t_ray *ray);
int				calculate_wall_height(struct s_ray *ray, int win_h);
uint32_t		calculate_floor_texture(t_engine *eng,
					int y, t_ray *ray, double *distance);
uint32_t		calculate_ceiling_texture(t_engine *eng,
					int y, t_ray *ray, double *distance);
int				calculate_texture_x(t_ray *ray, mlx_texture_t *tex,
					double wall_x);

void			cast_all_rays(struct s_engine *eng);
mlx_texture_t	*get_wall_texture(struct s_engine *eng, struct s_ray *ray);
uint32_t		get_texture_pixel(mlx_texture_t *tex, int tex_x, int tex_y);
uint32_t		get_texture_pixel(mlx_texture_t *tex, int tex_x, int tex_y);

void			render_wall_strip(struct s_engine *eng, struct s_ray *ray,
					int start, int end);
void			render_ceiling_floor(struct s_engine *eng, struct s_ray *ray,
					int start, int end);

float			calculate_distance_shade(double distance);
uint32_t		apply_distance_shading(uint32_t color, double distance);
uint32_t		shaded_pixel_from_pos(
					mlx_texture_t *tex, int tx, double pos, t_ray *ray);

#endif
