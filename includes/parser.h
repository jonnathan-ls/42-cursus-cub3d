/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 01:29:28 by jlacerda         ###   ########.fr       */
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
	int			r;		/**< Red channel [0-255]. */
	int			g;		/**< Green channel [0-255]. */
	int			b;		/**< Blue channel [0-255]. */
	int			rgba;	/**< Packed RGBA color value. */
}				t_color;

/**
 * @struct s_sprite_config
 * @brief Sprite texture configuration from .cub file.
 */
typedef struct s_sprite_config
{
	char		identifier;	/**< Single character identifier. */
	char		*path;		/**< Path to texture file. */
	int			frames;		/**< Number of animation frames. */
	int			type;		/**< Sprite behavior type ID. */
}				t_sprite_config;

/**
 * @struct s_textures
 * @brief Texture paths loaded from configuration file.
 */
typedef struct s_textures
{
	char				*no_path;		/**< North wall texture path. */
	char				*so_path;		/**< South wall texture path. */
	char				*we_path;		/**< West wall texture path. */
	char				*ea_path;		/**< East wall texture path. */
	char				*menu_path;		/**< Menu overlay texture path. */
	char				*floor_path;	/**< Floor texture path. */
	char				*ceiling_path;	/**< Ceiling texture path. */
	char				*door_path;		/**< Door texture path. */
	char				*start_path;	/**< Start screen texture path. */
	char				*win_path;		/**< Win screen texture path. */
	char				*lose_path;		/**< Lose screen texture path. */
	t_sprite_config		*sprites;		/**< Array of sprite configs. */
	int					sprite_count;	/**< Number of sprite configs. */
}				t_textures;

/**
 * @struct s_map
 * @brief Map grid layout and player spawn information.
 */
typedef struct s_map
{
	int			width;		/**< Map width in tiles. */
	int			height;		/**< Map height in tiles. */
	char		**grid;		/**< 2D character array of map. */
	int			player_x;	/**< Player spawn X coordinate. */
	int			player_y;	/**< Player spawn Y coordinate. */
	char		player_dir;	/**< Player spawn direction (N/S/E/W). */
}				t_map;

/**
 * @struct s_config
 * @brief Complete scene configuration from .cub file.
 */
typedef struct s_config
{
	t_map		map;			/**< Map layout and spawn data. */
	t_textures	textures;		/**< Texture file paths. */
	t_color		floor_color;	/**< Floor RGB color. */
	t_color		ceiling_color;	/**< Ceiling RGB color. */
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
int				handle_optional_texture(char *id, t_config *cfg, char *rest);
int				check_duplicate_identifier(t_config *cfg, char id);
int				extract_number(char *space);
void			set_sprite_data(t_sprite_config *sprite, int params[2]);
void			init_params(int params[2]);
int				parse_single_texture(char *rest, char **dst, char *name);
#endif
