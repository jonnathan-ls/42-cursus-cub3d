/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 20:34:53 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

char	*skip_to_space(char *str)
{
	while (*str && *str != ' ' && *str != '\t' && *str != '\n')
		str++;
	return (str);
}

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

char	extract_identifier(char *rest)
{
	while (*rest == ' ' || *rest == '\t')
		rest++;
	if ((*rest >= 'A' && *rest <= 'Z') || (*rest >= 'a' && *rest <= 'z'))
		return (*rest);
	return (0);
}
