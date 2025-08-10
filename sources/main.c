/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/10 18:35:39 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	init_mlx42_example(t_cub3d *cub3d);

int	main(void)
{
	t_cub3d	cub3d;

	ft_putstr_fd("Hello, Cube3D!\n", 1);
	printf("Math OK - sqrt of 25 is %f\n", sqrt(25.0));
	printf("MLX42 Example Initialization...\n");
	init_mlx42_example(&cub3d);
	return (0);
}
