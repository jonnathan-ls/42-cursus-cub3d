/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/10/04 00:16:12 by jlacerda         ###   ########.fr       */
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

# define FOV_DEG 60
# define ROT_SPEED 0.1
# define DIST_EPS 0.0001
# define MOVE_SPEED 0.075
# define PLANE_FACTOR 0.675
# define MOUSE_BORDER_ZONE 75
# define MOUSE_BORDER_SPEED 0.02
# define WALL_SLIDE_FACTOR 0.375
# define MOUSE_SENSITIVITY 0.0025

# define MINIMAP_OFFSET 10
# define MINIMAP_MIN_SCALE 1
# define MINIMAP_MAX_SCALE 10
# define MINIMAP_RESERVED_DIV 4
# define MINIMAP_WALL_COLOR GRAY
# define MINIMAP_DOOR_COLOR BLACK
# define MINIMAP_PLAYER_COLOR RED
# define MINIMAP_DIR_COLOR 0xFF0000FF
# define MINIMAP_FLOOR_COLOR WHITE
# define MINIMAP_FOG_COLOR LIGHT_GRAY
# define MINIMAP_EXTERNAL_COLOR 0xFF222222
# define MINIMAP_EXPLORE_RADIUS 1

# define SHADE_INTENSITY 0.85f
# define SHADE_MAX_INTENSITY 1.0f
# define SHADE_MIN_INTENSITY 0.70f

# define FOG_DISTANCE_MAX 30.0f
# define FOG_MIN_INTENSITY 0.1f
# define FOG_DISTANCE_START 2.0f
# define SIDE_SHADE_FACTOR 0.85f

#endif
