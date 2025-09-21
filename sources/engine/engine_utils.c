/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/21 16:38:07 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42/MLX42.h>

int	check_key_press_cooldown(void)
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
