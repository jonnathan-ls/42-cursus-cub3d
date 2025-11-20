/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/20 08:05:15 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * Prints parser error message to stderr.
 * @param msg Error message to display.
 * @return Always returns -1.
 */
int	parser_error(const char *msg)
{
	if (!msg)
		return (-1);
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd((char *)msg, 2);
	return (-1);
}

/**
 * Prints system error message to stderr.
 * @param prefix Prefix for the error message (e.g. filename).
 * @return Always returns -1.
 */
int	system_error(const char *prefix)
{
	ft_putstr_fd("Error: ", 2);
	if (prefix)
	{
		ft_putstr_fd((char *)prefix, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errno), 2);
	return (-1);
}
