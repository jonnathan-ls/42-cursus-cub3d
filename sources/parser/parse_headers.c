/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:28 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 09:03:56 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <unistd.h>

static int	read_header_block(int fd, t_config *cfg, int *count)
{
	char	*line;

	while (*count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (parser_error("incomplete header set"));
		if (!is_empty_line(line))
		{
			if (parse_header_line(line, cfg, count) < 0)
			{
				free(line);
				return (-1);
			}
		}
		free(line);
	}
	return (0);
}

static int	fetch_first_map_line(int fd, char **out)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (parser_error("empty map"));
		if (!is_empty_line(line))
		{
			*out = line;
			return (0);
		}
		free(line);
	}
	return (0);
}

int	parse_headers(int fd, t_config *cfg, char **line_after_headers)
{
	int	count;

	count = 0;
	if (read_header_block(fd, cfg, &count) < 0)
		return (-1);
	if (fetch_first_map_line(fd, line_after_headers) < 0)
		return (-1);
	return (0);
}
