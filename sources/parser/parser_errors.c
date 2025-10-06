/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 23:48:36 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>

/**
 * Prints parser error message to stderr.
 * @param msg Error message to display.
 * @return Always returns -1.
 */
int	parser_error(const char *msg)
{
	ssize_t	ret;

	if (!msg)
		return (-1);
	ret = write(2, "Parse Error\n", 12);
	if (ret == -1)
		return (-1);
	ret = write(2, msg, ft_strlen(msg));
	if (ret == -1)
		return (-1);
	ret = write(2, "\n", 1);
	if (ret == -1)
		return (-1);
	return (-1);
}
