/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 04:36:17 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_rotation(t_vec2 distance, t_FdF *s)
{
	s->yaw -= (double)distance.x / 300;
	if (s->yaw > 2 * M_PI)
		s->yaw -= 2 * M_PI;
	if (s->yaw < 0)
		s->yaw += 2 * M_PI;
	s->pitch -= (double)distance.y / 300;
	s->pitch = fmax(fmin(s->pitch, M_PI), 0);
}

void	cursor_hook(double cursor_x, double cursor_y, void *param)
{
	t_FdF	*s;
	t_vec2	distance;

	s = param;
	s->clicked = 0;
	if (!mlx_is_mouse_down(s->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& !mlx_is_mouse_down(s->mlx, MLX_MOUSE_BUTTON_MIDDLE)
		&& !mlx_is_mouse_down(s->mlx, MLX_MOUSE_BUTTON_RIGHT))
		return ;
	distance.x = cursor_x - s->initial_cursor_pos.x;
	distance.y = cursor_y - s->initial_cursor_pos.y;
	if (mlx_is_mouse_down(s->mlx, MLX_MOUSE_BUTTON_MIDDLE))
		s->height_scale -= (double)distance.y / 500;
	if (mlx_is_mouse_down(s->mlx, MLX_MOUSE_BUTTON_RIGHT))
		set_rotation(distance, s);
	if (mlx_is_mouse_down(s->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (!s->orthographic)
			distance = (t_vec2){distance.x * 3.3333, distance.y * 3.3333};
		s->mesh_pos.x += distance.x;
		s->mesh_pos.y += distance.y;
	}
	if (CURSOR_SETTABLE)
		mlx_set_mouse_pos(s->mlx, s->initial_cursor_pos.x, s->initial_cursor_pos.y);
	else
		s->initial_cursor_pos = (t_ivec2){cursor_x, cursor_y};
}
