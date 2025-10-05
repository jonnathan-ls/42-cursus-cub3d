/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:47:56 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 00:30:52 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "parser.h"
# include "player.h"
# include "sprite.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
	double	offset;
}			t_door;

typedef struct s_doors_manager
{
	t_door	*list;
	int		count;
}			t_doors_manager;

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
}						t_textures_bundle;

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
	t_sprite_manager	sprites;
	double				*z_buffer;
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
int						configure_doors(t_engine *eng);
void					handle_door_interaction(t_engine *eng);
int						door_is_open(t_engine *eng, int x, int y);
int						can_interact_with_door(t_engine *eng);
int						find_nearest_door_index(t_engine *eng);
void					handle_door_updates(t_engine *eng);
int						get_door_texture_offset(
							t_engine *eng, int map_x, int map_y);

#endif
