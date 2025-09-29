/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 22:19:28 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "engine.h"

void	draw_minimap(t_engine *eng);
void	config_minimap(t_engine *eng);
void	handle_minimap_zoom(t_engine *eng);
void	handle_minimap_view(t_engine *eng);
void	handle_minimap_exploration(t_engine *eng);
int		initialize_minimap_exploration(t_engine *eng);
void	render_minimap_cells(t_engine *eng, int final_scale);
void	draw_minimap_cell_block(
			t_engine *eng, int cell_x, int cell_y, int scale);

#endif