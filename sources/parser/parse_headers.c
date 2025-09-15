/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:28 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 18:49:05 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <unistd.h>

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

static int	process_header_line(char *line, t_config *cfg, int *count)
{
	int	parse_result;

	if (is_empty_line(line))
		return (0);
	parse_result = parse_header_line(line, cfg, count);
	if (parse_result == -2)
		return (-2);
	if (parse_result < 0)
		return (-1);
	return (0);
}

static int	read_header_block(int fd, t_config *cfg, char **first_map_line)
{
	char	*line;
	int		count;
	int		result;

	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		result = process_header_line(line, cfg, &count);
		if (result == -2)
		{
			*first_map_line = line;
			return (0);
		}
		if (result < 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (fetch_first_map_line(fd, first_map_line));
}

static int	validate_headers_complete(t_config *cfg)
{
	if (!cfg->textures.no_path)
		return (parser_error("missing NO texture"));
	if (!cfg->textures.so_path)
		return (parser_error("missing SO texture"));
	if (!cfg->textures.we_path)
		return (parser_error("missing WE texture"));
	if (!cfg->textures.ea_path)
		return (parser_error("missing EA texture"));
	if (cfg->floor_color.rgba == -1)
		return (parser_error("missing F color"));
	if (cfg->ceiling_color.rgba == -1)
		return (parser_error("missing C color"));
	return (0);
}

int	parse_headers(int fd, t_config *cfg, char **line_after_headers)
{
	if (read_header_block(fd, cfg, line_after_headers) < 0)
		return (-1);
	if (validate_headers_complete(cfg) < 0)
		return (-1);
	return (0);
}
