/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:37 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/23 21:33:39 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <unistd.h>

static void	init_config(t_config *cfg)
{
	cfg->textures.no_path = NULL;
	cfg->textures.so_path = NULL;
	cfg->textures.we_path = NULL;
	cfg->textures.ea_path = NULL;
	cfg->textures.floor_path = NULL;
	cfg->textures.ceiling_path = NULL;
	cfg->floor_color.rgba = -1;
	cfg->ceiling_color.rgba = -1;
	cfg->map.grid = NULL;
	cfg->map.width = 0;
	cfg->map.height = 0;
	cfg->map.player_x = -1;
	cfg->map.player_y = -1;
	cfg->map.player_dir = 0;
}

static int	phase_open_and_headers(const char *path, t_config *cfg, int *fd,
		char **first_map_line)
{
	*first_map_line = NULL;
	if (validate_file_extension(path) < 0)
		return (-1);
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (parser_error("cannot open file"));
	if (parse_headers(*fd, cfg, first_map_line) < 0)
		return (-1);
	return (0);
}

static int	phase_map_read(int fd, char *first_map_line, t_config *cfg)
{
	if (collect_map(fd, first_map_line, &cfg->map) < 0)
		return (-1);
	if (normalize_map(&cfg->map) < 0)
		return (-1);
	return (0);
}

static int	phase_validate(t_config *cfg)
{
	if (validate_map_chars(&cfg->map) < 0)
		return (-1);
	if (locate_player(&cfg->map) < 0)
		return (-1);
	if (check_map_closed(&cfg->map) < 0)
		return (-1);
	return (0);
}

int	parse_cub(const char *path, t_config *cfg)
{
	int		fd;
	char	*first_line;

	if (!cfg)
		return (parser_error("malloc failure"));
	init_config(cfg);
	if (phase_open_and_headers(path, cfg, &fd, &first_line) < 0)
		return (-1);
	if (phase_map_read(fd, first_line, cfg) < 0)
	{
		close(fd);
		free_config(cfg);
		return (-1);
	}
	if (phase_validate(cfg) < 0)
	{
		close(fd);
		free_config(cfg);
		return (-1);
	}
	close(fd);
	return (0);
}
