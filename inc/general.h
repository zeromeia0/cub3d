/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:16:21 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/17 18:25:22 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H
# include <X11/X.h>
# include <X11/extensions/Xfixes.h>
# include <sys/wait.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

// ###### WINDOW | MLX ######

# define WINDOW_NAME "cub3d"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000

// ###### PLAYER CONFIG ######

# define DEFAULT_PLAYER_MOVE_SPEED 0.05
# define DEFAULT_PLAYER_ROTATE_SPEED 0.045
# define DEFAULT_PLAYER_FOV 2.0

# define WALL_MARGIN 0.3

// ###### MOUSE CONFIG ######

# define MOUSE_SENS 0.0025

// ###### MINIMAP CONFIG ######

# define MINIMAP_SCALE 15
# define MINIMAP_RADIUS 6
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20
# define MINIMAP_PIXELS 200

// ###### COLORS ######

# define RED_CLR 0xFF0000
# define INFO_TEXT_COLOR 0xFFFFFF
# define MINIMAP_PLAYER_CLR 0xFFA500
# define MINIMAP_WALL_CLR 0xFFFFFF
# define DOOR_CLR 0x5ea7c4
# define MINIMAP_GROUND_CLR 0x161616
# define BLACK_CLR 0X000000
# define TERROR_ARM_TRANSPARENT 0XA8E61D

// ######ASSETS######

# define USER_HAND_XPM "./imgs/pixil-frame-0.xpm"
# define USER_HAND_PNG "./imgs/pixil-frame-0.png"
# define USER_TERROR_HAND_PNG "./imgs/terror_arm.png"
# define USER_TERROR_HAND_XPM "./imgs/terror_arm.xpm"
# define ENEMY_SPRITE_PNG "./imgs/enemy.png"
# define ENEMY_SPRITE_XPM "./imgs/enemy.xpm"

// ######SHADOW######
# define FOG_START 0.3
# define FOG_END 5.5

#endif