/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/20 22:12:18 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "player.h"
#include <math.h>

static void	toggle_door_by_index(t_engine *eng, int door_index)
{
	int	is_open;

	if (door_index >= 0 && door_index < eng->doors.count)
	{
		is_open = !eng->doors.doors[door_index].is_open;
		eng->doors.doors[door_index].is_open = is_open;
	}
}

void	ft_handle_door_interaction(t_engine *eng)
{
	int	nearest_door_index;

	if (!ft_can_interact_with_door(eng))
		return ;
	nearest_door_index = ft_find_nearest_door_index(eng);
	toggle_door_by_index(eng, nearest_door_index);
}
