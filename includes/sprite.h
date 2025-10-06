/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:31:38 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <MLX42/MLX42.h>

/**
 * @struct s_sprite
 * @brief Sprite entity state and properties.
 */
typedef struct s_sprite
{
	double			x;				/**< Sprite X position in world. */
	double			y;				/**< Sprite Y position in world. */
	double			distance;		/**< Distance from player (for sorting). */
	int				type_index;		/**< Index into sprite type array. */
	int				sprite_type;	/**< Sprite behavior type ID. */
	int				collected;		/**< Collected/removed flag. */
	int				frame_count;	/**< Total animation frames. */
	int				current_frame;	/**< Current animation frame. */
	double			anim_timer;		/**< Animation frame timer. */
	int				health;			/**< Current health points. */
	int				is_dying;		/**< Death animation active flag. */
	double			death_timer;	/**< Death animation timer. */
	double			move_dir_x;		/**< Movement direction X. */
	double			move_dir_y;		/**< Movement direction Y. */
	double			move_timer;		/**< Movement update timer. */
	double			move_speed;		/**< Movement speed multiplier. */
}					t_sprite;

/**
 * @struct s_sprite_manager
 * @brief Manages all sprites in the scene.
 */
typedef struct s_sprite_manager
{
	t_sprite			*list;			/**< Array of sprite entities. */
	int					count;			/**< Total sprite count. */
	int					*order;			/**< Depth-sorted render order. */
	mlx_texture_t		**textures;		/**< Sprite texture array. */
	int					*frame_counts;	/**< Frames per texture. */
	int					*frame_widths;	/**< Width per frame. */
	int					*sprite_types;	/**< Type ID per texture. */
	int					texture_count;	/**< Total loaded textures. */
	t_sprite_config		*configs;		/**< Sprite configurations. */
}					t_sprite_manager;

/**
 * @struct s_sprite_render
 * @brief Sprite rendering calculation state.
 */
typedef struct s_sprite_render
{
	double			sprite_x;		/**< Sprite X relative to player. */
	double			sprite_y;		/**< Sprite Y relative to player. */
	double			inv_det;		/**< Inverse determinant for transform. */
	double			transform_x;	/**< Transformed X in camera space. */
	double			transform_y;	/**< Transformed Y (depth). */
	int				screen_x;		/**< Screen X position of sprite. */
	int				sprite_height;	/**< Screen height of sprite. */
	int				sprite_width;	/**< Screen width of sprite. */
	int				draw_start_y;	/**< Top pixel to draw. */
	int				draw_end_y;		/**< Bottom pixel to draw. */
	int				draw_start_x;	/**< Left pixel to draw. */
	int				draw_end_x;		/**< Right pixel to draw. */
}					t_sprite_render;

void				init_sprites(void *eng, t_sprite_config *sprites,
						int count);
void				init_sprite_values(t_engine *eng);
void				setup_sprite_type(t_engine *eng, t_sprite_config *cfg,
						int i);
void				setup_sprite_loop(t_engine *eng, t_sprite_config *cfg,
						int count);
void				update_sprites(void *eng, double delta);
void				render_sprites(void *eng);
void				free_sprites(void *eng);
void				sprite_sorting(void *eng);
int					collect_sprites_from_map(void *eng);
int					count_sprites_in_map(t_engine *eng);
void				add_sprite_to_list(t_engine *eng, int *idx, int pos[2],
						char type);
int					allocate_sprites(t_engine *eng);
void				fill_sprites(t_engine *eng);
void				calculate_transform(t_engine *eng, t_sprite *sprite,
						t_sprite_render *render);
void				calculate_height(t_engine *eng, t_sprite_render *render);
void				calculate_width(t_engine *eng, t_sprite_render *render);
int					validate_depth(t_engine *eng, t_sprite_render *render,
						int x);
void				put_pixel(t_engine *eng, int x, int y, uint32_t color);
void				draw_column(t_engine *eng, t_sprite *sprite,
						t_sprite_render *render, int x);
void				check_sprite_interactions(void *eng);
void				handle_coin_pickup(t_engine *eng, t_sprite *sprite);
void				update_enemy_movement(void *eng, double delta);
int					get_death_texture_index(t_engine *eng);
mlx_texture_t		*get_sprite_texture(t_engine *eng, t_sprite *sprite);
int					get_sprite_frame_count(t_engine *eng, t_sprite *sprite);
int					get_sprite_texture_index(t_engine *eng, t_sprite *sprite);

#endif
