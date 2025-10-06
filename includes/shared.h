/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:52:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
# define SHARED_H

# include <unistd.h>
# include <stdint.h>

typedef struct s_engine	t_engine;

void		mm_garbage_collector(void);
size_t		mm_nodes_alloc_length(void);
void		*mm_alloc(size_t count, size_t size);

double		calc_euclidean_dist(double x1, double y1, double x2, double y2);
int			is_in_radius(double x1, double y1, double x2, double y2);
double		clamp_double(double value, double min, double max);
int			is_within_bounds(int value, int min, int max);
uint8_t		extract_color_channel(uint32_t color, int shift);
uint32_t	build_rgba_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif
