/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:48:47 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/28 21:55:27 by peda-cos         ###   ########.fr       */
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
}			t_ray;

void		ft_init_ray(struct s_engine *eng, t_ray *ray, int x);
void		ft_calculate_ray_dir(t_ray *ray, struct s_player *pl);

void		ft_setup_dda(t_ray *ray, struct s_player *pl);
void		ft_perform_dda(struct s_engine *eng, t_ray *ray);
int			ft_detect_wall_hit(struct s_engine *eng, t_ray *ray);

void		ft_calculate_distances(t_ray *ray, struct s_player *pl);
void		ft_apply_fish_eye_correction(t_ray *ray, struct s_player *pl);

#endif
