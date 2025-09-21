/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:46:44 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/21 10:58:45 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <MLX42/MLX42.h>

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
	if (eng->tex.door_closed)
		mlx_delete_texture(eng->tex.door_closed);
	eng->tex.north = NULL;
	eng->tex.south = NULL;
	eng->tex.west = NULL;
	eng->tex.east = NULL;
	eng->tex.door_closed = NULL;
}

int	ft_load_textures(t_engine *eng, t_config *cfg)
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
	eng->tex.door_closed = mlx_load_png("./maps/textures/door_closed.png");
	if (!eng->tex.door_closed)
		return (cleanup_partial_textures(eng), -1);
	return (0);
}
