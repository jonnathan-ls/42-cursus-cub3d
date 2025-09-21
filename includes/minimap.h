/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/21 16:33:20 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "engine.h"

void	ft_minimap_init(t_engine *eng);
void	ft_minimap_draw(t_engine *eng);
void	ft_handle_minimap_zoom(t_engine *eng);
void	ft_handle_minimap_toggle(t_engine *eng);
int		ft_minimap_init_exploration(t_engine *eng);
void	ft_minimap_update_exploration(t_engine *eng);
void	ft_minimap_render_cells(t_engine *eng, int final_scale);
void	ft_minimap_draw_cell_block(
			t_engine *eng, int cell_x, int cell_y, int scale);

#endif