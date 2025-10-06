/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:21:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 01:25:28 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "parser.h"
# include "player.h"
# include "sprite.h"
# include "weapon.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

/**
 * @struct s_door
 * @brief Interactive door entity state.
 */
typedef struct s_door
{
	int		x;			/**< Door map X coordinate. */
	int		y;			/**< Door map Y coordinate. */
	int		is_open;	/**< Door open state flag. */
	double	offset;		/**< Opening animation offset [0, 1]. */
}			t_door;

/**
 * @struct s_doors_manager
 * @brief Manages all doors in the scene.
 */
typedef struct s_doors_manager
{
	t_door	*list;	/**< Array of door entities. */
	int		count;	/**< Total door count. */
}			t_doors_manager;

/**
 * @struct s_textures_bundle
 * @brief Collection of loaded game textures.
 */
typedef struct s_textures_bundle
{
	mlx_texture_t		*door;		/**< Door texture. */
	mlx_texture_t		*west;		/**< West wall texture. */
	mlx_texture_t		*east;		/**< East wall texture. */
	mlx_texture_t		*floor;		/**< Floor texture. */
	mlx_texture_t		*north;		/**< North wall texture. */
	mlx_texture_t		*south;		/**< South wall texture. */
	mlx_texture_t		*ceiling;	/**< Ceiling texture. */
	mlx_texture_t		*menu;		/**< Menu overlay texture. */
	mlx_texture_t		*start;		/**< Start screen texture. */
	mlx_texture_t		*win;		/**< Win screen texture. */
	mlx_texture_t		*lose;		/**< Lose screen texture. */
}						t_textures_bundle;

/**
 * @struct s_engine
 * @brief Main game engine state container.
 */
typedef struct s_engine
{
	mlx_t				*mlx;				/**< MLX42 instance. */
	mlx_image_t			*frame;				/**< Frame buffer image. */
	mlx_image_t			*cursor;			/**< Crosshair cursor image. */
	t_player			player;				/**< Player state. */
	t_textures_bundle	tex;				/**< Loaded textures. */
	char				**map;				/**< Map grid array. */
	int					map_width;			/**< Map width in tiles. */
	int					map_height;			/**< Map height in tiles. */
	int					window_width;		/**< Window width in pixels. */
	int					window_height;		/**< Window height in pixels. */
	uint32_t			ceiling_color;		/**< Ceiling RGBA color. */
	uint32_t			floor_color;		/**< Floor RGBA color. */
	int					minimap_visible;	/**< Minimap visible flag. */
	int					minimap_scale;		/**< Minimap zoom level. */
	int					minimap_toggle;		/**< Minimap toggle debounce. */
	int					**explored_map;		/**< Fog of war grid. */
	int					fullmap_visible;	/**< Full map visible flag. */
	int					fullmap_toggle;		/**< Full map toggle debounce. */
	int					ignore_doors;		/**< Door collision ignore flag. */
	t_doors_manager		doors;				/**< Door manager. */
	int					menu_visible;		/**< Menu overlay visible flag. */
	int					menu_toggle;		/**< Menu toggle debounce. */
	int					fullscreen;			/**< Fullscreen mode flag. */
	int					game_started;		/**< Game started flag. */
	int					start_toggle;		/**< Start toggle debounce. */
	t_sprite_manager	sprites;			/**< Sprite manager. */
	char				*sprite_chars;		/**< Valid sprite characters. */
	double				*z_buffer;			/**< Depth buffer for sprites. */
	t_weapon_system		weapon;				/**< Weapon system. */
}						t_engine;

void					apply_window_scale(t_engine *eng);
void					reset_engine_values(t_engine *eng);

int						configure_engine(t_engine *eng, t_config *cfg);
void					destroy_engine(t_engine *eng);
void					close_engine(void *param);
int						check_key_press_cooldown(void);
void					set_player_direction(t_engine *eng, char dir);
void					draw_circle(uint32_t *pixels, int cx, int cy,
							int radius);

void					engine_loop(t_engine *eng);
int						configure_textures(t_engine *eng, t_config *cfg);
void					handle_menu_view(t_engine *eng);
void					draw_menu_overlay(t_engine *eng);
void					draw_screen_overlay(t_engine *eng, mlx_texture_t *tex);
void					handle_start_screen(t_engine *eng);
void					handle_win_screen(t_engine *eng);
void					handle_lose_screen(t_engine *eng);
void					handle_gameplay_updates(t_engine *eng,
							double delta_time);
void					handle_frame_updates(t_engine *eng,
							double delta_time);
void					draw_interface(t_engine *eng);
void					render_scene(t_engine *eng);
int						configure_doors(t_engine *eng);
void					handle_door_interaction(t_engine *eng);
int						door_is_open(t_engine *eng, int x, int y);
int						can_interact_with_door(t_engine *eng);
int						find_nearest_door_index(t_engine *eng);
void					handle_door_updates(t_engine *eng);
int						get_door_texture_offset(
							t_engine *eng, int map_x, int map_y);

int						is_valid_map_coords(t_engine *eng, int mx, int my);
int						is_walkable_tile(t_engine *eng, int mx, int my);
char					get_map_tile(t_engine *eng, int map_x, int map_y);

#endif
