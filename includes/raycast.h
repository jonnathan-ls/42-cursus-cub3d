/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:47 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 22:30:21 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "engine.h"
# include "player.h"
# include <stdint.h>

typedef struct s_ray
{
	int		x;
	int		hit;
	int		side;
	double	cam_x;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	char	hit_type;
	double	perp_dist;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
}			t_ray;

void		setup_dda(t_ray *ray, t_player *pl);
void		perform_dda(t_engine *eng, t_ray *ray);
int			detect_collision(t_engine *eng, t_ray *ray);
void		calculate_distances(t_ray *ray, t_player *pl);
void		calculate_raycast_direction(t_ray *ray, t_player *pl);
void		configure_raycast_initialization(t_engine *eng, t_ray *ray, int x);

#endif
