/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:46:44 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/13 22:55:11 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "libft.h"
#include <MLX42/MLX42.h>

/**
 * Frees main wall textures on error.
 * @param eng Pointer to engine structure.
 */
static void	cleanup_wall_textures(t_engine *eng)
{
	if (eng->tex.north)
		mlx_delete_texture(eng->tex.north);
	eng->tex.north = NULL;
	if (eng->tex.south)
		mlx_delete_texture(eng->tex.south);
	eng->tex.south = NULL;
	if (eng->tex.west)
		mlx_delete_texture(eng->tex.west);
	eng->tex.west = NULL;
	if (eng->tex.east)
		mlx_delete_texture(eng->tex.east);
	eng->tex.east = NULL;
	if (eng->tex.door)
		mlx_delete_texture(eng->tex.door);
	eng->tex.door = NULL;
}

/**
 * Frees optional textures on error.
 * @param eng Pointer to engine structure.
 */
static void	cleanup_optional_textures(t_engine *eng)
{
	if (eng->tex.floor)
		mlx_delete_texture(eng->tex.floor);
	eng->tex.floor = NULL;
	if (eng->tex.ceiling)
		mlx_delete_texture(eng->tex.ceiling);
	eng->tex.ceiling = NULL;
	if (eng->tex.menu)
		mlx_delete_texture(eng->tex.menu);
	eng->tex.menu = NULL;
	if (eng->tex.start)
		mlx_delete_texture(eng->tex.start);
	eng->tex.start = NULL;
	if (eng->tex.win)
		mlx_delete_texture(eng->tex.win);
	eng->tex.win = NULL;
	if (eng->tex.lose)
		mlx_delete_texture(eng->tex.lose);
	eng->tex.lose = NULL;
}

/**
 * Frees partially loaded textures on error.
 * @param eng Pointer to engine structure.
 */
static void	cleanup_partial_textures(t_engine *eng)
{
	cleanup_wall_textures(eng);
	cleanup_optional_textures(eng);
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
		return (ft_putendl_fd("Error: Failed to load north texture", 2),
			cleanup_partial_textures(eng), -1);
	eng->tex.south = mlx_load_png(cfg->textures.so_path);
	if (!eng->tex.south)
		return (ft_putendl_fd("Error: Failed to load south texture", 2),
			cleanup_partial_textures(eng), -1);
	eng->tex.west = mlx_load_png(cfg->textures.we_path);
	if (!eng->tex.west)
		return (ft_putendl_fd("Error: Failed to load west texture", 2),
			cleanup_partial_textures(eng), -1);
	eng->tex.east = mlx_load_png(cfg->textures.ea_path);
	if (!eng->tex.east)
		return (ft_putendl_fd("Error: Failed to load east texture", 2),
			cleanup_partial_textures(eng), -1);
	if (cfg->textures.door_path)
		eng->tex.door = mlx_load_png(cfg->textures.door_path);
	return (load_optional_textures(eng, cfg));
}
