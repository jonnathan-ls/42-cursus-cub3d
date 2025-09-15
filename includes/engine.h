/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:47:56 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 19:44:53 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "parser.h"
# include "player.h"
# include <MLX42/MLX42.h>
# include <stdint.h>

typedef struct s_player	t_player;

typedef struct s_textures_bundle
{
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*west;
	mlx_texture_t		*east;
}						t_textures_bundle;

typedef struct s_image
{
	mlx_image_t			*frame;
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
}						t_engine;

int						ft_engine_init(t_engine *eng, t_config *cfg);
void					ft_engine_destroy(t_engine *eng);
void					ft_engine_close(void *param);

void					ft_engine_loop(t_engine *eng);
int						ft_load_textures(t_engine *eng, t_config *cfg);

#endif
