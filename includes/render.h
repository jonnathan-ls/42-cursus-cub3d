/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:42 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/23 23:13:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "engine.h"
# include "raycast.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

int				ft_calculate_wall_height(struct s_ray *ray, int win_h);
mlx_texture_t	*ft_get_wall_texture(struct s_engine *eng, struct s_ray *ray);
int				ft_calculate_texture_x(t_ray *ray, mlx_texture_t *tex,
					double wall_x);
uint32_t		ft_get_texture_pixel(mlx_texture_t *tex, int tex_x, int tex_y);

void			ft_render_wall_strip(struct s_engine *eng, struct s_ray *ray,
					int start, int end);
void			ft_render_ceiling_floor(struct s_engine *eng, struct s_ray *ray,
					int start, int end);

void			ft_cast_all_rays(struct s_engine *eng);
void			ft_render_walls(struct s_engine *eng);
void			ft_update_image_buffer(struct s_engine *eng);

#endif
