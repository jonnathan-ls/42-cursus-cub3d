/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/20 16:05:52 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "engine.h"

int		ft_minimap_init(t_engine *eng);
void	ft_minimap_toggle(t_engine *eng, int pressed, int *key_prev);
void	ft_minimap_zoom(t_engine *eng, int zoom_in, int zoom_out);
void	ft_minimap_draw(t_engine *eng);
void	ft_minimap_render_cells(t_engine *eng, int final_scale);
void	ft_minimap_draw_cell_block(
			t_engine *eng, int cell_x, int cell_y, int scale);

#endif
