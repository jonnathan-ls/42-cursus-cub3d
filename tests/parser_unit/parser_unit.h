/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_unit.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:41:02 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 17:41:03 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UNIT_H
# define PARSER_UNIT_H

# include "parser.h"

typedef struct s_test_result
{
	int			passed;
	int			expected_ok;
	char		name[64];
	char		msg[256];
}				t_test_result;

typedef int		(*t_test_fn)(t_test_result *res, const char *tmp_root);

typedef struct s_test_case
{
	char		name[64];
	t_test_fn	fn;
	int			should_pass;
}				t_test_case;

int				capture_parse(const char *path, t_config *cfg, char *errbuf,
					int buflen);
int				write_file(const char *path, const char *content);
int				ensure_dir(const char *path);
char			*join_path(const char *a, const char *b, char *buf,
					int bufsize);
int				create_dummy_texture(const char *dir, const char *name,
					char *out, int outsz);
int				build_temp_root(char *buf, int buflen);

/* Individual test functions */
int				test_valid_minimal(t_test_result *res, const char *tmp_root);
int				test_invalid_extension(t_test_result *res,
					const char *tmp_root);
int				test_duplicate_texture(t_test_result *res,
					const char *tmp_root);
int				test_duplicate_color(t_test_result *res, const char *tmp_root);
int				test_missing_player(t_test_result *res, const char *tmp_root);
int				test_multiple_players(t_test_result *res, const char *tmp_root);
int				test_map_not_closed(t_test_result *res, const char *tmp_root);
int				test_invalid_map_char(t_test_result *res, const char *tmp_root);
int				test_color_out_of_range(t_test_result *res,
					const char *tmp_root);
int				test_texture_file_missing(t_test_result *res,
					const char *tmp_root);

#endif
