/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_extension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:24:49 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/22 08:39:46 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

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
