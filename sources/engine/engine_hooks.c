/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:00:00 by peda-cos          #+#    #+#             */
/*   Updated: 2025/10/05 13:48:58 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	close_engine(void *param)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (eng && eng->mlx)
		mlx_close_window(eng->mlx);
}
