/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:05 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/23 09:15:20 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"

void	ft_engine_destroy(t_engine *eng)
{
	if (!eng)
		return ;
	if (eng->mlx)
		mlx_set_cursor_mode(eng->mlx, MLX_MOUSE_NORMAL);
	if (eng->tex.north)
		mlx_delete_texture(eng->tex.north);
	if (eng->tex.south)
		mlx_delete_texture(eng->tex.south);
	if (eng->tex.west)
		mlx_delete_texture(eng->tex.west);
	if (eng->tex.east)
		mlx_delete_texture(eng->tex.east);
	if (eng->tex.door_closed)
		mlx_delete_texture(eng->tex.door_closed);
	if (eng->img.frame)
		mlx_delete_image(eng->mlx, eng->img.frame);
	if (eng->img.cursor)
		mlx_delete_image(eng->mlx, eng->img.cursor);
	if (eng->mlx)
		mlx_terminate(eng->mlx);
	mm_garbage_collector();
}
