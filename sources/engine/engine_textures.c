/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:46:44 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 01:21:54 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <MLX42/MLX42.h>

/**
 * Frees partially loaded textures on error.
 * @param eng Pointer to engine structure.
 */
static void	cleanup_partial_textures(t_engine *eng)
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

static int	load_optional_textures(t_engine *eng, t_config *cfg)
{
	if (cfg->textures.floor_path)
		eng->tex.floor = mlx_load_png(cfg->textures.floor_path);
	if (cfg->textures.ceiling_path)
		eng->tex.ceiling = mlx_load_png(cfg->textures.ceiling_path);
	if (cfg->textures.menu_path)
		eng->tex.menu = mlx_load_png(cfg->textures.menu_path);
	if (cfg->textures.start_path)
		eng->tex.start = mlx_load_png(cfg->textures.start_path);
	if (cfg->textures.win_path)
		eng->tex.win = mlx_load_png(cfg->textures.win_path);
	if (cfg->textures.lose_path)
		eng->tex.lose = mlx_load_png(cfg->textures.lose_path);
	return (0);
}

int	configure_textures(t_engine *eng, t_config *cfg)
{
	eng->tex.north = mlx_load_png(cfg->textures.no_path);
	if (!eng->tex.north)
		return (cleanup_partial_textures(eng), -1);
	eng->tex.south = mlx_load_png(cfg->textures.so_path);
	if (!eng->tex.south)
		return (cleanup_partial_textures(eng), -1);
	eng->tex.west = mlx_load_png(cfg->textures.we_path);
	if (!eng->tex.west)
		return (cleanup_partial_textures(eng), -1);
	eng->tex.east = mlx_load_png(cfg->textures.ea_path);
	if (!eng->tex.east)
		return (cleanup_partial_textures(eng), -1);
	if (cfg->textures.door_path)
		eng->tex.door = mlx_load_png(cfg->textures.door_path);
	return (load_optional_textures(eng, cfg));
}
