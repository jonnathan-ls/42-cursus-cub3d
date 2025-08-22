/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_unit_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:40:38 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 17:40:56 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_unit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	build_header_block(char *buf, int sz, const char *no,
		const char *so, const char *we, const char *ea, const char *f,
		const char *c)
{
	int	len;

	len = snprintf(buf, sz, "NO %s\nSO %s\nWE %s\nEA %s\nF %s\nC %s\n", no, so,
			we, ea, f, c);
	if (len < 0 || len >= sz)
		return (-1);
	return (len);
}

static int	make_textures(const char *root, char *no, char *so, char *we,
		char *ea)
{
	char	texdir[512];

	if (!join_path(root, "tex", texdir, sizeof(texdir)))
		return (-1);
	if (ensure_dir(texdir) < 0)
		return (-1);
	if (create_dummy_texture(texdir, "n.xpm", no, 512) < 0)
		return (-1);
	if (create_dummy_texture(texdir, "s.xpm", so, 512) < 0)
		return (-1);
	if (create_dummy_texture(texdir, "w.xpm", we, 512) < 0)
		return (-1);
	if (create_dummy_texture(texdir, "e.xpm", ea, 512) < 0)
		return (-1);
	return (0);
}

static int	write_case_file(const char *root, const char *name,
		const char *content, char *outpath, int outsz)
{
	if (!join_path(root, name, outpath, outsz))
		return (-1);
	if (write_file(outpath, content) < 0)
		return (-1);
	return (0);
}

int	test_valid_minimal(t_test_result *res, const char *tmp_root)
{
	char		no[512];
	char		so[512];
	char		we[512];
	char		ea[512];
	char		head[1024];
	char		file[512];
	char		buf[1600];
	char		err[512];
	t_config	cfg;
	int			len;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	len = build_header_block(head, sizeof(head), no, so, we, ea, "220,100,0",
			"225,30,0");
	if (len < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "%s111\n1N1\n111\n", head);
	if (write_case_file(tmp_root, "ok.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	if (capture_parse(file, &cfg, err, sizeof(err)) < 0)
		return (-1);
	if (err[0])
		return (-1);
	free_config(&cfg);
	return (0);
}

int	test_invalid_extension(t_test_result *res, const char *tmp_root)
{
	char		file[512];
	char		err[256];
	t_config	cfg;

	(void)res;
	if (write_case_file(tmp_root, "bad.ext", "", file, sizeof(file)) < 0)
		return (-1);
	if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		return (-1);
	if (!ft_strnstr(err, "invalid file extension", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_duplicate_texture(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	file[512];
	char	buf[1600];
	char	err[512];
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "NO %s\nSO %s\nWE %s\nNO %s\nEA
		%s\nF 0,0,0\nC 0,0,0\n111\n1N1\n111\n", no, so, we, no, ea);
	if (write_case_file(tmp_root, "duptex.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "duplicate", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_duplicate_color(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	file[512];
	char	buf[1600];
	char	err[512];
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "NO %s\nSO %s\nWE %s\nEA
		%s\nF 0,0,0\nF 0,0,1\nC 5,5,5\n111\n1N1\n111\n", no, so, we, ea);
	if (write_case_file(tmp_root, "dupcol.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "duplicate", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_missing_player(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	file[512];
	char	buf[1600];
	char	err[512];
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "NO %s\nSO %s\nWE %s\nEA
		%s\nF 0,0,0\nC 5,5,5\n111\n101\n111\n", no, so, we, ea);
	if (write_case_file(tmp_root, "noplayer.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "player", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_multiple_players(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	file[512];
	char	buf[1600];
	char	err[512];
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "NO %s\nSO %s\nWE %s\nEA
		%s\nF 0,0,0\nC 5,5,5\n111\n1N1\n1S1\n111\n", no, so, we, ea);
	if (write_case_file(tmp_root, "multi.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "multiple", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_map_not_closed(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	file[512];
	char	buf[1600];
	char	err[512];
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "NO %s\nSO %s\nWE %s\nEA
		%s\nF 0,0,0\nC 5,5,5\n111\n1N \n111\n", no, so, we, ea);
	if (write_case_file(tmp_root, "open.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "not closed", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_invalid_map_char(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	file[512];
	char	buf[1600];
	char	err[512];
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "NO %s\nSO %s\nWE %s\nEA
		%s\nF 0,0,0\nC 5,5,5\n111\n1X1\n1N1\n111\n", no, so, we, ea);
	if (write_case_file(tmp_root, "badchar.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "invalid map character", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_color_out_of_range(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	file[512];
	char	buf[1600];
	char	err[512];
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "NO %s\nSO %s\nWE %s\nEA
		%s\nF 256,0,0\nC 5,5,5\n111\n1N1\n111\n", no, so, we, ea);
	if (write_case_file(tmp_root, "badcolor.cub", buf, file, sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "color", ft_strlen(err)))
		return (-1);
	return (0);
}

int	test_texture_file_missing(t_test_result *res, const char *tmp_root)
{
	char	no[512];
	char	so[512];
	char	we[512];
	char	ea[512];
	char	head[1024];
	char	file[512];
	char	buf[1600];
	char	err[512];
	int		len;
		t_config cfg;

	(void)res;
	if (make_textures(tmp_root, no, so, we, ea) < 0)
		return (-1);
	/* Use non-existent path for east */
	len = build_header_block(head, sizeof(head), no, so, we,
			"./does_not_exist.xpm", "0,0,0", "5,5,5");
	if (len < 0)
		return (-1);
	snprintf(buf, sizeof(buf), "%s111\n1N1\n111\n", head);
	if (write_case_file(tmp_root, "missingtex.cub", buf, file,
			sizeof(file)) < 0)
		return (-1);
	{
		if (capture_parse(file, &cfg, err, sizeof(err)) >= 0)
		{
			free_config(&cfg);
			return (-1);
		}
	}
	if (!ft_strnstr(err, "cannot open file", ft_strlen(err)))
		return (-1);
	return (0);
}
