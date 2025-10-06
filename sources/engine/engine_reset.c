/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 00:21:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

/**
 * Resets engine dimension and flag values to zero.
 * @param eng Pointer to engine structure.
 */
static void	reset_engine_dimensions(t_engine *eng)
{
	eng->map_width = 0;
	eng->map_height = 0;
	eng->window_width = 0;
	eng->window_height = 0;
	eng->ceiling_color = 0;
	eng->floor_color = 0;
	eng->doors.count = 0;
	eng->ignore_doors = 0;
	eng->menu_toggle = 1;
	eng->menu_visible = 0;
}

/**
 * Resets all engine pointers to NULL.
 * @param eng Pointer to engine structure.
 */
static void	reset_engine_pointers(t_engine *eng)
{
	eng->mlx = NULL;
	eng->map = NULL;
	eng->frame = NULL;
	eng->cursor = NULL;
	eng->doors.list = NULL;
	eng->z_buffer = NULL;
}

/**
 * Resets all texture pointers to NULL.
 * @param eng Pointer to engine structure.
 */
static void	reset_engine_textures(t_engine *eng)
{
	eng->tex.door = NULL;
	eng->tex.menu = NULL;
	eng->tex.west = NULL;
	eng->tex.east = NULL;
	eng->tex.north = NULL;
	eng->tex.south = NULL;
	eng->tex.floor = NULL;
	eng->tex.ceiling = NULL;
}

/**
 * Initializes all engine values to default state.
 * @param eng Pointer to engine structure.
 */
void	reset_engine_values(t_engine *eng)
{
	reset_engine_dimensions(eng);
	reset_engine_pointers(eng);
	reset_engine_textures(eng);
}
