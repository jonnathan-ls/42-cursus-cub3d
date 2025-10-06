/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_screens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 01:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 01:43:59 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <MLX42/MLX42.h>

void	draw_screen_overlay(t_engine *eng, mlx_texture_t *tex)
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	if (!eng || !tex || !eng->frame)
		return ;
	y = 0;
	while (y < eng->window_height)
	{
		x = 0;
		tex_y = (y * tex->height) / eng->window_height;
		while (x < eng->window_width)
		{
			tex_x = (x * tex->width) / eng->window_width;
			color = ((uint32_t *)tex->pixels)[tex_y * tex->width + tex_x];
			mlx_put_pixel(eng->frame, x, y, color);
			x++;
		}
		y++;
	}
}

void	handle_start_screen(t_engine *eng)
{
	int	key_pressed;

	if (!eng)
		return ;
	key_pressed = mlx_is_key_down(eng->mlx, MLX_KEY_ENTER);
	if (key_pressed && !eng->start_toggle)
		eng->game_started = 1;
	eng->start_toggle = key_pressed;
}

static int	check_win_condition(t_engine *eng)
{
	int	i;
	int	coins;

	i = 0;
	coins = 0;
	while (i < eng->sprites.count)
	{
		if (eng->sprites.list[i].sprite_type == 4)
		{
			if (!eng->sprites.list[i].collected)
				return (0);
			coins++;
		}
		i++;
	}
	if (coins > 0)
		return (1);
	return (0);
}

void	handle_win_screen(t_engine *eng)
{
	if (!eng)
		return ;
	if (check_win_condition(eng))
		eng->player.game_over = 2;
}

void	handle_lose_screen(t_engine *eng)
{
	if (!eng)
		return ;
	if (eng->player.health <= 0)
		eng->player.game_over = 1;
}
