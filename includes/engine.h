/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:47:56 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 16:57:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "parser.h"
# include "player.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

typedef struct s_player	t_player;

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

typedef struct s_image
{
	mlx_image_t			*frame;
	mlx_image_t			*cursor;
}						t_image;

typedef struct s_engine
{
	mlx_t				*mlx;
	t_player			player;
	t_textures_bundle	tex;
	char				**map;
	int					map_w;
	int					map_h;
	int					win_w;
	int					win_h;
	uint32_t			ceil_color;
	uint32_t			floor_color;
	t_image				img;
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
}						t_engine;

void					config_init_engine(t_engine *eng);

int						config_engine(t_engine *eng, t_config *cfg);
void					engine_destroy(t_engine *eng);
void					engine_close(void *param);
int						check_key_press_cooldown(void);
void					set_player_dir(t_engine *eng, char dir);
void					draw_circle(uint32_t *pixels, int cx, int cy,
							int radius);

void					engine_loop(t_engine *eng);
int						config_textures(t_engine *eng, t_config *cfg);

void					handle_menu_view(t_engine *eng);
void					draw_menu_overlay(t_engine *eng);
int						config_doors(t_engine *eng);
void					handle_door_interaction(t_engine *eng);
int						door_is_open(t_engine *eng, int x, int y);
int						can_interact_with_door(t_engine *eng);
int						find_nearest_door_index(t_engine *eng);
void					handle_door_updates(t_engine *eng);
int						get_door_texture_offset(
							t_engine *eng, int map_x, int map_y);

#endif
