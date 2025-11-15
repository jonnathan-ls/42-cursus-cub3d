/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:21:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/15 20:30:31 by peda-cos         ###   ########.fr       */
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
	int		x;
	int		y;
	int		is_open;
	int		is_active;
	double	offset;
}			t_door;

/**
 * @struct s_doors_manager
 * @brief Manages all doors in the scene.
 */
typedef struct s_doors_manager
{
	t_door	*list;
	int		count;
	int		**grid;
}			t_doors_manager;

/**
 * @struct s_textures_bundle
 * @brief Collection of loaded game textures.
 */
typedef struct s_textures_bundle
{
	mlx_texture_t		*door;
	mlx_texture_t		*west;
	mlx_texture_t		*east;
	mlx_texture_t		*floor;
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*ceiling;
	mlx_texture_t		*menu;
	mlx_texture_t		*start;
	mlx_texture_t		*win;
	mlx_texture_t		*lose;
}						t_textures_bundle;

/**
 * @struct s_engine
 * @brief Main game engine state container.
 */
typedef struct s_engine
{
	mlx_t				*mlx;
	mlx_image_t			*frame;
	mlx_image_t			*cursor;
	t_player			player;
	t_textures_bundle	tex;
	char				**map;
	int					map_width;
	int					map_height;
	int					window_width;
	int					window_height;
	uint32_t			ceiling_color;
	uint32_t			floor_color;
	int					minimap_visible;
	int					minimap_scale;
	int					minimap_toggle;
	int					**explored_map;
	int					fullmap_visible;
	int					fullmap_toggle;
	int					ignore_doors;
	t_doors_manager		doors;
	int					menu_visible;
	int					menu_toggle;
	int					fullscreen;
	int					game_started;
	int					start_toggle;
	t_sprite_manager	sprites;
	char				*sprite_chars;
	double				*z_buffer;
	t_weapon_system		weapon;
	double				horizon_y;
}						t_engine;

void					apply_window_scale(t_engine *eng);
void					init_engine_values(t_engine *eng);

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
