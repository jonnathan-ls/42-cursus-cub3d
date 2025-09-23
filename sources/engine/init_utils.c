/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:28:16 by peda-cos          #+#    #+#             */
/*   Updated: 2025/09/23 19:28:17 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Initializes all members of the t_engine structure to NULL.
 * This ensures safe cleanup by preventing undefined behavior from
 * uninitialized pointers.
 */
void	zero_engine(t_engine *eng)
{
	eng->mlx = NULL;
	eng->img.frame = NULL;
	eng->img.cursor = NULL;
	eng->tex.north = NULL;
	eng->tex.south = NULL;
	eng->tex.west = NULL;
	eng->tex.east = NULL;
	eng->tex.door_closed = NULL;
}
