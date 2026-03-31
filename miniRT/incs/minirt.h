/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 16:47:34 by klima-do          #+#    #+#             */
/*   Updated: 2026/03/23 17:17:24 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define EPSILON 0.0001
# define SPECULAR_KV 0.5
# define SPECULAR_N 20
# define MIRROR 0.0
# define REFRACT 0.0
# define PATTERN_LEN 0.0
# define PATTERN_NUM 0
# define FOCAL_DIST 0.5
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define DECO_WIDTH 60
# define COLORDEF 0x81A1C1
# define BG_COLOR 0xCFCFFF
# define WHITE 0x00FFFFFF
# define BLACK 0x0000000
# define DARKGREY 0x333333
# define MAX_KEY 65535
# define MAX_REFLECT 5
# define ANTIALIASING_ON FALSE
# define PROGBAR_TEXT_W 90
# define PROGBAR_TEXT_H 12
# define PROGBAR_W 180
# define PROGBAR_H 12
# define MAX_THREADS 10
# ifdef __APPLE__
#  define IS_LINUX 0
#  define ESC_KEY 53
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define C_KEY 5
#  define I_KEY 34
#  define P_KEY 35
#  define L_KEY 37
# elif defined __unix__
#  define IS_LINUX 1
#  define ESC_KEY 65307
#  define A_KEY 97
#  define S_KEY 115
#  define P_KEY 112
#  define L_KEY 108
#  define C_KEY 99
#  define D_KEY 100
#  define I_KEY 105
# endif
# define MSG_USAGE "Usage: ./minirt scenes/mandatory.rt"
# define ERR_FILE_NOT_FOUND "file not found"
# define ERR_IS_NOT_RT_FILE "isn't a rt file"
# define ERR_FORBIDDEN_CHAR "contain forbidden character"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <sys/time.h>

# include "mlx.h"
# include "libft.h"
# include "objects.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum {
	BUMP = 0,
	TEXTURE = 1
};

typedef struct s_event
{
	int		key[MAX_KEY];
}	t_event;

typedef struct s_rt
{
	char			*path;
	float			width;
	float			height;
	float			aspectratio;
	float			cam_matrix[4][4];
	void			*mlx;
	void			*mlx_win;
	t_img			img;
	t_camera		camera;
	t_ambient		ambient;
	t_light			*light;
	t_obj			*objs;
	size_t			num_objs;
	t_event			event;
	int				display_info;
	t_color			bg_color;
	int				lnum;
	int				pnum;
	int				process;
	pthread_mutex_t	process_lock;
	char			*process_text;
	t_bool			is_processing;
}	t_rt;

typedef struct s_line_trd
{
	int			i;
	t_rt		*rt;
	pthread_t	trd;
}	t_line_trd;

/* window.c */
void	initialize_renderer(t_rt *rt, char *path);
void	shutdown_renderer(t_rt *rt);
int		handle_window_close(t_rt *rt);
void	destroy_renderer_state(t_rt *rt);

/* event.c */
void	initialize_event_hooks(t_rt *rt);

/* keyboard */
int		on_key_down(int key, t_rt *rt);
int		on_key_up(int key, t_rt *rt);

/* deco.c */
void	draw_overlay_frame(t_rt *rt, int width, int color);
void	draw_help_overlay(t_rt *rt);

/* progbar.c */
void	print_progress_console(float perc);
void	draw_progress_overlay(t_rt *rt);
void	draw_progress_box(t_rt *rt, int x, int y);
void	draw_progress_background(t_rt *rt, int x, int y);
void	draw_progress_column(t_rt *rt, int x, int y);
void	draw_progress_text(t_rt *rt, float perc);
char	*build_progress_text(float percent);

/* test.c */
void	init_test(t_rt *rt);

/* main.c */
int		msg_quit(char *s);

/* image.c*/
t_color	sample_texture_color(t_img *img, float xf, float yf);
void	putpixel(t_img *img, int x, int y, int color);
void	gen_img(t_rt *rt);
void	render_frame(t_rt *rt);
int		trace_primary_ray(t_rt *rt, float x, float y);
int		sample_antialiasing(t_rt *rt, float x, float y);

/* ray.c */
void	initialize_ray(t_ray *ray, t_vect *origin, t_vect *direction);
void	build_camera_basis(t_rt *rt);
t_vect	transform_camera_to_world(float matrix[4][4], t_vect *vector);
void	build_camera_ray(t_rt *rt, t_ray *ray, float x, float y);
t_vect	*point_at_ray_distance(t_vect *point, t_ray *ray, float distance);

/* lightray.c */
t_color	compute_specular_light(t_rays *rays, t_light *light);
t_color	compute_diffuse_light(t_rays *rays, t_light *light);
t_bool	is_shadowed(t_rt *rt, t_rays *rays, t_light *light);
t_color	trace_refraction(t_rt *rt, t_rays *rays, int max_reflect);
t_color	trace_reflection(t_rt *rt, t_rays *rays, int max_reflect);

/* raytrace.c */
t_color	trace_ray(t_rt *rt, t_rays *rays, int max_reflect);
t_obj	*find_closest_object_hit(t_ray *ray, t_obj *obj, t_hit *hit);

/* inter.c */
t_bool	intersect_sphere(t_ray *ray, t_sphere *sphere, t_hit *hit);
t_bool	intersect_plane(t_ray *ray, t_plane *plane, t_hit *hit);
t_bool	intersect_infinite_cylinder(t_ray *ray, t_cylinder *cylinder,
			t_hit *hit);
t_bool	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, t_hit *hit);
t_bool	intersect_cone_body(t_ray *ray, t_cone *cone, t_hit *hit);
t_bool	intersect_cone(t_ray *ray, t_cone *cone, t_hit *hit);
t_bool	intersect_triangle(t_ray *ray, t_triangle *triangle, t_hit *hit);
t_bool	intersect_torus(t_ray *ray, t_torus *torus, t_hit *hit);
int		intersect_object(t_ray *ray, t_obj *obj, t_hit *hit);

/* pattern.c */
void	initialize_pattern_basis(t_rt *rt, t_obj *obj);
t_color	resolve_pattern_color(t_obj *obj, t_vect phit);
void	map_cylindrical_uv(t_obj *obj, t_vect p, float *uv);
void	map_plane_uv(t_obj *obj, t_vect p, float *uv);
void	map_sphere_uv(t_obj *obj, t_vect p, float *uv);

/* bumpmap.c */
void	apply_bump_map(t_obj *obj, t_img *img, t_hit *hit);

/* vector.c */
t_vect	make_vector(float x, float y, float z);
float	vector_length(t_vect vector);
t_vect	vector_subtract(t_vect lhs, t_vect rhs);
t_vect	vector_add(t_vect lhs, t_vect rhs);
t_vect	vector_scale(t_vect vector, float scalar);
float	dot_product(t_vect lhs, t_vect rhs);
t_vect	cross_product(t_vect lhs, t_vect rhs);
float	point_distance(t_vect point_a, t_vect point_b);
t_vect	vector_negate(t_vect vector);
t_vect	*normalize_vector(t_vect *vector);
t_vect	reflect_vector(t_vect incident, t_vect normal);
t_vect	refract_vector(t_vect incident, t_vect normal, float eta);

/* color.c */
t_color	make_color(float r, float g, float b);
t_color	*scale_color_inplace(t_color *color, float factor);
t_color	scale_color(t_color color, float factor);
t_color	unpack_rgb_color(int packed_rgb);
int		pack_rgb_color(t_color color);
t_color	apply_light_contribution(t_color base_color, t_color light_color,
			float intensity);
t_color	blend_colors(t_color color_a, float weight_a, t_color color_b,
			float weight_b);
int		average_color_samples(t_color sample_colors[9]);
t_color	resolve_object_color(t_obj *obj, t_hit *hit);

/* quadratic.c */
t_bool	solve_quadratic_equation(t_quadratic *q);

/* object_utils.c */
void	append_object(t_obj *obj, t_obj **objs);
t_obj	*alloc_object(t_rt *rt, t_obj_id id);
void	destroy_objects(t_rt *rt, t_obj **objs);
void	normalize_scene_objects(t_rt *rt);
t_vect	*get_object_position(t_obj *obj);

/* file.c */
int		parse_scene_from_fd(t_rt *rt, int fd);
int		load_scene_file(t_rt *rt, char *path);
int		has_rt_extension(char *path);
int		validate_scene_requirements(t_rt *rt);
char	*normalize_scene_line(char *line);

/* number.c */
int		is_valid_float_literal(char *str);
int		is_valid_unsigned_number(char *str);

/* parsing.c */
int		parse_scene_line(t_rt *rt, char *line);
int		parse_vector3(char *str, t_vect *vect);
int		parse_rgb_color(char *str, t_color *color);
int		parse_dual_color(char *str, t_color *color, t_color *color2);
int		parse_float_value(char *str, float *num);
int		parse_size_value(char *str, size_t *num);
int		parse_resolution_settings(t_rt *rt, char *line);
int		parse_ambient_light(t_rt *rt, char *line);
int		parse_camera_definition(t_rt *rt, char *line, int i);
int		parse_point_light(t_rt *rt, char *line);
int		parse_plane_object(t_rt *rt, char **params, t_obj *obj);
int		parse_sphere_object(t_rt *rt, char **params, t_obj *obj);
int		parse_cylinder_object(t_rt *rt, char **params, t_obj *obj);
int		parse_cone_object(t_rt *rt, char **params, t_obj *obj);
int		parse_triangle_object(t_rt *rt, char **params, t_obj *obj);
int		parse_object_definition(t_rt *rt, char *line, t_obj_id id,
			int nb_params);
int		parse_object_modifiers(t_rt *rt, t_obj *obj, char **params, int i);
int		parse_specular_modifier(char *str, t_obj *obj);
int		parse_pattern_modifier(char *str, t_obj *obj);
int		parse_bump_modifier(char *param, t_obj *obj);
int		parse_texture_modifier(char *param, t_obj *obj);
int		is_invalid_xpm_path(char *path);

/* array_utils.c */
void	free_string_array(char *arr[]);
void	print_string_array(char *arr[]);
int		string_array_length(char *arr[]);

/* ligth_utils.c */
void	append_light(t_light *new_light, t_light **lights);
t_light	*alloc_light(t_rt *rt);
void	destroy_lights(t_light **lights);

/* convert.c */
float	parse_float_literal(char *str);
int		clamp_color_component(char *str);

/* error.c */
int		report_parsing_error(t_rt *rt, char **params, char *msg);
int		report_error(char *msg);

/* time.c */
double	get_elapsed_seconds(void);
void	render_multithreaded(t_rt *rt);

/* debug.c */
void	rt_dump(t_rt *rt);

#endif