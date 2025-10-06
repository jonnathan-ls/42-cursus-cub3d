/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 23:59:04 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/**
 * Advances pointer to next space or tab character.
 * @param str String to scan.
 * @return Pointer to first space/tab/newline found.
 */
char	*skip_to_space(char *str)
{
	while (*str && *str != ' ' && *str != '\t' && *str != '\n')
		str++;
	return (str);
}

/**
 * Extracts frame count from sprite configuration line.
 * @param space Pointer to start of number string.
 * @return Frame count or 1 if invalid.
 */
int	extract_frame_count(char *space)
{
	int	frames;

	while (*space == ' ' || *space == '\t')
		space++;
	frames = ft_atoi(space);
	if (frames > 0)
		return (frames);
	return (1);
}

/**
 * Extracts sprite identifier character from line.
 * @param rest Pointer to line after whitespace.
 * @return Identifier character or 0 if invalid.
 */
char	extract_identifier(char *rest)
{
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if ((*rest >= 'A' && *rest <= 'Z') || (*rest >= 'a' && *rest <= 'z'))
		return (*rest);
	return (0);
}
