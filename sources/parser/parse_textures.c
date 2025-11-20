/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:23 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/20 07:38:44 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <MLX42/MLX42.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Removes trailing whitespace and newlines from string.
 * @param s String to trim.
 * @return Trimmed string.
 */
static char	*trim_end(char *s)
{
	int	len;

	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' '
			|| s[len - 1] == '\t'))
	{
		s[len - 1] = '\0';
		len = len - 1;
	}
	return (s);
}

/**
 * Validates PNG file extension.
 * @param path Path to PNG file.
 * @param dst_path Pointer to free on error.
 * @return 0 on success, -1 on failure.
 */
static int	validate_png_format(char *path, char **dst_path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(&path[len - 4], ".png", 4) != 0)
	{
		free(*dst_path);
		*dst_path = NULL;
		return (parser_error("texture file must have .png extension"));
	}
	return (0);
}

/**
 * Parses texture path from configuration line.
 * @param rest Rest of line after identifier.
 * @param dst_path Pointer to store texture path.
 * @return 0 on success, -1 on failure.
 */
int	parse_texture(char *rest, char **dst_path)
{
	int	fd;

	if (!rest || !dst_path)
		return (parser_error("invalid texture line format"));
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if (*rest == '\0' || *rest == '\n')
		return (parser_error("invalid texture line format"));
	trim_end(rest);
	if (*dst_path)
		return (parser_error("duplicate texture identifier"));
	*dst_path = ft_strdup(rest);
	if (!*dst_path)
		return (parser_error("malloc failure"));
	fd = open(*dst_path, O_RDONLY);
	if (fd < 0)
	{
		system_error(*dst_path);
		free(*dst_path);
		*dst_path = NULL;
		return (-1);
	}
	close(fd);
	return (validate_png_format(*dst_path, dst_path));
}
