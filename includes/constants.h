/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/11/01 15:19:00 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

/** @brief Default window width in pixels. */
# define WIN_WIDTH 1280
/** @brief Default window height in pixels. */
# define WIN_HEIGHT 720

/** @brief Mathematical constant PI for trigonometric calculations. */
# define PI 3.14159265358979323846

/** @brief Red color in RGBA format. */
# define RED 0xFFFF0000
/** @brief Gray color in RGBA format. */
# define GRAY 0xFF888888
/** @brief Black color in RGBA format. */
# define BLACK 0xFF000000
/** @brief White color in RGBA format. */
# define WHITE 0xFFFFFFFF
/** @brief Light gray color in RGBA format. */
# define LIGHT_GRAY 0xFFCCCCCC

/** @brief Small value for floating point comparisons. */
# define EPSILON 0.0001
/** @brief Camera plane scaling factor for FOV. */
# define PLANE_FACTOR 0.675
/** @brief Player rotation speed in radians per frame. */
# define ROTATION_SPEED 0.1
/** @brief Player movement speed in units per frame. */
# define MOVEMENT_SPEED 0.075
/** @brief Friction factor when sliding against walls. */
# define WALL_SLIDE_FACTOR 0.375
/** @brief Mouse rotation sensitivity multiplier. */
# define MOUSE_SENSITIVITY 0.0025

/** @brief Minimap border offset from screen edges. */
# define MINIMAP_OFFSET 10
/** @brief Minimum minimap zoom level. */
# define MINIMAP_MIN_SCALE 1
/** @brief Maximum minimap zoom level. */
# define MINIMAP_MAX_SCALE 10
/** @brief Reserved screen space divisor for minimap. */
# define MINIMAP_RESERVED_DIV 4
/** @brief Minimap scale adjustment divisor. */
# define MINIMAP_SCALE_DIVISOR 10
/** @brief Minimap size calculation divisor. */
# define MINIMAP_SIZE_DIVISOR 10
/** @brief Minimum minimap size in pixels. */
# define MINIMAP_MIN_SIZE 8
/** @brief Minimap frame border thickness. */
# define MINIMAP_BORDER_OFFSET 4
/** @brief Minimap wall cell color. */
# define MINIMAP_WALL_COLOR GRAY
/** @brief Minimap door cell color. */
# define MINIMAP_DOOR_COLOR BLACK
/** @brief Minimap player indicator color. */
# define MINIMAP_PLAYER_COLOR RED
/** @brief Exploration reveal radius around player. */
# define MINIMAP_EXPLORE_RADIUS 1
/** @brief Minimap floor cell color. */
# define MINIMAP_FLOOR_COLOR WHITE
/** @brief Minimap fog of war color. */
# define MINIMAP_FOG_COLOR LIGHT_GRAY
/** @brief Minimap external area color. */
# define MINIMAP_EXTERNAL_COLOR 0xFF222222
/** @brief Minimap player direction arrow color. */
# define MINIMAP_DIRECTION_COLOR 0xFF0000FF

/** @brief Maximum distance for fog effect. */
# define FOG_DISTANCE_MAX 30.0f
/** @brief Minimum fog intensity (darkest). */
# define FOG_MIN_INTENSITY 0.1f
/** @brief Distance where fog begins. */
# define FOG_DISTANCE_START 2.0f

/** @brief Base shading intensity for walls. */
# define SHADE_INTENSITY 0.95f
/** @brief Side wall shading factor (darker). */
# define SIDE_SHADE_FACTOR 0.85f
/** @brief Maximum shading intensity (brightest). */
# define SHADE_MAX_INTENSITY 1.0f
/** @brief Minimum shading intensity (darkest). */
# define SHADE_MIN_INTENSITY 0.30f

/** @brief Sprite type: enemy character. */
# define SPRITE_TYPE_ENEMY 1
/** @brief Sprite type: dead enemy. */
# define SPRITE_TYPE_ENEMY_DEAD 2
/** @brief Sprite type: health pickup. */
# define SPRITE_TYPE_HEALTH 3
/** @brief Sprite type: coin collectible. */
# define SPRITE_TYPE_COIN 4
/** @brief Sprite type: weapon sprite. */
# define SPRITE_TYPE_WEAPON 5
/** @brief Sprite type: projectile. */
# define SPRITE_TYPE_PROJECTILE 6

/** @brief Maximum player health points. */
# define MAX_HEALTH 100
/** @brief Damage dealt by enemy on contact. */
# define ENEMY_DAMAGE 10
/** @brief Health restored by health pickup. */
# define HEALTH_RESTORE 25
/** @brief Maximum enemy health points. */
# define ENEMY_HEALTH 100
/** @brief Damage dealt by projectile. */
# define PROJECTILE_DAMAGE 25
/** @brief Projectile movement speed. */
# define PROJECTILE_SPEED 10.0

/** @brief Cooldown between damage events in seconds. */
# define DAMAGE_COOLDOWN 1.0
/** @brief Maximum distance for sprite interaction. */
# define SPRITE_INTERACT_DISTANCE 0.8
/** @brief Sprite center offset for positioning. */
# define SPRITE_CENTER_OFFSET 0.5
/** @brief Enemy sprite movement speed. */
# define SPRITE_MOVE_SPEED 0.5

/** @brief Collision detection margin buffer. */
# define COLLISION_BUFFER 0.15
/** @brief Door center offset for interaction. */
# define DOOR_CENTER_OFFSET 0.5
/** @brief Door opening animation speed. */
# define DOOR_ANIM_SPEED 4.0
/** @brief Delta time to 60 FPS conversion factor. */
# define DELTA_TIME_FACTOR 60.0
/** @brief Door interaction detection radius. */
# define DOOR_RADIUS 1.75
/** @brief Keyboard input debounce cooldown. */
# define KEY_COOLDOWN 0.3
/** @brief Camera X coordinate scaling factor. */
# define CAMERA_X_FACTOR 2.0
/** @brief Camera X coordinate offset. */
# define CAMERA_X_OFFSET 1.0
/** @brief Center calculation divisor. */
# define CENTER_DIVISOR 2.0
/** @brief Pitch calculation factor. */
# define PITCH_FACTOR 4.0
/** @brief Minimum texture clamp value. */
# define TEXTURE_CLAMP_MIN 0
/** @brief Texture clamp one value. */
# define TEXTURE_CLAMP_ONE 1
/** @brief Crosshair cursor size in pixels. */
# define CURSOR_SIZE 32
/** @brief Direction arrow length divisor. */
# define DIRECTION_ARROW_DIVISOR 8
/** @brief Arrow width calculation divisor. */
# define ARROW_WIDTH_DIVISOR 4
/** @brief Minimum arrow length in pixels. */
# define MIN_ARROW_LENGTH 1
/** @brief Minimum arrow width in pixels. */
# define MIN_ARROW_WIDTH 1
/** @brief Center position calculation factor. */
# define CENTER_FACTOR 2
/** @brief Smooth interpolation factor A. */
# define SMOOTH_FACTOR_A 3.0f
/** @brief Smooth interpolation factor B. */
# define SMOOTH_FACTOR_B 2.0f
/** @brief Red channel bit shift for RGBA. */
# define COLOR_SHIFT_RED 24
/** @brief Green channel bit shift for RGBA. */
# define COLOR_SHIFT_GREEN 16
/** @brief Blue channel bit shift for RGBA. */
# define COLOR_SHIFT_BLUE 8
/** @brief Color channel byte mask. */
# define COLOR_MASK 0xFF
/** @brief Bytes per RGBA pixel. */
# define RGBA_BYTES 4
/** @brief Full map player indicator size. */
# define FULLMAP_PLAYER_SIZE 5
/** @brief Default minimap zoom scale. */
# define DEFAULT_MINIMAP_SCALE 1

#endif
