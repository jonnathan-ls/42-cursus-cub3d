/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 23:20:00 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:24:47 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "sprite.h"
#include "shared.h"
#include <MLX42/MLX42.h>

/**
 * @brief Loads a sprite texture from a PNG file.
 *
 * Attempts to load the texture at the specified path and stores it in
 * the sprite textures array at the given index.
 *
 * @param eng Engine structure containing sprite textures array.
 * @param index Index to store the loaded texture.
 * @param path Path to the PNG file.
 * @return 0 on success, -1 on failure.
 */
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

/**
 * @brief Allocates arrays for sprite system management.
 *
 * Creates arrays for textures, frame counts, frame widths, sprite types,
 * configurations, and character mappings.
 *
 * @param eng Engine structure to allocate arrays in.
 * @param count Number of sprite types to allocate for.
 * @return 0 on success, -1 on allocation failure.
 */
static int	allocate_arrays(t_engine *eng, int count)
{
	eng->sprites.textures = mm_alloc(count, sizeof(mlx_texture_t *));
	if (!eng->sprites.textures)
		return (-1);
	eng->sprites.frame_counts = mm_alloc(count, sizeof(int));
	if (!eng->sprites.frame_counts)
		return (-1);
	eng->sprites.frame_widths = mm_alloc(count, sizeof(int));
	if (!eng->sprites.frame_widths)
		return (-1);
	eng->sprites.sprite_types = mm_alloc(count, sizeof(int));
	if (!eng->sprites.sprite_types)
		return (-1);
	eng->sprites.configs = mm_alloc(count, sizeof(t_sprite_config));
	if (!eng->sprites.configs)
		return (-1);
	eng->sprite_chars = mm_alloc(count + 1, sizeof(char));
	if (!eng->sprite_chars)
		return (-1);
	eng->sprite_chars[count] = '\0';
	return (0);
}

/**
 * @brief Configures a single sprite type from configuration data.
 *
 * Sets character mapping, frame count, sprite type, loads texture, and
 * calculates frame width for the sprite type at the given index.
 *
 * @param eng Engine structure to configure.
 * @param cfg Array of sprite configurations.
 * @param i Index of the configuration to process.
 */
void	setup_sprite_type(t_engine *eng, t_sprite_config *cfg, int i)
{
	int	width;

	eng->sprite_chars[i] = cfg[i].identifier;
	eng->sprites.frame_counts[i] = cfg[i].frames;
	eng->sprites.sprite_types[i] = cfg[i].type;
	eng->sprites.configs[i] = cfg[i];
	load_sprite_texture(eng, i, cfg[i].path);
	if (eng->sprites.textures[i])
	{
		width = eng->sprites.textures[i]->width;
		eng->sprites.frame_widths[i] = width / cfg[i].frames;
	}
}

/**
 * @brief Initializes the entire sprite system.
 *
 * Allocates sprite arrays, loads textures, configures sprite types, and
 * collects sprites from the map.
 *
 * @param param Engine structure cast from void pointer.
 * @param configs Array of sprite configurations.
 * @param count Number of sprite configurations.
 */
void	init_sprites(void *param, t_sprite_config *configs, int count)
{
	t_engine	*eng;

	eng = (t_engine *)param;
	if (!eng)
		return ;
	init_sprite_values(eng);
	if (!configs || count == 0)
		return ;
	if (allocate_arrays(eng, count) < 0)
	{
		eng->sprites.texture_count = 0;
		return ;
	}
	eng->sprites.texture_count = count;
	setup_sprite_loop(eng, configs, count);
	collect_sprites_from_map(eng);
}

/**
 * @brief Frees all allocated sprite textures.
 *
 * Iterates through sprite textures and deletes each one to free
 * graphics memory.
 *
 * @param param Engine structure cast from void pointer.
 */
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
