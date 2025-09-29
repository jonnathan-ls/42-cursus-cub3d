/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:19:25 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/28 22:20:44 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

/* Data Structures */

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			rgba;
}				t_color;

typedef struct s_textures
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*floor_path;
	char		*ceiling_path;
}				t_textures;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_config
{
	t_textures	textures;
	t_color		floor_color;
	t_color		ceiling_color;
	t_map		map;
}				t_config;

/* Error */

int				parser_error(const char *msg);

/* Parse Pipeline */

int				validate_file_extension(const char *path);
int				parse_cub(const char *path, t_config *cfg);

/* Headers (textures & colors) */
int				is_empty_line(const char *s);
int				parse_color(char *rest, t_color *dst);
int				parse_texture(char *rest, char **dst_path);
int				parse_header_line(char *line, t_config *cfg, int *count_done);
int				parse_headers(int fd, t_config *cfg, char **line_after_headers);

/* Map acquisition & normalization */
int				normalize_map(t_map *map);
int				collect_map(int fd, char *first_map_line, t_map *map_raw);

/* Map validation */
int				locate_player(t_map *map);
int				check_map_closed(t_map *map);
int				validate_map_chars(t_map *map);

/* Free */
void			free_config(t_config *cfg);

#endif
