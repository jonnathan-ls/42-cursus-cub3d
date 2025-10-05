/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 18:30:18 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <MLX42/MLX42.h>

typedef struct s_sprite
{
	double			x;
	double			y;
	double			distance;
	int				type_index;
	int				sprite_type;
	int				collected;
	int				frame_count;
	int				current_frame;
	double			anim_timer;
	int				health;
	int				is_dying;
	double			death_timer;
	double			move_dir_x;
	double			move_dir_y;
	double			move_timer;
	double			move_speed;
}					t_sprite;

typedef struct s_sprite_manager
{
	t_sprite			*list;
	int					count;
	int					*order;
	mlx_texture_t		**textures;
	int					*frame_counts;
	int					*frame_widths;
	int					*sprite_types;
	int					texture_count;
	t_sprite_config		*configs;
}					t_sprite_manager;

typedef struct s_sprite_render
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
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
