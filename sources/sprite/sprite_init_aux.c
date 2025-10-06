/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

/**
 * @brief Initializes sprite manager structure to default values.
 *
 * Sets all sprite system pointers to NULL and counters to zero.
 *
 * @param eng Engine structure to initialize.
 */
void	init_sprite_values(t_engine *eng)
{
	eng->sprites.list = NULL;
	eng->sprites.count = 0;
	eng->sprites.order = NULL;
	eng->sprites.texture_count = 0;
	eng->sprite_chars = NULL;
}

/**
 * @brief Iterates through sprite configurations to set up each type.
 *
 * Calls setup_sprite_type for each configuration in the array.
 *
 * @param eng Engine structure to configure.
 * @param configs Array of sprite configurations.
 * @param count Number of configurations to process.
 */
void	setup_sprite_loop(t_engine *eng, t_sprite_config *configs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		setup_sprite_type(eng, configs, i);
		i = i + 1;
	}
}
