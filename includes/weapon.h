/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:31:38 by jlacerda         ###   ########.fr       */
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
	double			x;				/**< Projectile X position. */
	double			y;				/**< Projectile Y position. */
	double			dir_x;			/**< Movement direction X component. */
	double			dir_y;			/**< Movement direction Y component. */
	int				active;			/**< Projectile active flag. */
	double			speed;			/**< Movement speed. */
	int				damage;			/**< Damage dealt on hit. */
	int				current_frame;	/**< Current animation frame. */
	double			anim_timer;		/**< Animation frame timer. */
}					t_projectile;

/**
 * @struct s_weapon_system
 * @brief Weapon and projectile management system.
 */
typedef struct s_weapon_system
{
	mlx_texture_t	*weapon_texture;		/**< Weapon sprite texture. */
	mlx_texture_t	*projectile_texture;	/**< Projectile sprite texture. */
	mlx_texture_t	*death_texture;			/**< Death animation texture. */
	int				weapon_frames;			/**< Weapon animation frames. */
	int				projectile_frames;		/**< Projectile animation frames. */
	int				death_frames;			/**< Death animation frames. */
	int				weapon_frame_width;		/**< Single weapon frame width. */
	int				projectile_frame_width;	/**< Projectile frame width. */
	int				death_frame_width;		/**< Death frame width. */
	t_projectile	projectiles[MAX_PROJECTILES];	/**< Projectile pool. */
	int				current_weapon_frame;	/**< Current weapon frame. */
	double			weapon_anim_timer;		/**< Weapon animation timer. */
	double			shoot_cooldown;			/**< Shooting cooldown timer. */
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
