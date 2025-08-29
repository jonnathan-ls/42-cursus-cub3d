/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:23 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 09:05:28 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*trim_end(char *s)
{
	int	len;

	len = (int)ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == ' '
			|| s[len - 1] == '\t'))
	{
		s[len - 1] = '\0';
		len--;
	}
	return (s);
}

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
		return (parser_error("cannot open file"));
	close(fd);
	return (0);
}
