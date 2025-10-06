/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 23:48:36 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

/**
 * Frees string and sets pointer to NULL.
 * @param s Pointer to string pointer.
 */
static void	free_str(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

/**
 * Frees map grid 2D array.
 * @param cfg Pointer to configuration structure.
 */
static void	free_map_grid(t_config *cfg)
{
	int	i;

	i = 0;
	while (cfg->map.grid && i < cfg->map.height)
	{
		free(cfg->map.grid[i]);
		i++;
	}
	if (cfg->map.grid)
	{
		free(cfg->map.grid);
		cfg->map.grid = NULL;
	}
}

/**
 * Frees all allocated memory in configuration.
 * @param cfg Pointer to configuration structure.
 */
void	free_config(t_config *cfg)
{
	if (!cfg)
		return ;
	free_str(&cfg->textures.no_path);
	free_str(&cfg->textures.so_path);
	free_str(&cfg->textures.we_path);
	free_str(&cfg->textures.ea_path);
	free_str(&cfg->textures.floor_path);
	free_str(&cfg->textures.ceiling_path);
	free_str(&cfg->textures.menu_path);
	free_map_grid(cfg);
}
