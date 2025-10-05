/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 01:02:40 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"
#include <MLX42/MLX42.h>

static int	load_sprite_texture(t_engine *eng, int index, char *path)
{
	mlx_texture_t	*texture;

	if (!path)
		return (-1);
	texture = mlx_load_png(path);
	if (!texture)
		return (-1);
	eng->sprites.textures[index] = texture;
	return (0);
}

void	init_sprites(void *param, char *sprite_path, int frames)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng)
		return ;
	eng->sprites.list = NULL;
	eng->sprites.count = 0;
	eng->sprites.order = NULL;
	eng->sprites.texture_count = 1;
	eng->sprites.frame_count = frames;
	eng->sprites.frame_width = 0;
	eng->sprites.textures = mm_alloc(1, sizeof(mlx_texture_t *));
	if (!eng->sprites.textures)
		return ;
	if (load_sprite_texture(eng, 0, sprite_path) < 0)
		return ;
	if (eng->sprites.textures[0])
		eng->sprites.frame_width = eng->sprites.textures[0]->width / frames;
	collect_sprites_from_map(eng);
}

void	free_sprites(void *param)
{
	t_engine	*eng;
	int			i;

	eng = (t_engine *)param;
	if (!eng)
		return ;
	i = 0;
	while (i < eng->sprites.texture_count)
	{
		if (eng->sprites.textures[i])
			mlx_delete_texture(eng->sprites.textures[i]);
		i = i + 1;
	}
}
