/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:07 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 23:07:43 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

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

static char	*alloc_row(int width)
{
	char	*row;
	int		j;

	row = (char *)malloc(width + 1);
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

static int	alloc_new_grid(t_map *map, char ***out)
{
	*out = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!*out)
		return (parser_error("malloc failure"));
	return (0);
}

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
