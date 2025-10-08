/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:50:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/07 22:46:26 by jlacerda         ###   ########.fr       */
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
 * @brief Finds the index with maximum distance in a range.
 *
 * @param eng Engine structure containing sprite list and order.
 * @param start Starting index of search range.
 * @param end Ending index of search range.
 * @return Index of the sprite with maximum distance.
 */
static int	find_max_index(t_engine *eng, int start, int end)
{
	int		max_idx;
	int		current_idx;
	double	max_dist;
	int		i;

	max_idx = start;
	max_dist = eng->sprites.list[eng->sprites.order[start]].distance;
	i = start + 1;
	while (i <= end)
	{
		current_idx = eng->sprites.order[i];
		if (eng->sprites.list[current_idx].distance > max_dist)
		{
			max_dist = eng->sprites.list[current_idx].distance;
			max_idx = i;
		}
		i = i + 1;
	}
	return (max_idx);
}

/**
 * @brief Sorts sprites by distance using selection sort algorithm.
 *
 * @param eng Engine structure containing sprite list and order array.
 */
static void	sort_by_distance(t_engine *eng)
{
	int	i;
	int	max_idx;
	int	last;

	last = eng->sprites.count - 1;
	i = 0;
	while (i < last)
	{
		max_idx = find_max_index(eng, i, last);
		if (max_idx != i)
			swap_order(eng->sprites.order, i, max_idx);
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
