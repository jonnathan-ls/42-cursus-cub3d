/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"
#include <MLX42/MLX42.h>

/**
 * @brief Finds first inactive projectile slot in pool.
 *
 * @param weapon Weapon system containing projectile array.
 * @return Index of free projectile, or -1 if none available.
 */
static int	find_free_projectile(t_weapon_system *weapon)
{
	int	i;

	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (weapon->projectiles[i].active == 0)
			return (i);
		i = i + 1;
	}
	return (-1);
}

/**
 * @brief Creates and activates a projectile from player position.
 *
 * @param eng Engine structure containing player and weapon data.
 * @param index Index in projectile array to activate.
 */
static void	create_projectile(t_engine *eng, int index)
{
	double	offset;

	offset = 0.5;
	eng->weapon.projectiles[index].active = 1;
	eng->weapon.projectiles[index].x = eng->player.pos_x;
	eng->weapon.projectiles[index].x += eng->player.dir_x * offset;
	eng->weapon.projectiles[index].y = eng->player.pos_y;
	eng->weapon.projectiles[index].y += eng->player.dir_y * offset;
	eng->weapon.projectiles[index].dir_x = eng->player.dir_x;
	eng->weapon.projectiles[index].dir_y = eng->player.dir_y;
	eng->weapon.projectiles[index].current_frame = 0;
	eng->weapon.projectiles[index].anim_timer = 0.0;
}

/**
 * @brief Handles weapon shooting on mouse click with cooldown.
 *
 * @param param Engine structure cast from void pointer.
 */
void	handle_weapon_shoot(void *param)
{
	t_engine	*eng;
	int			proj_index;

	eng = (t_engine *)param;
	if (!eng)
		return ;
	if (eng->weapon.shoot_cooldown > 0.0)
		return ;
	if (!mlx_is_mouse_down(eng->mlx, MLX_MOUSE_BUTTON_LEFT))
		return ;
	proj_index = find_free_projectile(&eng->weapon);
	if (proj_index < 0)
		return ;
	create_projectile(eng, proj_index);
	eng->weapon.shoot_cooldown = 0.2;
}
