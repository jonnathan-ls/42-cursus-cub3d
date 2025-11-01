/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/01 17:13:20 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>

/**
 * @struct s_color
 * @brief RGB color representation with RGBA value.
 */
typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			rgba;
}				t_color;

/**
 * @struct s_sprite_config
 * @brief Sprite texture configuration from .cub file.
 */
typedef struct s_sprite_config
{
	char		identifier;
	char		*path;
	int			frames;
	int			type;
}				t_sprite_config;

/**
 * @struct s_textures
 * @brief Texture paths loaded from configuration file.
 */
typedef struct s_textures
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	char				*menu_path;
	char				*floor_path;
	char				*ceiling_path;
	char				*door_path;
	char				*start_path;
	char				*win_path;
	char				*lose_path;
	t_sprite_config		*sprites;
	int					sprite_count;
}				t_textures;

/**
 * @struct s_map
 * @brief Map grid layout and player spawn information.
 */
typedef struct s_map
{
	int			width;
	int			height;
	char		**grid;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

/**
 * @struct s_config
 * @brief Complete scene configuration from .cub file.
 */
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
void			init_config_values(t_config *cfg);
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
int				handle_optional_texture(char *id, t_config *cfg, char *rest);
int				check_duplicate_identifier(t_config *cfg, char id);
int				extract_number(char *space);
void			set_sprite_data(t_sprite_config *sprite, int params[2]);
void			init_params(int params[2]);
int				parse_single_texture(char *rest, char **dst, char *name);
void			parser_release_resources(int fd, t_config *cfg);
#endif
