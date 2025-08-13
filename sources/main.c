/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/12 22:38:17 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	init_mlx42_example(t_cub3d *cub3d);

typedef struct s_test_struct
{
	int		value;
	char	*name;
}	t_test_struct;

int	main(void)
{
	// t_cub3d cub3d;

	ft_putstr_fd("Hello, Cube3D!\n", 1);
	printf("Math OK - sqrt of 25 is %f\n", sqrt(25.0));
	printf("MLX42 Example Initialization...\n");
	// init_mlx42_example(&cub3d);
	printf("Testing memory manager...\n");
	t_test_struct *test_struct = mm_alloc(1, sizeof(t_test_struct));
	test_struct->name = mm_alloc(10, sizeof(char));
	test_struct->value = 42;
	ft_strlcpy(test_struct->name, "Test", 10);
	mm_garbage_collector();
	int *int_list = mm_alloc(5, sizeof(int));
	for (int i = 0; i < 5; i++)
		int_list[i] = i * 10;
	mm_garbage_collector();
	return (0);
}
