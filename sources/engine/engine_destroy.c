/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:53:05 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/11 17:28:33 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "engine.h"
#include "sprite.h"

static void	delete_textures(t_engine *eng)
{
	if (eng->tex.north)
		mlx_delete_texture(eng->tex.north);
	if (eng->tex.south)
		mlx_delete_texture(eng->tex.south);
	if (eng->tex.west)
		mlx_delete_texture(eng->tex.west);
	if (eng->tex.east)
		mlx_delete_texture(eng->tex.east);
	if (eng->tex.door)
		mlx_delete_texture(eng->tex.door);
	if (eng->tex.floor)
		mlx_delete_texture(eng->tex.floor);
	if (eng->tex.ceiling)
		mlx_delete_texture(eng->tex.ceiling);
	if (eng->tex.menu)
		mlx_delete_texture(eng->tex.menu);
	if (eng->tex.start)
		mlx_delete_texture(eng->tex.start);
	if (eng->tex.win)
		mlx_delete_texture(eng->tex.win);
	if (eng->tex.lose)
		mlx_delete_texture(eng->tex.lose);
}

/**
 * Cleans up and frees all engine resources.
 * @param eng Pointer to engine structure.
 */
void	destroy_engine(t_engine *eng)
{
	if (!eng)
		return ;
	if (eng->mlx)
		mlx_set_cursor_mode(eng->mlx, MLX_MOUSE_NORMAL);
	if (eng->mlx && eng->frame)
		mlx_delete_image(eng->mlx, eng->frame);
	if (eng->mlx && eng->cursor)
		mlx_delete_image(eng->mlx, eng->cursor);
	free_sprites(eng);
	delete_textures(eng);
	mm_garbage_collector();
	free_weapon_system(eng);
	if (eng->mlx)
		mlx_terminate(eng->mlx);
}
