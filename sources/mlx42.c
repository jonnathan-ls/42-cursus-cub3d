/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx42.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/08/10 18:36:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	ft_randomize(void	*param)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	t_cub3d		*cub3d;
	mlx_image_t	*image;

	x = 0;
	cub3d = param;
	image = cub3d->mlx.image;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			color = ft_pixel(
					rand() % WHITE,
					rand() % WHITE,
					rand() % WHITE,
					rand() % WHITE);
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

static void	ft_hook(void	*param)
{
	t_cub3d		*cub3d;
	mlx_image_t	*image;
	mlx_t		*mlx;

	cub3d = param;
	mlx = cub3d->mlx.instance;
	image = cub3d->mlx.image;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		printf("Closing window...\n");
		mlx_close_window(mlx);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

static bool	config_mlx42(t_cub3d *cub3d)
{
	t_mlx42	*mlx42;

	mlx42 = &cub3d->mlx;
	mlx42->instance = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MLX42", true);
	if (!mlx42->instance)
	{
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	mlx42->image = mlx_new_image(mlx42->instance, 128, 128);
	if (!mlx42->image)
	{
		mlx_close_window(mlx42->instance);
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	if (mlx_image_to_window(mlx42->instance, mlx42->image, 0, 0) == -1)
	{
		mlx_close_window(mlx42->instance);
		puts(mlx_strerror(mlx_errno));
		return (false);
	}
	return (true);
}

int32_t	init_mlx42_example(t_cub3d *cub3d)
{
	mlx_t	*mlx;

	if (!config_mlx42(cub3d))
		return (EXIT_FAILURE);
	mlx = cub3d->mlx.instance;
	mlx_loop_hook(mlx, ft_randomize, cub3d);
	mlx_loop_hook(mlx, ft_hook, cub3d);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
