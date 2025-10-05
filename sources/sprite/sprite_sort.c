/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 01:50:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 01:53:53 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include <math.h>

static void	calculate_distances(t_engine *eng)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < eng->sprites.count)
	{
		dx = eng->sprites.list[i].x - eng->player.pos_x;
		dy = eng->sprites.list[i].y - eng->player.pos_y;
		eng->sprites.list[i].distance = dx * dx + dy * dy;
		eng->sprites.order[i] = i;
		i = i + 1;
	}
}

static void	swap_order(int *order, int i, int j)
{
	int	temp;

	temp = order[i];
	order[i] = order[j];
	order[j] = temp;
}

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

void	sprite_sorting(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng || !eng->sprites.list || eng->sprites.count == 0)
		return ;
	calculate_distances(eng);
	sort_by_distance(eng);
}
