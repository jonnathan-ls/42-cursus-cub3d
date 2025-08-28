/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/08/28 20:25:12 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>

int	parser_error(const char *msg)
{
	ssize_t	ret;

	if (!msg)
		return (-1);
	ret = write(2, "Error\n", 6);
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
