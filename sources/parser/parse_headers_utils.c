/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 09:01:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 20:45:55 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shared.h"

static int	parse_single_texture(char *rest, char **dst, char *name)
{
	if (*dst)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" ", 1);
		return (parser_error("Duplicate texture"));
	}
	return (parse_texture(rest, dst));
}

static int	handle_texture_line(char *id, t_config *cfg)
{
	char	*rest;

	rest = id + 2;
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if (id[0] == 'N' && id[1] == 'O')
		return (parse_single_texture(rest, &cfg->textures.no_path, "NO"));
	if (id[0] == 'S' && id[1] == 'O')
		return (parse_single_texture(rest, &cfg->textures.so_path, "SO"));
	if (id[0] == 'W' && id[1] == 'E')
		return (parse_single_texture(rest, &cfg->textures.we_path, "WE"));
	if (id[0] == 'E' && id[1] == 'A')
		return (parse_single_texture(rest, &cfg->textures.ea_path, "EA"));
	if (id[0] == 'F' && id[1] == 'T')
		return (parse_single_texture(rest, &cfg->textures.floor_path, "FT"));
	if (id[0] == 'C' && id[1] == 'T')
		return (parse_single_texture(rest, &cfg->textures.ceiling_path, "CT"));
	if (id[0] == 'D' && id[1] == 'R')
		return (parse_single_texture(rest, &cfg->textures.door_path, "DR"));
	if (id[0] == 'M' && id[1] == 'N')
		return (parse_single_texture(rest, &cfg->textures.menu_path, "MN"));
	if (id[0] == 'S' && id[1] == 'P')
		return (parse_sprite_texture(rest, cfg));
	return (parser_error("invalid texture identifier"));
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

static int	parse_texture_paths(char *id, t_config *cfg, int *count_done)
{
	if ((id[0] == 'N' && id[1] == 'O') || (id[0] == 'S' && id[1] == 'O')
		|| (id[0] == 'W' && id[1] == 'E') || (id[0] == 'E' && id[1] == 'A'))
	{
		if (handle_texture_line(id, cfg) < 0)
			return (-1);
		(*count_done)++;
		return (0);
	}
	if ((id[0] == 'F' && id[1] == 'T') || (id[0] == 'C' && id[1] == 'T')
		|| (id[0] == 'D' && id[1] == 'R') || (id[0] == 'M' && id[1] == 'N')
		|| (id[0] == 'S' && id[1] == 'P'))
	{
		if (handle_texture_line(id, cfg) < 0)
			return (-1);
		return (0);
	}
	return (1);
}

int	parse_header_line(char *line, t_config *cfg, int *count_done)
{
	char	*id;
	int		result;

	if (!line || !cfg)
		return (parser_error("incomplete header set"));
	id = line;
	while (*id == ' ' || *id == '\t')
		id++;
	if (*id == '\n' || *id == '\0')
		return (0);
	result = parse_texture_paths(id, cfg, count_done);
	if (result != 1)
		return (result);
	if (id[0] == 'F' || id[0] == 'C')
	{
		if (handle_color_line(id, cfg) < 0)
			return (-1);
		(*count_done)++;
		return (0);
	}
	return (-2);
}
