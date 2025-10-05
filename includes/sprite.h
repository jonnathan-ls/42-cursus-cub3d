/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 01:00:45 by jlacerda         ###   ########.fr       */
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
	mlx_texture_t	*texture;
	int				frame_count;
	int				current_frame;
	double			anim_timer;
}					t_sprite;

typedef struct s_sprite_manager
{
	t_sprite		*list;
	int				count;
	int				*order;
	mlx_texture_t	**textures;
	int				texture_count;
	int				frame_count;
	int				frame_width;
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

void				init_sprites(void *eng, char *sprite_path, int frames);
void				update_sprites(void *eng, double delta);
void				render_sprites(void *eng);
void				free_sprites(void *eng);
int					collect_sprites_from_map(void *eng);
int					count_sprites_in_map(t_engine *eng);
void				add_sprite(t_engine *eng, int *index, int pos_x,
						int pos_y);
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

#endif
