/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/05 21:43:51 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define PI 3.14159265358979323846

# define RED 0xFFFF0000
# define GRAY 0xFF888888
# define BLACK 0xFF000000
# define WHITE 0xFFFFFFFF
# define LIGHT_GRAY 0xFFCCCCCC

# define EPSILON 0.0001
# define PLANE_FACTOR 0.675
# define ROTATION_SPEED 0.1
# define MOVEMENT_SPEED 0.075
# define WALL_SLIDE_FACTOR 0.375
# define MOUSE_SENSITIVITY 0.0025

# define MINIMAP_OFFSET 10
# define MINIMAP_MIN_SCALE 1
# define MINIMAP_MAX_SCALE 10
# define MINIMAP_RESERVED_DIV 4
# define MINIMAP_SCALE_DIVISOR 10
# define MINIMAP_SIZE_DIVISOR 10
# define MINIMAP_MIN_SIZE 8
# define MINIMAP_BORDER_OFFSET 4
# define MINIMAP_WALL_COLOR GRAY
# define MINIMAP_DOOR_COLOR BLACK
# define MINIMAP_PLAYER_COLOR RED
# define MINIMAP_EXPLORE_RADIUS 1
# define MINIMAP_FLOOR_COLOR WHITE
# define MINIMAP_FOG_COLOR LIGHT_GRAY
# define MINIMAP_EXTERNAL_COLOR 0xFF222222
# define MINIMAP_DIRECTION_COLOR 0xFF0000FF

# define FOG_DISTANCE_MAX 30.0f
# define FOG_MIN_INTENSITY 0.1f
# define FOG_DISTANCE_START 2.0f

# define SHADE_INTENSITY 0.95f
# define SIDE_SHADE_FACTOR 0.85f
# define SHADE_MAX_INTENSITY 1.0f
# define SHADE_MIN_INTENSITY 0.30f

# define SPRITE_TYPE_ENEMY 1
# define SPRITE_TYPE_ENEMY_DEAD 2
# define SPRITE_TYPE_HEALTH 3
# define SPRITE_TYPE_COIN 4
# define SPRITE_TYPE_WEAPON 5
# define SPRITE_TYPE_PROJECTILE 6

# define MAX_HEALTH 100
# define ENEMY_DAMAGE 10
# define HEALTH_RESTORE 25
# define ENEMY_HEALTH 100
# define PROJECTILE_DAMAGE 25
# define PROJECTILE_SPEED 10.0

# define DAMAGE_COOLDOWN 1.0
# define SPRITE_INTERACT_DISTANCE 0.8
# define SPRITE_CENTER_OFFSET 0.5
# define SPRITE_MOVE_SPEED 0.5

# define COLLISION_BUFFER 0.15
# define DOOR_CENTER_OFFSET 0.5
# define DOOR_ANIM_SPEED 4.0
# define DELTA_TIME_FACTOR 60.0
# define DOOR_RADIUS 1.75
# define KEY_COOLDOWN 0.3
# define CAMERA_X_FACTOR 2.0
# define CAMERA_X_OFFSET 1.0
# define CENTER_DIVISOR 2.0
# define PITCH_FACTOR 4.0
# define TEXTURE_CLAMP_MIN 0
# define TEXTURE_CLAMP_ONE 1
# define CURSOR_SIZE 32
# define DIRECTION_ARROW_DIVISOR 8
# define ARROW_WIDTH_DIVISOR 4
# define MIN_ARROW_LENGTH 1
# define MIN_ARROW_WIDTH 1
# define CENTER_FACTOR 2
# define SMOOTH_FACTOR_A 3.0f
# define SMOOTH_FACTOR_B 2.0f
# define COLOR_SHIFT_RED 24
# define COLOR_SHIFT_GREEN 16
# define COLOR_SHIFT_BLUE 8
# define COLOR_MASK 0xFF
# define RGBA_BYTES 4
# define FULLMAP_PLAYER_SIZE 5
# define DEFAULT_MINIMAP_SCALE 3

#endif
