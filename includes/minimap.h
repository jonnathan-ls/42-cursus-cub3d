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

/**
 * @struct s_minimap
 * @brief Minimap rendering state and properties.
 */
typedef struct s_minimap
{
	int	final_scale;	/**< Computed scale factor for rendering. */
	int	left;			/**< Left screen position of minimap. */
	int	top;			/**< Top screen position of minimap. */
	int	size;			/**< Minimap size in pixels. */
	int	block_cell_x;	/**< Current map cell X being rendered. */
	int	block_cell_y;	/**< Current map cell Y being rendered. */
	int	block_start_x;	/**< Block start screen X coordinate. */
	int	block_start_y;	/**< Block start screen Y coordinate. */
	int	block_color;	/**< Color of current block being drawn. */
}	t_minimap;

/**
 * @struct s_minimap_projection
 * @brief Minimap pixel to map tile projection.
 */
typedef struct s_minimap_projection
{
	int	tile_x;	/**< Projected map tile X coordinate. */
	int	tile_y;	/**< Projected map tile Y coordinate. */
}	t_minimap_projection;

/**
 * @struct s_minimap_player_params
 * @brief Player indicator rendering parameters.
 */
typedef struct s_minimap_player_params
{
	double	dx_screen;	/**< Player direction X in screen space. */
	double	dy_screen;	/**< Player direction Y in screen space. */
	double	perp_x;		/**< Perpendicular vector X for arrow width. */
	double	perp_y;		/**< Perpendicular vector Y for arrow width. */
	int		length;		/**< Direction arrow length in pixels. */
	int		half_width;	/**< Half width of direction arrow. */
}	t_minimap_player_params;

/**
 * @struct s_minimap_draw_info
 * @brief Minimap positioning and sizing information.
 */
typedef struct s_minimap_draw_info
{
	int	left;	/**< Left screen position. */
	int	top;	/**< Top screen position. */
	int	size;	/**< Minimap size in pixels. */
}	t_minimap_draw_info;

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
void		draw_minimap_frame(t_engine *eng, t_minimap_draw_info *info);
void		draw_minimap_background(t_engine *eng, t_minimap *map);
void		draw_minimap_player(t_engine *eng, t_minimap_draw_info *info);
void		compute_minimap_pixel_color(t_engine *eng, t_minimap *map,
				int pixel_x, int pixel_y);

#endif