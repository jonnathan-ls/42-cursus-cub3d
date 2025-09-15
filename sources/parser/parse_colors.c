/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:18 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/14 18:50:47 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

static int	parse_component(char *s, int *out)
{
	int	val;
	int	i;

	if (!s || !s[0])
		return (parser_error("empty color component"));
	while (*s == ' ' || *s == '\t')
		s++;
	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != ' ' && s[i] != '\t')
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (parser_error("non-numeric color component"));
		i++;
	}
	if (i == 0)
		return (parser_error("empty color component"));
	s[i] = '\0';
	val = ft_atoi(s);
	if (val < 0 || val > 255)
		return (parser_error("color component out of range [0-255]"));
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

static int	validate_part_count(char **parts)
{
	int	count;

	count = 0;
	while (parts[count])
		count++;
	if (count != 3)
		return (parser_error("color must have exactly 3 components"));
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
	if (validate_part_count(parts) < 0 || parse_components(parts, dst) < 0)
	{
		free_parts(parts);
		return (-1);
	}
	free_parts(parts);
	return (0);
}
