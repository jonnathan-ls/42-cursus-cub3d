/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/20 20:58:35 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <MLX42/MLX42.h>

typedef struct s_config	t_config;

typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
}			t_door;

typedef struct s_doors_manager
{
	t_door	*doors;
	int		count;
}			t_doors_manager;

typedef struct s_mlx42
{
	mlx_t				*instance;
	mlx_image_t			*image;
}						t_mlx42;

typedef struct s_cub3d
{
	t_mlx42				mlx;
	t_config			config;
}						t_cub3d;

#endif
