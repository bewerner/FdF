/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:45:38 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/15 17:25:01 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scroll_hook(double a, double scroll, void *param)
{
	t_FdF	*s;

	s = param;
	if (a || mlx_is_key_down(s->mlx, MLX_KEY_LEFT_SHIFT)
		|| mlx_is_key_down(s->mlx, MLX_KEY_RIGHT_SHIFT))
	{
		s->foc += (a + scroll) * (s->foc / 100);
		s->foc = fmin(fmax(s->foc, 300), 50000);
		s->camera_height = s->foc * 3.3333;
	}
	else
	{
		scroll = fmin((1500 - s->mesh_scale) / 100, scroll);
		s->initial_mesh_scale = s->mesh_scale;
		s->mesh_scale += (s->mesh_scale / 100) * scroll;
		s->mesh_scale = fmin(fmax(s->mesh_scale, 0.01), 1500);
		s->mesh_pos.x *= (1 + scroll / 100);
		s->mesh_pos.y *= (1 + scroll / 100);
		if (s->vert_size > 1)
			s->vert_size *= s->mesh_scale / s->initial_mesh_scale;
		s->vert_size = fmax(s->vert_size, 1);
		if (s->dot_size > 1)
			s->dot_size *= s->mesh_scale / s->initial_mesh_scale;
		s->dot_size = fmax(s->dot_size, 1);
	}
}

void	mouse_hook(	enum mouse_key button,		enum action action,
					enum modifier_key modifier, void *param			)
{
	t_FdF	*s;

	s = param;
	if (action == MLX_PRESS && !modifier)
	{
		s->mouse_buttons_pressed++;
		if (button == MLX_MOUSE_BUTTON_LEFT && s->clicked)
			s->mesh_pos = (t_vec2){0, 0};
		if (button == MLX_MOUSE_BUTTON_LEFT)
			s->clicked = 0.3;
		mlx_get_mouse_pos(s->mlx,
			&s->initial_cursor_pos.x, &s->initial_cursor_pos.y);
		mlx_set_cursor_mode(s->mlx, MLX_MOUSE_HIDDEN);
	}
	if (action == MLX_RELEASE && !modifier)
	{
		s->mouse_buttons_pressed = ft_imax(0, s->mouse_buttons_pressed - 1);
		if (!s->mouse_buttons_pressed)
		{
			mlx_set_cursor_mode(s->mlx, MLX_MOUSE_NORMAL);
			mlx_set_mouse_pos(s->mlx, s->initial_cursor_pos.x,
				s->initial_cursor_pos.y);
		}
	}
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_FdF	*s;

	s = param;
	mlx_resize_image(s->depth_map, width, height);
	if (!s->depth_map)
		clean_exit("mlx_resize_image failed", s);
	mlx_resize_image(s->canvas, width, height);
	if (!s->canvas)
		clean_exit("mlx_resize_image failed", s);
	mlx_resize_image(s->background, width, height);
	if (!s->background)
		clean_exit("mlx_resize_image failed", s);
}

void	init_hooks(t_FdF *s)
{
	mlx_key_hook(s->mlx, key_hook, s);
	mlx_mouse_hook(s->mlx, mouse_hook, s);
	mlx_cursor_hook(s->mlx, cursor_hook, s);
	mlx_scroll_hook(s->mlx, scroll_hook, s);
	mlx_resize_hook(s->mlx, resize_hook, s);
	mlx_loop_hook(s->mlx, main_loop, s);
	mlx_loop(s->mlx);
}
