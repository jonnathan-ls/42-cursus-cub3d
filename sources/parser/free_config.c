/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:52 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 08:41:43 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>

static void	free_str(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

void	free_config(t_config *cfg)
{
	int	i;

	if (!cfg)
		return ;
	free_str(&cfg->textures.no_path);
	free_str(&cfg->textures.so_path);
	free_str(&cfg->textures.we_path);
	free_str(&cfg->textures.ea_path);
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
