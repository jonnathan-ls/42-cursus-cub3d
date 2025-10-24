/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/23 21:14:55 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_H
# define WEAPON_H

# include <MLX42/MLX42.h>

/** @brief Maximum number of active projectiles in pool. */
# define MAX_PROJECTILES 32

/**
 * @struct s_projectile
 * @brief Projectile entity state and properties.
 */
typedef struct s_projectile
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	int				active;
	double			speed;
	int				damage;
	int				current_frame;
	double			anim_timer;
}					t_projectile;

/**
 * @struct s_weapon_system
 * @brief Weapon and projectile management system.
 */
typedef struct s_weapon_system
{
	mlx_texture_t	*weapon_texture;
	mlx_texture_t	*projectile_texture;
	mlx_texture_t	*death_texture;
	int				weapon_frames;
	int				projectile_frames;
	int				death_frames;
	int				weapon_frame_width;
	int				projectile_frame_width;
	int				death_frame_width;
	t_projectile	projectiles[MAX_PROJECTILES];
	int				current_weapon_frame;
	double			weapon_anim_timer;
	double			shoot_cooldown;
}					t_weapon_system;

int					is_wall(t_engine *eng, double x, double y);
void				init_weapon_system(void *eng);
void				free_weapon_system(void *eng);
void				render_weapon(void *eng);
void				handle_weapon_shoot(void *eng);
void				update_projectiles(void *eng, double delta);
void				render_projectiles(void *eng);
void				check_projectile_hits(void *eng);

void				init_default_values(void *eng);
void				set_weapon_frame_width(void *eng);
void				set_projectile_frame_width(void *eng);
void				set_death_frame_width(void *eng);

#endif
