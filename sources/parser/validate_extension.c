/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_extension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:49 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 23:48:36 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

/**
 * Validates that file has .cub extension.
 * @param path File path to validate.
 * @return 0 if valid, -1 otherwise.
 */
int	validate_file_extension(const char *path)
{
	int	len;

	if (!path)
		return (parser_error("invalid file extension"));
	len = (int)ft_strlen(path);
	if (len < 4)
		return (parser_error("invalid file extension"));
	if (path[len - 4] != '.' || path[len - 3] != 'c' || path[len - 2] != 'u'
		|| path[len - 1] != 'b')
		return (parser_error("invalid file extension"));
	return (0);
}
