/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:28:28 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/17 17:28:48 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <sys/errno.h>

# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	1024

# define R 3
# define G 2
# define B 1
# define A 0

typedef union u_color
{
	uint32_t	color;
	uint8_t		channel[4];
}				t_color;

typedef struct s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct s_ivec2
{
	int32_t		x;
	int32_t		y;
}				t_ivec2;

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_pixel
{
	union
	{
		t_ivec2		pos;
		struct
		{
			int32_t	x;
			int32_t	y;
		};
	};
	double			depth;
	union
	{
		uint32_t	color;
		uint8_t		channel[4];
	};
	int8_t			vis;
	double			u;
	double			v;
}					t_pixel;

typedef struct s_vert
{
	union
	{
		t_vec3		pos;
		struct
		{
			double	x;
			double	y;
			double	z;
		};
	};
	t_pixel			pixel;
	t_vec3			world;
}					t_vert;

typedef struct s_tri
{
	t_pixel			a;
	t_pixel			b;
	t_pixel			c;
	t_ivec2			bbox[2];
	double			weight_a;
	double			weight_b;
	double			weight_c;
	double			area;
}					t_tri;

typedef struct s_face
{
	t_vert			a;
	t_vert			b;
	t_vert			c;
	t_vert			d;
}					t_face;

typedef struct s_skybox
{
	mlx_texture_t	*ft_tex;
	mlx_texture_t	*rt_tex;
	mlx_texture_t	*bk_tex;
	mlx_texture_t	*lf_tex;
	mlx_texture_t	*up_tex;
	mlx_texture_t	*dn_tex;
	t_vert			ft[121];
	t_vert			rt[121];
	t_vert			bk[121];
	t_vert			lf[121];
	t_vert			up[121];
	t_vert			dn[121];
}					t_skybox;

typedef struct s_FdF
{
	t_vert		*mesh;
	t_vec3		x_dir;
	t_vec3		y_dir;
	t_vec3		z_dir;
	t_skybox	skybox;
	size_t		mesh_height;
	size_t		mesh_width;
	t_vec2		mesh_pos;
	size_t		vert_count;
	int32_t		max_height;
	int32_t		min_height;
	mlx_image_t	*depth_map;
	mlx_image_t	*background;
	mlx_image_t	*canvas;
	mlx_image_t	*fps_image;
	mlx_t		*mlx;
	int8_t		anti_aliasing;
	int8_t		draw_fps;
	int8_t		draw_verts;
	int8_t		draw_edges;
	int8_t		draw_dotted_edges;
	int8_t		draw_faces;
	int8_t		draw_faces_edges;
	int8_t		draw_skybox;
	t_ivec2		initial_cursor_pos;
	double		height_scale;
	double		mesh_scale;
	double		initial_mesh_scale;
	double		pitch;
	double		yaw;
	double		vert_size;
	double		dot_size;
	int16_t		dot_density;
	uint8_t		line_thickness;
	int8_t		orthographic;
	int8_t		skybox_number;
	double		clicked;
	int8_t		mouse_buttons_pressed;
	double		foc;
	double		camera_height;
	int8_t		wsl_mode;
}				t_FdF;

//	cleanup.c
void		delete_skybox_textures(t_FdF *s);
void		clean_exit(char *error_message, t_FdF *s);

//	color_math.c
uint32_t	sample_texture(mlx_texture_t *image, int32_t x, int32_t y);
uint32_t	sample_image(mlx_image_t *image, int32_t x, int32_t y);
uint32_t	lerp_color(u_int32_t color_a, u_int32_t color_b, double factor);
uint32_t	fade_color(uint32_t col_a, uint32_t col_b, int32_t steps, int step);

//	cursor_hook.c
void		cursor_hook(double cursor_x, double cursor_y, void *param);

//	init_fdf.c
void		init_fdf(char *filepath, t_FdF *s);

//	init_hooks.c
void		init_hooks(t_FdF *s);

//	init_mesh.c
void		init_mesh(int argc, char **argv, t_FdF *s);

//	init_png.c
void		init_png(char *file1, char *file2, t_FdF *s);

//	init_skybox.c
void		load_skybox_textures(uint8_t sky_number, t_FdF *s);
void		init_skybox(t_FdF *s);

//	key_hook.c
void		key_hook(mlx_key_data_t keydata, void *param);

//	main_loop.c
void		main_loop(void *param);

//	project_mesh.c
void		project_mesh(t_FdF *s);

//	put_dot.c
void		put_dot(mlx_image_t *image, t_pixel pixel, uint16_t size, t_FdF *s);
void		put_dotted_line(t_vert a, t_vert b, uint16_t size, t_FdF *s);

//	put_face.c
void		put_face(t_face face, t_FdF *s);

//	put_line.c
uint8_t		line_is_visible(t_pixel a, t_pixel b, t_FdF *s);
void		put_line(t_pixel a, t_pixel b, uint8_t thickness, t_FdF *s);

//	put_mesh.c
void		put_mesh(t_FdF *s);

//	put_pixel.c
void		put_aa_pixel(mlx_image_t *img, t_pixel pixel, t_FdF *s);
void		put_pixel(mlx_image_t *img, t_pixel pixel, uint8_t size, t_FdF *s);

//	put_sky_tri.c
void		put_sky_tri(mlx_texture_t *texture, t_tri tri, t_FdF *s);

//	put_skybox.c
void		put_skybox(t_FdF *s);

//	set_vert_colors.c
void		set_vert_colors(t_FdF *s);
void		set_min_max_height(t_FdF *s);

//	validate_value.c
void		validate_value(char *str, t_FdF *s);

//	vector_math.c
double		get_length(t_ivec2 p1, t_ivec2 p2);
double		edge_function(t_ivec2 a, t_ivec2 b, t_ivec2 p);

#endif
