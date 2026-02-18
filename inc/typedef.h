/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:16:27 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/15 22:06:09 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

typedef enum e_element
{
	E_NO = 0,
	E_SO,
	E_WE,
	E_EA,
	E_F,
	E_C,
	E_COUNT
}					t_element;

typedef struct s_mouse
{
	int				previous_x;
	int				x;
	int				y;
	double			sens;
}					t_mouse;

typedef struct s_parsing
{
	char			**textures_info;
	char			**map;
	char			player;
	int				width;
	int				height;
	int				fd;
	int				elements[E_COUNT];
}					t_parsing;

typedef struct s_keyboard
{
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			space;
	bool			key_right;
	bool			key_left;
	bool			control_left;
	bool			shift_left;
	bool			key_f;
	bool			key_l;
	bool			key_t;
	bool			key_i;
	bool			key_z;
	bool			key_x;
	bool			key_m;
	bool			key_caps_lock;
	bool			key_e;
	bool			key_num_one;
	bool			key_num_two;
	bool			key_num_three;
	bool			key_num_four;
	bool			key_num_five;
	bool			key_num_six;

}					t_keyboard;

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
}					t_mlx_data;

typedef struct texture_data
{
	uint32_t		arm_width;
	uint32_t		arm_height;
	uint32_t		terror_arm_width;
	uint32_t		terror_arm_height;
	int				horizon;
	int				flr_color;
	int				clng_color;
}					t_texture_data;

typedef struct s_texture
{
	void			*img;
	int				*data;
	int				width;
	int				height;
}					t_texture;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rotate_speed;
	double			fov;
}					t_player;

typedef struct s_images_data
{
	void			*img;
	char			*addr;
	int				bits_pixel;
	int				line_len;
	int				endian;
	int				width;
	int				height;
	float			*vignette;
}					t_img_data;

typedef struct s_minimap
{
	t_img_data		image;
	char			**map;
	int				width;
	int				height;
	double			zoom_level;
}					t_minimap;

typedef enum e_wall_face
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}					t_wall_face;

typedef enum e_hit_type
{
	HIT_WALL,
	HIT_DOOR
}					t_hit_type;

typedef struct s_rayhit
{
	int				map_x;
	int				map_y;
	int				side;
	double			dist;
	double			zbuffer[WIN_WIDTH];
	t_wall_face		face;
	t_hit_type		type;
}					t_rayhit;

typedef struct s_flags
{
	bool			terror_mode;
	bool			info;
	bool			minimap;
	bool			enemy_mini;
	bool			mouse_on;
	bool			music_on;
}					t_flags;

typedef struct s_sound
{
	pid_t			*pids;
	int				count;
	int				capacity;
	pid_t			terror_music_pid;
	pid_t			background_music_pid;
}					t_sound;

typedef struct s_default_values
{
	double			player_x;
	double			player_y;
	double			player_move_speed;
	double			player_rotation_speed;
	double			minimap_zoom_level;
	double			fov;
	double			terror_player_move_speed;
	char			**env;
	t_sound			sounds;
}					t_def_values;

typedef enum e_enemy_type
{
	ENEMY_GHOST,
	ENEMY_CTHULHU,
	ENEMY_SKELETON,
	ENEMY_SKELETON2,
	HANGED_SKELETON,
	WINNING_STAR
}					t_enemy_type;

typedef struct s_enemy
{
	double			x;
	double			y;
	double			move_speed;
	int				size;
	int				enemy_frame;
	int				enemy_timer;
	t_enemy_type	first_type;
	t_enemy_type	type;
}					t_enemy;

typedef struct s_node
{
	int				x;
	int				y;
}					t_node;

typedef struct s_dda
{
	int				start_x;
	int				start_y;
	double			delta_x;
	double			delta_y;
	double			side_x;
	double			side_y;
	int				step_x;
	int				step_y;
	int				side;
	int				wall_hit;
}					t_dda;

typedef struct s_render_scene
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				texture_x;
}					t_render_scene;

typedef struct s_player_move
{
	double			move_x;
	double			move_y;
}					t_player_move;

typedef struct s_draw_enemy
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				color;
	int				tex_y;
	int				d;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	double			distance;
}					t_draw_enemy;

typedef struct s_xpm_paths
{
	char			*normal[4];
	char			*terror[4];
	char			*ghost[4];
	char			*cthulhu[2];
	char			*skeleton[8];
	char			*hanged_skel[4];
	char			*star[3];
}					t_xpm_paths;

typedef struct s_quad_bounds
{
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}					t_quad_bounds;

typedef struct s_exit
{
	bool			active;
}					t_exit;

typedef struct s_general
{
	t_flags			*flags;
	t_texture_data	*texture_data;
	t_parsing		*parse;
	t_mlx_data		*mlx_data;
	t_img_data		*img_data;
	t_player		*player;
	t_keyboard		*kboard;
	t_minimap		*minimap;
	t_rayhit		*rayhit;
	t_img_data		*arm;
	t_img_data		*terror_arm;
	t_texture		*texture[4];
	t_texture		*terror_texture[4];
	t_texture		*ghost_enemy[4];
	t_texture		*cthulhu_enemy[2];
	t_texture		*skeleton_enemy[8];
	t_texture		*winning_exit[3];
	t_texture		*hanged_skel[4];
	t_texture		*door_texture;
	t_texture		*door_texture2;
	t_mouse			*mouse;
	t_def_values	*def_values;
	t_enemy			*enemy;
	t_dda			*dda;
	t_render_scene	*render;
	t_player_move	*player_move;
	t_draw_enemy	*draw_enemy;
	t_xpm_paths		*xpm_paths;
	t_exit			*exit;
	int				enemy_count;
}					t_gen;
