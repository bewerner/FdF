/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:55:23 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/14 14:47:26 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_draw_mode(mlx_key_data_t keydata, t_FdF *s)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key >= MLX_KEY_1 && keydata.key <= MLX_KEY_6)
	{
		s->draw_verts = 0;
		s->draw_edges = 0;
		s->draw_dotted_edges = 0;
		s->draw_faces = 0;
		s->draw_faces_edges = 0;
	}
	if (keydata.key == MLX_KEY_1)
		s->draw_verts = 1;
	if (keydata.key == MLX_KEY_2)
		s->draw_dotted_edges = 1;
	if (keydata.key == MLX_KEY_3)
		s->draw_edges = 1;
	if (keydata.key == MLX_KEY_4 || keydata.key == MLX_KEY_5)
		s->draw_faces = 1;
	if (keydata.key == MLX_KEY_5)
		s->draw_faces_edges = 1;
	if (keydata.key == MLX_KEY_A)
		if (s->draw_edges)
			s->anti_aliasing = !s->anti_aliasing;
	if (keydata.key == MLX_KEY_F)
		s->draw_fps = !s->draw_fps;
}

void	set_projection_type(mlx_key_data_t keydata, t_FdF *s)
{
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_I)
	{
		s->yaw = M_PI / 180 * 45;
		s->pitch = M_PI / 180 * (90 - 35.264);
	}
	if (keydata.key == MLX_KEY_P && s->orthographic)
	{
		s->orthographic = 0;
		s->mesh_scale *= s->foc / (s->camera_height / 11.1111);
		s->mesh_pos.x *= 3.3333;
		s->mesh_pos.y *= 3.3333;
	}
	if ((keydata.key == MLX_KEY_O || keydata.key == MLX_KEY_I)
		&& !s->orthographic)
	{
		s->orthographic = 1;
		s->mesh_scale /= s->foc / (s->camera_height / 11.1111);
		s->mesh_pos.x /= 3.3333;
		s->mesh_pos.y /= 3.3333;
	}
	if (keydata.key == MLX_KEY_R)
		s->mesh_pos = (t_vec2){0, 0};
}

void	set_line_and_dot_size(mlx_key_data_t keydata, t_FdF *s)
{
	if (keydata.key == MLX_KEY_DOWN && keydata.action)
	{
		if (s->draw_edges && !s->anti_aliasing)
			s->line_thickness = ft_imax(s->line_thickness - 2, 1);
		else if (s->draw_dotted_edges)
			s->dot_size = ft_imax(s->dot_size - 2, 1);
		else if (s->draw_verts)
			s->vert_size = ft_imax(s->vert_size - 2, 1);
	}
	if (keydata.key == MLX_KEY_UP && keydata.action)
	{
		if (s->draw_edges && !s->anti_aliasing)
			s->line_thickness = ft_imax(s->line_thickness + 2, 1);
		else if (s->draw_dotted_edges)
			s->dot_size = ft_imax(s->dot_size + 2, 1);
		else if (s->draw_verts)
			s->vert_size = ft_imax(s->vert_size + 2, 1);
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action)
		if (s->draw_dotted_edges)
			s->dot_density = ft_imax(s->dot_density - 1, 1);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action)
		if (s->draw_dotted_edges)
			s->dot_density = ft_imax(s->dot_density + 1, 1);
}

void	set_skybox_number(mlx_key_data_t keydata, t_FdF *s)
{
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (keydata.modifier == MLX_SHIFT)
			s->draw_skybox = !s->draw_skybox;
		else
		{
			s->skybox_number++;
			if (s->skybox_number > 3)
				s->skybox_number = 1;
			load_skybox_textures(s->skybox_number, s);
			s->draw_skybox = 1;
		}
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_FdF	*s;

	s = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(s->mlx);
	set_draw_mode(keydata, s);
	set_projection_type(keydata, s);
	set_skybox_number(keydata, s);
	if (keydata.modifier != MLX_SHIFT)
		set_line_and_dot_size(keydata, s);
	else if (keydata.key == MLX_KEY_UP && keydata.action)
		s->height_scale += 0.025;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action)
		s->height_scale -= 0.025;
}
