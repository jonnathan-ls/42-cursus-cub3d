/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:00:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "weapon.h"
#include "sprite.h"

void	calc_tex_coords(int pos[2], int start[2], int screen, int *tex);
void	draw_pixel_if_valid(t_engine *eng, int pos[2], uint32_t color);

/**
 * @brief Calculates projectile screen position using camera transform.
 *
 * @param eng Engine structure containing camera data.
 * @param proj Projectile to calculate position for.
 * @param screen Output array [x_pos, size] (-9999 if behind camera).
 */
static void	calculate_projectile_screen_pos(t_engine *eng,
	t_projectile *proj, int *screen)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	tx;
	double	ty;

	sprite_x = proj->x - eng->player.pos_x;
	sprite_y = proj->y - eng->player.pos_y;
	inv_det = 1.0 / (eng->player.plane_x * eng->player.dir_y
			- eng->player.dir_x * eng->player.plane_y);
	tx = inv_det * (eng->player.dir_y * sprite_x
			- eng->player.dir_x * sprite_y);
	ty = inv_det * (-eng->player.plane_y * sprite_x
			+ eng->player.plane_x * sprite_y);
	if (ty <= 0.1)
	{
		screen[0] = -9999;
		return ;
	}
	screen[0] = (int)((eng->window_width / 2) * (1 + tx / ty));
	screen[1] = (int)(eng->window_height / ty);
}

/**
 * @brief Gets pixel from projectile animation frame.
 *
 * @param eng Engine structure containing projectile texture.
 * @param proj Projectile to get pixel from.
 * @param tx Texture X coordinate within frame.
 * @param ty Texture Y coordinate.
 * @return Packed RGBA color value.
 */
static uint32_t	get_proj_pixel(t_engine *eng,
	t_projectile *proj, int tx, int ty)
{
	mlx_texture_t	*tex;
	int				frame_x;
	int				index;
	uint32_t		color;

	tex = eng->weapon.projectile_texture;
	if (!tex)
		return (0);
	frame_x = proj->current_frame * eng->weapon.projectile_frame_width;
	frame_x += tx;
	if (frame_x < 0 || frame_x >= (int)tex->width)
		return (0);
	if (ty < 0 || ty >= (int)tex->height)
		return (0);
	index = (ty * tex->width + frame_x) * 4;
	color = (tex->pixels[index] << 24);
	color |= (tex->pixels[index + 1] << 16);
	color |= (tex->pixels[index + 2] << 8) | tex->pixels[index + 3];
	return (color);
}

/**
 * @brief Draws one horizontal row of projectile sprite.
 *
 * @param eng Engine structure containing frame buffer.
 * @param proj Projectile to draw.
 * @param data Render parameters [start_x, start_y, end_x, width, size, y].
 */
static void	draw_proj_row(t_engine *eng, t_projectile *proj, int data[5])
{
	int			pos[2];
	int			tex[2];
	uint32_t	color;

	pos[0] = data[0];
	while (pos[0] < data[2] && pos[0] < eng->window_width)
	{
		if (pos[0] >= 0 && data[4] >= 0)
		{
			tex[0] = (pos[0] - data[0]) * data[3] / data[4];
			tex[1] = (data[5] - data[1])
				* eng->weapon.projectile_texture->height / data[4];
			color = get_proj_pixel(eng, proj, tex[0], tex[1]);
			pos[1] = data[5];
			draw_pixel_if_valid(eng, pos, color);
		}
		pos[0]++;
	}
}

/**
 * @brief Draws complete projectile sprite to frame buffer.
 *
 * @param eng Engine structure containing frame buffer.
 * @param proj Projectile to draw.
 * @param screen Screen position [x, size] from transform calculation.
 */
static void	draw_projectile_sprite(t_engine *eng,
	t_projectile *proj, int screen[2])
{
	int	start[2];
	int	end[2];
	int	data[6];

	if (!eng->weapon.projectile_texture)
		return ;
	start[0] = screen[0] - screen[1] / 2;
	start[1] = eng->window_height / 2 - screen[1] / 2;
	end[0] = screen[0] + screen[1] / 2;
	end[1] = eng->window_height / 2 + screen[1] / 2;
	data[3] = eng->weapon.projectile_frame_width;
	data[4] = screen[1];
	data[5] = start[1];
	while (data[5] < end[1] && data[5] < eng->window_height)
	{
		data[0] = start[0];
		data[1] = start[1];
		data[2] = end[0];
		draw_proj_row(eng, proj, data);
		data[5]++;
	}
}

/**
 * @brief Renders all active projectiles as 3D sprites.
 *
 * @param param Engine structure cast from void pointer.
 */
void	render_projectiles(void *param)
{
	t_engine	*eng;
	int			i;
	int			screen[2];

	eng = (t_engine *)param;
	if (!eng || !eng->weapon.projectile_texture)
		return ;
	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (eng->weapon.projectiles[i].active)
		{
			calculate_projectile_screen_pos(eng,
				&eng->weapon.projectiles[i], screen);
			if (screen[0] > -9999)
				draw_projectile_sprite(eng,
					&eng->weapon.projectiles[i], screen);
		}
		i++;
	}
}
