/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/23 22:17:29 by jlacerda         ###   ########.fr       */
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
 * Frees all sprite texture paths in configuration.
 * @param cfg Pointer to configuration structure.
 */
static void	free_sprite_textures(t_config *cfg)
{
	int	i;

	i = 0;
	if (!cfg || !cfg->textures.sprites)
		return ;
	while (i < cfg->textures.sprite_count)
	{
		free_str(&cfg->textures.sprites[i].path);
		i++;
	}
	cfg->textures.sprites = NULL;
	cfg->textures.sprite_count = 0;
}

/**
 * Frees all allocated memory in configuration.
 * NOTE: 
 * - map.grid is managed by garbage collector after normalize_map()
 * - sprites array is managed by garbage collector (mm_alloc)
 * - Only textures paths need manual free (from ft_strdup)
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
	free_str(&cfg->textures.start_path);
	free_str(&cfg->textures.win_path);
	free_str(&cfg->textures.lose_path);
	free_str(&cfg->textures.door_path);
	free_sprite_textures(cfg);
}
