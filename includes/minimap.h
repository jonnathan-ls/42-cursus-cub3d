/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/01 01:06:42 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "engine.h"

typedef struct s_minimap
{
	int	final_scale;
	int	left;
	int	top;
	int	size;
	int	block_cell_x;
	int	block_cell_y;
	int	block_start_x;
	int	block_start_y;
	int	block_color;
}	t_minimap;

typedef struct s_minimap_projection
{
	int	tile_x;
	int	tile_y;
}	t_minimap_projection;

typedef struct s_minimap_player_params
{
	double	dx_screen;
	double	dy_screen;
	double	perp_x;
	double	perp_y;
	int		length;
	int		half_width;
}	t_minimap_player_params;

void		draw_minimap(t_engine *eng);
void		draw_full_map(t_engine *eng);
void		configure_minimap(t_engine *eng);
void		handle_minimap_zoom(t_engine *eng);
void		handle_minimap_view(t_engine *eng);
void		handle_fullmap_view(t_engine *eng);
void		handle_minimap_exploration(t_engine *eng);
int			initialize_minimap_exploration(t_engine *eng);
void		render_minimap_cells(t_engine *eng, t_minimap *map);
void		render_minimap_pixels(t_engine *eng, t_minimap *map);
void		draw_minimap_frame(t_engine *eng, int left, int top,
				int square_size);
void		draw_minimap_background(t_engine *eng, t_minimap *map);
void		draw_minimap_player(t_engine *eng,
				int square_left, int square_top, int square_size);
void		compute_minimap_pixel_color(t_engine *eng, t_minimap *map,
				int pixel_x, int pixel_y);

#endif