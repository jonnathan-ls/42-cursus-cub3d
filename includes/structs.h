/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peda-cos <peda-cos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/14 18:16:27 by peda-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <MLX42/MLX42.h>

typedef struct s_config	t_config;

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
