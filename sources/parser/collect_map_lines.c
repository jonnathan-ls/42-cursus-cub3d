/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:13 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/04 23:07:43 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static char	**grow_lines(char **old, int old_count)
{
	char	**new_arr;
	int		i;

	new_arr = (char **)ft_calloc(old_count + 2, sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < old_count)
	{
		new_arr[i] = old[i];
		i = i + 1;
	}
	free(old);
	return (new_arr);
}

static void	strip_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	append_line(char ***lines, int *count, char *line)
{
	char	**tmp;

	strip_newline(line);
	tmp = grow_lines(*lines, *count);
	if (!tmp)
	{
		free(line);
		return (parser_error("malloc failure"));
	}
	*lines = tmp;
	(*lines)[(*count)++] = line;
	return (0);
}

static int	read_more(int fd, char ***lines, int *count)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (0);
		if (line[0] == '\n')
		{
			free(line);
			return (0);
		}
		if (append_line(lines, count, line) < 0)
			return (-1);
	}
	return (0);
}

int	collect_map(int fd, char *first_map_line, t_map *map_raw)
{
	char	**lines;
	int		count;

	count = 0;
	lines = grow_lines(NULL, 0);
	if (!lines)
		return (parser_error("malloc failure"));
	strip_newline(first_map_line);
	lines[count++] = first_map_line;
	if (read_more(fd, &lines, &count) < 0)
		return (-1);
	if (count == 0)
	{
		free(lines);
		return (parser_error("empty map"));
	}
	map_raw->grid = lines;
	map_raw->height = count;
	map_raw->width = 0;
	return (0);
}
