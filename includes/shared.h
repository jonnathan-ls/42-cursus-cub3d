/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 22:18:34 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <unistd.h>

size_t	mm_nodes_alloc_length(void);
void	mm_garbage_collector(void);
void	*mm_alloc(size_t count, size_t size);
int		ternary_int(int condition, int true_val, int false_val);

#endif
