/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:19:25 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 13:53:17 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			rgba;
}				t_color;

typedef struct s_sprite_config
{
	char		identifier;
	char		*path;
	int			frames;
	int			type;
}				t_sprite_config;

typedef struct s_textures
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	char				*menu_path;
	char				*floor_path;
	char				*ceiling_path;
	t_sprite_config		*sprites;
	int					sprite_count;
}				t_textures;

typedef struct s_map
{
	int			width;
	int			height;
	char		**grid;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_config
{
	t_map		map;
	t_textures	textures;
	t_color		floor_color;
	t_color		ceiling_color;
}				t_config;

int				normalize_map(t_map *map);
int				locate_player(t_map *map);
void			free_config(t_config *cfg);
int				check_map_closed(t_map *map);
int				parser_error(const char *msg);
int				validate_map_chars(t_map *map);
int				parse_color(char *rest, t_color *dst);
int				validate_file_extension(const char *path);
int				parse_cub(const char *path, t_config *cfg);
int				parse_texture(char *rest, char **dst_path);
int				parse_sprite_texture(char *rest, t_config *cfg);
char			*skip_to_space(char *str);
int				extract_frame_count(char *space);
char			extract_identifier(char *rest);
int				collect_map(int fd, char *first_map_line, t_map *map_raw);
int				parse_header_line(char *line, t_config *cfg, int *count_done);
int				parse_headers(int fd, t_config *cfg, char **line_after_headers);

#endif
