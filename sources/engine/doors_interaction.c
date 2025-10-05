/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_interaction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/04 22:23:50 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"
#include "player.h"
#include <MLX42/MLX42.h>

static void	toggle_door_by_index(t_engine *eng, int door_index)
{
	int	is_door_open;

	if (door_index >= 0 && door_index < eng->doors.count)
	{
		is_door_open = !eng->doors.list[door_index].is_open;
		eng->doors.list[door_index].is_open = is_door_open;
	}
}

void	handle_door_interaction(t_engine *eng)
{
	int	nearest_door_index;

	if (!can_interact_with_door(eng))
		return ;
	nearest_door_index = find_nearest_door_index(eng);
	toggle_door_by_index(eng, nearest_door_index);
}

int	can_interact_with_door(t_engine *eng)
{
	if (!eng || !mlx_is_key_down(eng->mlx, MLX_KEY_E))
		return (0);
	return (check_key_press_cooldown());
}

int	door_is_open(t_engine *eng, int x, int y)
{
	int	i;

	if (!eng || !eng->doors.list || eng->doors.count == 0)
		return (0);
	i = 0;
	while (i < eng->doors.count)
	{
		if (eng->doors.list[i].x == x && eng->doors.list[i].y == y)
			return (eng->doors.list[i].is_open);
		i = i + 1;
	}
	return (0);
}
