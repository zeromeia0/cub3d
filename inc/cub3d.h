/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:16:24 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:35:00 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "general.h"
# include "typedef.h"

int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strcpy(char *s1, char *s2);
void			ft_print_matrix(char **matrix);
int				ft_matrix_len(char **matrix);
int				ultimate_file_validation(char *argv, t_parsing *parse);
int				init_all(t_gen *gen);
void			ft_free_matrix(char **matrix);
int				super_duper_hiper_free(void);
void			file_closer(void);
void			free_parsing(t_parsing *parse);
int				window_init(t_gen *gen, int w, int h);
int				handle_exit(int keysys);
void			ft_free_matrix_partial(char **matrix, int max_index);
int				png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int				png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int				rgb_to_hex(int r, int g, int b);
int				color_switch(char *str);
char			*space_skipper_shift(char *str);
int				game_loop(t_gen *gen);
void			copied_mlx_pixel_put(t_img_data *img_data, int x, int y,
					int color);
int				only_num(char *str);
int				validate_file(int fd);
char			**refactored_shit(char *file);
int				validate_file(int fd);
void			draw_static_minimap(t_gen *gen);
int				is_wall(t_gen *gen, int map_x, int map_y);
int				get_player_position(t_gen *gen);
void			direction_hits_wall(t_gen *gen, double ray_direction_x,
					double ray_direction_y);
void			draw_minimap(t_gen *gen);
int				move_player(int keysym, t_gen *gen);
void			ft_bzero(void *s, size_t n);
void			genesis(t_gen *gen);
void			draw_arm(t_gen *gen);
void			draw_minimap_tile(t_gen *gen, int row, int col, int color);
int				key_press(int key, t_gen *gen);
int				key_release(int key, t_gen *gen);
bool			collision(t_gen *gen, double next_y, double next_x);
void			render_scene(t_gen *gen);
void			draw_minimap(t_gen *gen);
int				key_handler(int keysym, t_gen *gen);
void			draw_minimap_tile(t_gen *gen, int row, int col, int color);
int				ft_abs(int n);
int				main_loop(t_gen *gen);
int				key_press(int key, t_gen *gen);
int				key_release(int key, t_gen *gen);
t_gen			*gen_stuff(void);
t_parsing		*parsing_init(void);
int				main_init(t_gen *gen, char *argv, char **environ);
int				start_window(t_gen *gen, char *argv);
void			render_scene(t_gen *gen);
void			draw_minimap_fov(t_gen *gen);
int				get_pixel_color(t_gen *gen, int x, int y);
int				get_pixel_color_img(t_img_data *img, int x, int y);
void			init_vignette(t_img_data *img);
void			ciclope_dos_xman(t_img_data *img, int *coords, int color);
int				png_name_to_xpm(t_gen *gen, char *xpm_files[4]);
void			rotate_player(t_gen *gen, double angle);
int				mouse_looking(t_gen *gen);
t_rayhit		castrate(t_gen *gen, double ray_direction_x,
					double ray_direction_y, bool interact);
void			draw_terror_arm(t_gen *gen);
int				apply_fog(int color, double dist);
void			play_music(t_gen *gen);
void			start_terror_music(t_gen *gen);
void			stop_all_sounds(t_gen *gen);
void			play_sound(t_gen *gen, const char *filename);
int				apply_fog(int color, double dist);
void			open_close_door(t_gen *gen);
t_texture		*load_xpm_texture(void *mlx_ptr, char *file);
void			*ft_memset(void *b, int c, size_t len);
void			handle_movement_keys(int key, t_gen *gen);
void			handle_modifier_keys(int key, t_gen *gen);
void			handle_view_keys(int key, t_gen *gen);
void			handle_toggle_keys(int key, t_gen *gen);
void			handle_audio_keys(int key, t_gen *gen);
void			release_movement_keys(int key, t_gen *gen);
void			release_modifier_keys(int key, t_gen *gen);
void			release_toggle_keys(int key, t_gen *gen);
void			init_line(int *coords, int *vars);
void			draw_line(t_img_data *img, int *coords, int *vars, int color);
void			perform_dda(t_gen *gen, double *vars);
void			calculate_ray_params(t_gen *gen, int x);
void			calculate_wall_dimensions(double dist, int *line_h,
					int *draw_start, int *draw_end);
void			calculate_wall_x(t_gen *gen, t_rayhit hit);
void			get_wall_texture(t_gen *gen, t_rayhit hit, t_texture **tex);
void			calculate_texture_x(t_gen *gen, t_rayhit hit, t_texture *tex,
					int *texture_x);
void			draw_wall_slice(t_gen *gen, int x, t_texture *tex,
					double hit_dist);
void			draw_ceiling_slice(t_gen *gen, int x, int draw_start);
void			draw_floor_slice(t_gen *gen, int x, int draw_end);
void			game_loop_part_one(t_gen *gen);
void			game_loop_part_two(t_gen *gen);
int				is_texture_path_invalid(t_parsing *data, char *line, int type);
int				validate_texture_file(char *path);
void			write_free(char *path);
bool			enemy_visible(t_gen *gen, double *distance_out, int i);
void			find_enemy_from_map(t_gen *gen, int i);
void			set_enemy(t_gen *gen, t_enemy *enemy, int row, int col);
int				count_enemies_in_map(t_gen *gen);
void			draw_enemy_minimap(t_gen *gen, int i);
void			draw_enemy_square(t_gen *gen, int px, int py);
void			draw_enemy(t_gen *gen, int i);
void			render_enemy_stripe(t_gen *gen, t_texture *tex, int stripe);
void			crazy_math_operations(t_gen *gen);
void			draw_enemy_variable_initialization(t_gen *gen, t_enemy *enemy);
int				enemy_dealer(t_gen *gen, t_texture **tex, t_enemy **enemy,
					int i);
void			update_enemy_animation(t_enemy *enemy, int i);
void			get_enemy_anim_stats(int type, int *max_frames, int *speed);
bool			enemy_visible(t_gen *gen, double *distance_out, int i);
bool			raycast_clear(t_gen *gen, double dx, double dy,
					double distance);
t_parsing		*parsing_init(void);
void			copy_matrix(char **original_matrix, char ***matrix_to_copy_ptr);
int				main_init(t_gen *gen, char *argv, char **environ);
int				mouse_init(t_gen *gen);
int				avg_img_init(t_gen *gen);
void			init_vignette(t_img_data *img);
int				general_texture_init(t_gen *gen);
void			wall_textures_init(t_gen *gen);
void			load_textures(t_gen *gen, t_texture **dst, char **xpm_files,
					int count);
int				texture_data_init(t_gen *gen);
int				minimap_init(t_gen *gen);
void			free_exit(t_gen *gen);
void			init_extra_keys(t_keyboard *kb);
int				keyboard_init(t_gen *gen);
int				rayhit_init(t_gen *gen);
int				player_init(t_gen *gen);
int				arm_init(t_gen *gen);
int				terror_arm_init(t_gen *gen);
int				basic_mlx_init(t_gen *gen);
int				init_flags(t_gen *gen);
int				def_values_init(t_gen *gen);
int				enemy_init(t_gen *gen);
int				goated_checker(t_draw_enemy *d, t_texture *t);
int				dda_init(t_gen *gen);
int				render_scene_init(t_gen *gen);
int				player_move_init(t_gen *gen);
int				init_draw_enemy(t_gen *gen);
int				init_all(t_gen *gen);
void			stop_background_and_terror(t_sound *sounds);
void			play_looped_background(t_gen *gen, const char *filename,
					int is_terror);
void			background_supervisor(t_gen *gen, const char *filename,
					int is_terror);
void			stop_background_music(t_sound *sounds);
void			exec_sound(t_gen *gen, const char *filename);
int				exit_init(t_gen *gen);
void			update_enemy_modes(t_gen *gen);
void			update_enemy_animation(t_enemy *enemy, int i);
void			find_enemy_from_map(t_gen *gen, int i);
void			update_enemy(t_gen *gen, int i);
void			draw_enemy(t_gen *gen, int i);
void			draw_enemy_minimap(t_gen *gen, int i);
int				count_enemies_in_map(t_gen *gen);
bool			enemy_visible(t_gen *gen, double *distance_out, int i);
void			set_valid_exit(t_gen *gen);
int				parser(t_gen *gen, int argc, char **argv);
int				is_map_valid(t_parsing *data);
int				construct_map_and_textures(t_parsing *data);
int				not_last_element(t_parsing *data);
int				is_header_line(t_parsing *data, char *line);
int				check_all_elements(t_parsing *data, char *line);
int				is_rgb_colours_invalid(t_parsing *data, char *line, char c,
					int type);
int				is_header_line_with_validation(t_parsing *data, char *line);
void			free_parsing(t_parsing *parse);
void			free_texture(void *mlx_ptr, t_texture *tex);
void			free_images(t_gen *gen);
void			free_textures(t_gen *gen);
void			free_all_resources(t_gen *gen);
void			free_arm_object(t_gen *gen, t_img_data *arm);
void			free_minimap(t_gen *gen);
char			**create_copy_map(t_parsing *data);
void			free_enemies(t_gen *gen);
void			free_game_objects(t_gen *gen);
void			free_input_and_raycast(t_gen *gen);
void			free_config_and_parsing(t_gen *gen);
char			*print_helper(char *which_info, double what_to_convert);
void			print_info(t_gen *gen);
void			clear_image(t_img_data *img, int color);
void			rotate_player(t_gen *gen, double angle);
void			calculate_player_movement(t_gen *gen);
char			*ft_dtoa_fixed(double v);
char			*print_helper(char *which_info, double what_to_convert);
void			apply_vignette_to_image(t_gen *gen, t_img_data *img);
void			apply_vignette_pixel(t_img_data *img, int x, int y);
void			draw_minimap_player(t_gen *gen);
void			process_fov_ray(t_gen *gen, int i, int num_rays);
void			draw_minimap_fov(t_gen *gen);
int				is_wall(t_gen *gen, int map_x, int map_y);
void			draw_minimap_tile_one(t_gen *gen, int x, int y, int color);
int				get_minimap_tile_color(t_gen *gen, int map_x, int map_y);
void			draw_minimap_area(t_gen *gen, int start_x, int start_y);
void			draw_minimap_enemies(t_gen *gen);
void			draw_minimap(t_gen *gen);
void			init_start(t_gen *gen);
void			init_delta(t_gen *gen, double ray_x, double ray_y);
void			init_step_x(t_gen *gen, double ray_x);
void			init_step_y(t_gen *gen, double ray_y);
void			dda_step(t_gen *gen);
int				check_hit(t_gen *gen, bool interact, t_rayhit *hit);
void			finalize_hit(t_gen *gen, double ray_x, double ray_y,
					t_rayhit *hit);
t_rayhit		castrate(t_gen *gen, double ray_x, double ray_y, bool interact);
void			update_game_state(t_gen *gen);
void			update_player(t_gen *gen);
char			*get_next_line(int fd);
int				contains_tab(char *s);
int				is_line_empty(char *line);
void			wall_textures_init(t_gen *gen);
int				init_xpm_paths(t_gen *gen);
void			free_double(char **arg);
int				ft_clamp(int value, int min, int max);
void			load_all_textures(t_gen *gen, t_xpm_paths *paths);
char			*ft_strchr(const char *s, int c);
void			free_xpm_paths(t_xpm_paths *paths);
void			toggle_flag(bool *key_state, bool *flag);
int				ft_isdigit(int c);
void			set_quad_x_bounds(t_gen *gen, t_quad_bounds *b, int quadrant,
					int mid_x);
void			set_quad_y_bounds(t_gen *gen, t_quad_bounds *b, int quadrant,
					int mid_y);
t_quad_bounds	get_quadrant_bounds(t_gen *gen, int quadrant);
void			get_quadrant_priority(int player_q, int order[4]);

char			*ft_strdup(const char *s);
char			*ft_strrchr(const char *s, int c);
void			ft_bzero(void *s, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				ft_strlen(const char *str);
void			handle_terror_toggle(int key, t_gen *gen);
void			handle_misc_toggles(int key, t_gen *gen);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strcpy(char *s1, char *s2);
void			*ft_calloc(size_t nmemb, size_t size);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *nptr);
char			*ft_strncpy(char *dst, char *srce, int n);
char			*ft_strcat(char *dst, char *srce);
char			*ft_itoa(int n);
char			*ft_strjoin(char *s1, char *s2);
void			ft_putstr_fd(char *s, int fd);
int				ft_str_count(char *str, char c);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				is_set(char c, const char *set);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strcpy(char *s1, char *s2);
void			ft_print_matrix(char **matrix);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_str_count(char *str, char c);
int				apply_fog(int color, double dist);
char			*ft_split_strndup(const char *s, char c);
void			*free_all(char **strs, int count);
char			**alloc_mem(int str_count);
char			**ft_split(char const *s, char c);
int				is_space(char c);
int				ft_atoi(const char *nptr);
int				ft_matrix_len(char **matrix);
int				png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int				color_switch(char *str);
int				rgb_to_hex(int r, int g, int b);
char			*space_skipper_shift(char *str);
void			copied_mlx_pixel_put(t_img_data *img_data, int x, int y,
					int color);
int				only_num(char *str);
void			set_player_dir(t_player *p, char c);
void			search_in_matrix(t_gen *gen, char c);
int				ft_abs(int n);
char			*ft_strncpy(char *dst, char *srce, int n);
char			*ft_strcat(char *dst, char *srce);
int				png_name_to_xpm(t_gen *gen, char *xpm_files[4]);
size_t			ft_putnbr_fake(int n);
char			*ft_itoa(int n);
char			*ft_strjoin(char *s1, char *s2);
int				ft_clamp(int value, int min, int max);
void			ft_putstr_fd(char *s, int fd);
t_texture		*load_xpm_texture(void *mlx_ptr, char *file);
void			open_close_door(t_gen *gen);
void			*ft_memset(void *b, int c, size_t len);
int				contains_tab(char *line);
char			*ft_strchr(const char *s, int c);

#endif