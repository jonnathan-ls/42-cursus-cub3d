/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_interact_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 13:48:58 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"

void	handle_coin_pickup(t_engine *eng, t_sprite *sprite)
{
	sprite->collected = 1;
	eng->player.game_over = 2;
}
