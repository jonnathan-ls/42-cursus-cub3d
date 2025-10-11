/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:07 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/11 17:03:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shared.h"

/**
 * @brief Computes the maximum width of all lines in the map.
 *
 * Iterates through all map lines to find the longest line length,
 * which will be used to normalize all rows to the same width.
 *
 * @param lines Array of strings representing map lines.
 * @param height Number of lines in the map.
 * @return Maximum width found.
 */
static int	compute_max_width(char **lines, int height)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < height)
	{
		len = (int)ft_strlen(lines[i]);
		if (len > max)
			max = len;
		i = i + 1;
	}
	return (max);
}

/**
 * @brief Allocates a row filled with spaces for map normalization.
 *
 * Creates a new string of specified width using mm_alloc (garbage collector),
 * fills it with space characters, and null-terminates it.
 *
 * @param width Desired width of the row.
 * @return Allocated string on success, NULL on failure.
 */
static char	*alloc_row(int width)
{
	char	*row;
	int		j;

	row = (char *)mm_alloc(width + 1, sizeof(char));
	if (!row)
		return (NULL);
	j = 0;
	while (j < width)
	{
		row[j] = ' ';
		j = j + 1;
	}
	row[width] = '\0';
	return (row);
}

/**
 * @brief Copies source line into destination, removing trailing newline.
 *
 * Strips the trailing newline character if present, then copies the
 * source content into the destination, respecting the width limit.
 *
 * @param src Source line to copy.
 * @param dst Destination buffer (already allocated with spaces).
 * @param width Maximum width to copy.
 * @return Always returns 0.
 */
static int	copy_line(char *src, char *dst, int width)
{
	int	len;

	len = (int)ft_strlen(src);
	if (len > 0 && src[len - 1] == '\n')
	{
		src[len - 1] = '\0';
		len--;
	}
	if (len > width)
		len = width;
	ft_memcpy(dst, src, len);
	return (0);
}

/**
 * @brief Allocates a new grid array for the normalized map.
 *
 * Creates an array of string pointers with space for all map rows
 * plus a NULL terminator.
 *
 * @param map Map structure containing height information.
 * @param out Pointer to store the allocated grid.
 * @return 0 on success, -1 on failure.
 */
static int	alloc_new_grid(t_map *map, char ***out)
{
	*out = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!*out)
		return (parser_error("malloc failure"));
	return (0);
}

/**
 * @brief Normalizes all map rows to have equal width.
 *
 * Computes the maximum width among all rows, allocates a new grid
 * where each row has this width (padding with spaces), copies the
 * original content, and replaces the old grid.
 *
 * @param map Map structure to normalize.
 * @return 0 on success, -1 on failure.
 */
int	normalize_map(t_map *map)
{
	char	**new_grid;
	int		i;

	if (!map || !map->grid || map->height <= 0)
		return (parser_error("empty map"));
	map->width = compute_max_width(map->grid, map->height);
	if (alloc_new_grid(map, &new_grid) < 0)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = alloc_row(map->width);
		if (!new_grid[i])
			return (parser_error("malloc failure"));
		copy_line(map->grid[i], new_grid[i], map->width);
		free(map->grid[i]);
		i = i + 1;
	}
	free(map->grid);
	map->grid = new_grid;
	return (0);
}
