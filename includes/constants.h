/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#             */
/*   Updated: 2025/09/28 02:03:19 by jlacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define WHITE 0xFFFFFFFF
# define BLACK 0xFF000000
# define RED 0xFFFF0000
# define GRAY 0xFF888888
# define DARK_GRAY 0xFF444444

# define FOV_DEG 60
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.075
# define DIST_EPS 0.0001
# define PLANE_FACTOR 0.675
# define MOUSE_BORDER_ZONE 75
# define MOUSE_BORDER_SPEED 0.02
# define WALL_SLIDE_FACTOR 0.375
# define MOUSE_SENSITIVITY 0.0025

# define MINIMAP_OFFSET 10
# define MINIMAP_RESERVED_DIV 4
# define MINIMAP_MIN_SCALE 1
# define MINIMAP_MAX_SCALE 10
# define MINIMAP_WALL_COLOR GRAY
# define MINIMAP_FLOOR_COLOR WHITE
# define MINIMAP_DOOR_COLOR BLACK
# define MINIMAP_PLAYER_COLOR RED
# define MINIMAP_FOG_COLOR DARK_GRAY

# define SHADE_INTENSITY 0.85f
# define SHADE_MIN_INTENSITY 0.70f
# define SHADE_MAX_INTENSITY 1.0f

# define FOG_DISTANCE_START 2.0f
# define FOG_DISTANCE_MAX 30.0f
# define FOG_MIN_INTENSITY 0.1f
# define SIDE_SHADE_FACTOR 0.85f

#endif
