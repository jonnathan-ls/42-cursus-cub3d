/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 05:23:48 by peda-cos          #+#    #+#             */
/*   Updated: 2025/11/01 16:10:55 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"

/**
 * @brief Releases resources allocated during parsing.
 *
 * Clears GNL storage, closes the file descriptor, and frees the
 * configuration structure if provided.
 *
 * @param fd File descriptor to close.
 * @param cfg Configuration structure to free.
 */
void	parser_release_resources(int fd, t_config *cfg)
{
	gnl_clear_storage();
	close(fd);
	if (cfg)
		free_config(cfg);
}
