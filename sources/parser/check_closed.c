/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:56 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 00:09:57 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

/**
 * @brief Frees the visited matrix used during flood fill.
 *
 * Iterates through each row of the visited matrix, frees the row,
 * then frees the matrix pointer itself.
 *
 * @param v Visited matrix to free.
 * @param h Number of rows in the matrix.
 */
static void	free_visited(char **v, int h)
{
	int	i;

	i = 0;
	if (!v)
		return ;
	while (i < h)
	{
		free(v[i]);
		i = i + 1;
	}
	free(v);
}

/**
 * @brief Recursively flood-fills the map to check enclosure.
 *
 * Performs a recursive traversal starting from (x, y), ensuring that
 * all reachable floor cells are surrounded by walls. Returns error if
 * a space or boundary is reached.
 *
 * @param m Map structure containing the grid.
 * @param y Y coordinate of the current cell.
 * @param x X coordinate of the current cell.
 * @param v Visited matrix to track processed cells.
 * @return 0 if enclosed, -1 if open boundary detected.
 */
static int	flood(t_map *m, int y, int x, char **v)
{
	if (y < 0 || x < 0 || y >= m->height || x >= m->width)
		return (parser_error("map not closed"));
	if (m->grid[y][x] == ' ')
		return (parser_error("map not closed"));
	if (m->grid[y][x] == '1' || v[y][x])
		return (0);
	v[y][x] = 1;
	if (flood(m, y + 1, x, v) < 0 || flood(m, y - 1, x, v) < 0
		|| flood(m, y, x + 1, v) < 0 || flood(m, y, x - 1, v) < 0)
		return (-1);
	return (0);
}

/**
 * @brief Allocates a visited matrix for flood fill tracking.
 *
 * Creates a 2D matrix of chars with dimensions matching the map,
 * initializing all values to 0 (unvisited).
 *
 * @param m Map structure containing dimensions.
 * @return Allocated visited matrix on success, NULL on failure.
 */
static char	**alloc_visited(t_map *m)
{
	char	**v;
	int		y;

	v = (char **)ft_calloc(m->height, sizeof(char *));
	if (!v)
		return (NULL);
	y = 0;
	while (y < m->height)
	{
		v[y] = (char *)ft_calloc(m->width, sizeof(char));
		if (!v[y])
		{
			free_visited(v, y);
			return (NULL);
		}
		y = y + 1;
	}
	return (v);
}

/**
 * @brief Processes all floor cells to verify map enclosure.
 *
 * Iterates through all cells in the map grid. For each unvisited floor
 * cell ('0'), initiates a flood fill to check if it is enclosed.
 *
 * @param map Map structure containing the grid.
 * @param vis Visited matrix to track processed cells.
 * @return 0 if all floor cells are enclosed, -1 otherwise.
 */
static int	process_cells(t_map *map, char **vis)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0' && !vis[y][x])
			{
				if (flood(map, y, x, vis) < 0)
					return (-1);
			}
			x = x + 1;
		}
		y = y + 1;
	}
	return (0);
}

/**
 * @brief Verifies that the map is fully enclosed by walls.
 *
 * Allocates a visited matrix, processes all floor cells with flood fill
 * to ensure they are surrounded by walls, then frees the visited matrix.
 *
 * @param map Map structure to validate.
 * @return 0 if map is properly enclosed, -1 otherwise.
 */
int	check_map_closed(t_map *map)
{
	char	**visited;

	if (!map || !map->grid)
		return (parser_error("empty map"));
	visited = alloc_visited(map);
	if (!visited)
		return (parser_error("malloc failure"));
	if (process_cells(map, visited) < 0)
	{
		free_visited(visited, map->height);
		return (-1);
	}
	free_visited(visited, map->height);
	return (0);
}
