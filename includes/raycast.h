/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:47 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/08 00:04:39 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "engine.h"
# include "player.h"
# include <stdint.h>

/**
 * @struct s_ray
 * @brief Ray casting calculation state for a single vertical strip.
 */
typedef struct s_ray
{
	int		x;				/**< Current screen column being rendered. */
	int		hit;			/**< Wall collision detected flag. */
	int		side;			/**< Wall side hit (0=X, 1=Y axis). */
	double	cam_x;			/**< Camera space X coordinate [-1, 1]. */
	int		map_x;			/**< Current map grid X coordinate. */
	int		map_y;			/**< Current map grid Y coordinate. */
	int		step_x;			/**< DDA step direction X (-1 or 1). */
	int		step_y;			/**< DDA step direction Y (-1 or 1). */
	char	hit_type;		/**< Type of object hit (wall, door, etc). */
	double	perp_dist;		/**< Perpendicular distance to wall. */
	double	ray_dir_x;		/**< Ray direction vector X component. */
	double	ray_dir_y;		/**< Ray direction vector Y component. */
	double	side_dist_x;	/**< Distance to next X grid line. */
	double	side_dist_y;	/**< Distance to next Y grid line. */
	double	delta_dist_x;	/**< Distance between X grid lines. */
	double	delta_dist_y;	/**< Distance between Y grid lines. */
	double	angle_cache;	/**< Cached atan2 for ceiling texture. */
}			t_ray;

void		setup_dda(t_ray *ray, t_player *pl);
void		perform_dda(t_engine *eng, t_ray *ray);
int			detect_collision(t_engine *eng, t_ray *ray);
void		calculate_distances(t_ray *ray, t_player *pl);
void		calculate_raycast_direction(t_ray *ray, t_player *pl);
void		configure_raycast_initialization(t_engine *eng, t_ray *ray, int x);

#endif
