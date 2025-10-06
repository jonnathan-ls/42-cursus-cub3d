/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 19:16:30 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include <math.h>

double	calc_euclidean_dist(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

int	is_in_radius(double x1, double y1, double x2, double y2)
{
	double	dist;
	double	radius;

	radius = 1.75;
	dist = calc_euclidean_dist(x1, y1, x2, y2);
	return (dist <= radius);
}

double	clamp_double(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}
