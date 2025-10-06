/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:37:26 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared.h"
#include "constants.h"
#include <math.h>

/**
 * Calculates Euclidean distance between two points.
 * @param x1 X coordinate of first point.
 * @param y1 Y coordinate of first point.
 * @param x2 X coordinate of second point.
 * @param y2 Y coordinate of second point.
 * @return Distance between points.
 */
double	calc_euclidean_dist(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

/**
 * Checks if two points are within door interaction radius.
 * @param x1 X coordinate of first point.
 * @param y1 Y coordinate of first point.
 * @param x2 X coordinate of second point.
 * @param y2 Y coordinate of second point.
 * @return 1 if within radius, 0 otherwise.
 */
int	is_in_radius(double x1, double y1, double x2, double y2)
{
	double	dist;

	dist = calc_euclidean_dist(x1, y1, x2, y2);
	return (dist <= DOOR_RADIUS);
}

/**
 * Restricts a double value within min and max bounds.
 * @param value Value to clamp.
 * @param min Minimum allowed value.
 * @param max Maximum allowed value.
 * @return Clamped value.
 */
double	clamp_double(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/**
 * Checks if an integer value is within bounds.
 * @param value Value to check.
 * @param min Minimum boundary (inclusive).
 * @param max Maximum boundary (exclusive).
 * @return 1 if within bounds, 0 otherwise.
 */
int	is_within_bounds(int value, int min, int max)
{
	if (value < min)
		return (0);
	if (value >= max)
		return (0);
	return (1);
}
