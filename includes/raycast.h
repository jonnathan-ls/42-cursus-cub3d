/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:47 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 22:21:02 by jlacerda         ###   ########.fr       */
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
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	char	hit_type;
}			t_ray;

void		calculate_raycast_direction(t_ray *ray, struct s_player *pl);
void		config_initialize_raycast(struct s_engine *eng, t_ray *ray, int x);

void		setup_dda(t_ray *ray, struct s_player *pl);
void		perform_dda(struct s_engine *eng, t_ray *ray);
int			detect_collision(struct s_engine *eng, t_ray *ray);

void		calculate_distances(t_ray *ray, struct s_player *pl);

#endif
