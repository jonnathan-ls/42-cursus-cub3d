/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:18 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/06 00:09:57 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>

/**
 * @brief Parses and validates a single RGB color component.
 *
 * Extracts a numeric value from the input string, validates that it
 * contains only digits, and ensures the value is within [0-255] range.
 *
 * @param s String containing the color component.
 * @param out Pointer to store the parsed value.
 * @return 0 on success, -1 on failure.
 */
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
		i = i + 1;
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

/**
 * @brief Frees an array of strings and the array itself.
 *
 * Iterates through the string array, freeing each element, then frees
 * the array pointer.
 *
 * @param parts Array of strings to free.
 */
static void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts && parts[i])
		free(parts[i++]);
	free(parts);
}

/**
 * @brief Validates that a color specification has exactly 3 components.
 *
 * Counts the number of parts in the split string and verifies that
 * exactly 3 components (R, G, B) are present.
 *
 * @param parts Array of strings representing color components.
 * @return 0 if valid, -1 otherwise.
 */
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

/**
 * @brief Parses R, G, B components and computes the RGBA value.
 *
 * Extracts red, green, and blue values from the parts array, validates
 * each component, and constructs the final RGBA integer value.
 *
 * @param parts Array of strings containing R, G, B values.
 * @param dst Color structure to populate.
 * @return 0 on success, -1 on failure.
 */
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

/**
 * @brief Parses a color specification string into a color structure.
 *
 * Expects a comma-separated RGB format "R,G,B". Splits the input,
 * validates component count, and extracts each color value.
 *
 * @param rest String containing color specification.
 * @param dst Color structure to populate.
 * @return 0 on success, -1 on failure.
 */
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
