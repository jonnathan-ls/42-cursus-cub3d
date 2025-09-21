/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/20 22:27:44 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <MLX42/MLX42.h>
#include <math.h>

int	ft_is_door_at(t_engine *eng, int x, int y)
{
	int	i;

	if (!eng || !eng->doors.doors)
		return (0);
	i = 0;
	while (i < eng->doors.count)
	{
		if (eng->doors.doors[i].x == x && eng->doors.doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_door_open_at(t_engine *eng, int x, int y)
{
	int	i;

	if (!eng || !eng->doors.doors || eng->doors.count == 0)
		return (0);
	i = 0;
	while (i < eng->doors.count)
	{
		if (eng->doors.doors[i].x == x && eng->doors.doors[i].y == y)
			return (eng->doors.doors[i].is_open);
		i++;
	}
	return (0);
}

static int	check_key_press_cooldown(void)
{
	static double	last_press_time = 0.0;
	double			current_time;
	double			cooldown;

	cooldown = 0.2;
	current_time = mlx_get_time();
	if (current_time - last_press_time < cooldown)
		return (0);
	last_press_time = current_time;
	return (1);
}

int	ft_can_interact_with_door(t_engine *eng)
{
	if (!eng || !mlx_is_key_down(eng->mlx, MLX_KEY_E))
		return (0);
	return (check_key_press_cooldown());
}
