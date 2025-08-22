/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:18 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 08:59:48 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static int	parse_component(char *s, int *out)
{
	int	val;
	int	i;

	i = 0;
	if (!s || !s[0])
		return (parser_error("invalid color format"));
	while (s[i])
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			break ;
		}
		if (!ft_isdigit((unsigned char)s[i]))
			return (parser_error("invalid color format"));
		i++;
	}
	val = ft_atoi(s);
	if (val < 0 || val > 255)
		return (parser_error("color component out of range"));
	*out = val;
	return (0);
}

static void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts && parts[i])
		free(parts[i++]);
	free(parts);
}

static int	trim_and_count(char **parts)
{
	int	count;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
		return (parser_error("invalid color format"));
	while (*parts && (**parts == ' ' || **parts == '\t'))
		(*parts)++;
	while (parts[1] && (*parts[1] == ' ' || *parts[1] == '\t'))
		parts[1]++;
	while (parts[2] && (*parts[2] == ' ' || *parts[2] == '\t'))
		parts[2]++;
	return (0);
}

static int	parse_components(char **parts, t_color *dst)
{
	if (parse_component(parts[0], &dst->r) < 0)
		return (-1);
	if (parse_component(parts[1], &dst->g) < 0)
		return (-1);
	if (parse_component(parts[2], &dst->b) < 0)
		return (-1);
	dst->rgba = (dst->r << 24) | (dst->g << 16) | (dst->b << 8) | 0xFF;
	return (0);
}

int	parse_color(char *rest, t_color *dst)
{
	char	**parts;

	if (!rest || !dst)
		return (parser_error("invalid color format"));
	while (*rest == ' ' || *rest == '\t')
		rest++;
	parts = ft_split(rest, ',');
	if (!parts)
		return (parser_error("malloc failure"));
	if (trim_and_count(parts) < 0 || parse_components(parts, dst) < 0)
	{
		free_parts(parts);
		return (-1);
	}
	free_parts(parts);
	return (0);
}
