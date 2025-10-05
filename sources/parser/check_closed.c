/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:56 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 22:23:50 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

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

static char	**alloc_visited(t_map *m)
{
	char	**v;
	int		y;

	v = (char **)calloc(m->height, sizeof(char *));
	if (!v)
		return (NULL);
	y = 0;
	while (y < m->height)
	{
		v[y] = (char *)calloc(m->width, sizeof(char));
		if (!v[y])
		{
			free_visited(v, y);
			return (NULL);
		}
		y = y + 1;
	}
	return (v);
}

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
