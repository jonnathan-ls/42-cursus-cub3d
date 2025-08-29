/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 09:01:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 09:01:51 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int	is_empty_line(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		if (!(s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\v'
				|| s[i] == '\f'))
			return (0);
		i++;
	}
	return (1);
}

static int	handle_texture_line(char *id, t_config *cfg)
{
	char	*rest;

	rest = id + 2;
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if (id[0] == 'N' && id[1] == 'O' && !cfg->textures.no_path)
		return (parse_texture(rest, &cfg->textures.no_path));
	if (id[0] == 'S' && id[1] == 'O' && !cfg->textures.so_path)
		return (parse_texture(rest, &cfg->textures.so_path));
	if (id[0] == 'W' && id[1] == 'E' && !cfg->textures.we_path)
		return (parse_texture(rest, &cfg->textures.we_path));
	if (id[0] == 'E' && id[1] == 'A' && !cfg->textures.ea_path)
		return (parse_texture(rest, &cfg->textures.ea_path));
	return (parser_error("duplicate texture identifier"));
}

static int	handle_color_line(char *id, t_config *cfg)
{
	char	*rest;

	if (!(id[1] == ' ' || id[1] == '\t'))
		return (parser_error("invalid texture line format"));
	rest = id + 1;
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if (id[0] == 'F')
	{
		if (cfg->floor_color.rgba != -1)
			return (parser_error("duplicate color identifier"));
		if (parse_color(rest, &cfg->floor_color) < 0)
			return (-1);
	}
	else if (id[0] == 'C')
	{
		if (cfg->ceiling_color.rgba != -1)
			return (parser_error("duplicate color identifier"));
		if (parse_color(rest, &cfg->ceiling_color) < 0)
			return (-1);
	}
	return (0);
}

int	parse_header_line(char *line, t_config *cfg, int *count_done)
{
	char	*id;

	if (!line || !cfg)
		return (parser_error("incomplete header set"));
	id = line;
	while (*id == ' ' || *id == '\t')
		id++;
	if (*id == '\n' || *id == '\0')
		return (0);
	if ((id[0] == 'N' && id[1] == 'O') || (id[0] == 'S' && id[1] == 'O')
		|| (id[0] == 'W' && id[1] == 'E') || (id[0] == 'E' && id[1] == 'A'))
	{
		if (handle_texture_line(id, cfg) < 0)
			return (-1);
		(*count_done)++;
		return (0);
	}
	if (id[0] == 'F' || id[0] == 'C')
	{
		if (handle_color_line(id, cfg) < 0)
			return (-1);
		(*count_done)++;
		return (0);
	}
	return (parser_error("invalid texture line format"));
}
