/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:50:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"

/**
 * @brief Calculates distance from each sprite to the player.
 *
 * @param eng Engine structure containing sprites and player position.
 */
static void	calculate_distances(t_engine *eng)
{
	int		i;
	double	dist;

	i = 0;
	while (i < eng->sprites.count)
	{
		dist = calc_euclidean_dist(eng->sprites.list[i].x,
				eng->sprites.list[i].y,
				eng->player.pos_x, eng->player.pos_y);
		eng->sprites.list[i].distance = dist * dist;
		eng->sprites.order[i] = i;
		i = i + 1;
	}
}

/**
 * @brief Swaps two elements in the sprite order array.
 *
 * @param order Sprite order array.
 * @param i First index.
 * @param j Second index.
 */
static void	swap_order(int *order, int i, int j)
{
	int	temp;

	temp = order[i];
	order[i] = order[j];
	order[j] = temp;
}

/**
 * @brief Sorts sprites by distance from player (far to near).
 *
 * @param eng Engine structure containing sprite list and order array.
 */
static void	sort_by_distance(t_engine *eng)
{
	int	i;
	int	j;
	int	idx_i;
	int	idx_j;

	i = 0;
	while (i < eng->sprites.count - 1)
	{
		j = i + 1;
		while (j < eng->sprites.count)
		{
			idx_i = eng->sprites.order[i];
			idx_j = eng->sprites.order[j];
			if (eng->sprites.list[idx_i].distance
				< eng->sprites.list[idx_j].distance)
				swap_order(eng->sprites.order, i, j);
			j = j + 1;
		}
		i = i + 1;
	}
}

/**
 * @brief Sorts all sprites by distance for proper depth rendering.
 *
 * @param param Engine structure cast from void pointer.
 */
void	sprite_sorting(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng || !eng->sprites.list || eng->sprites.count == 0)
		return ;
	calculate_distances(eng);
	sort_by_distance(eng);
}
