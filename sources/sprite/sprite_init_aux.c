/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 13:48:58 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

void	init_sprite_values(t_engine *eng)
{
	eng->sprites.list = NULL;
	eng->sprites.count = 0;
	eng->sprites.order = NULL;
	eng->sprites.texture_count = 0;
	eng->sprite_chars = NULL;
}

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
