/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/11 17:20:38 by jlacerda         ###   ########.fr       */
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
}
