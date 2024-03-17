/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_mesh.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:58:59 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_directions(t_FdF *s)
{
	t_vec3	vec;

	vec = (t_vec3){1, 0, 0};
	vec.x = s->mesh_scale * cos(s->yaw);
	vec.y = s->mesh_scale * sin(s->yaw);
	vec.z = 0;
	s->x_dir.x = vec.x;
	s->x_dir.y = vec.y * cos(s->pitch) + vec.z * -sin(s->pitch);
	s->x_dir.z = vec.y * sin(s->pitch) + vec.z * cos(s->pitch);
	vec = (t_vec3){0, 1, 0};
	vec.x = s->mesh_scale * -sin(s->yaw);
	vec.y = s->mesh_scale * cos(s->yaw);
	vec.z = 0;
	s->y_dir.x = vec.x;
	s->y_dir.y = vec.y * cos(s->pitch) + vec.z * -sin(s->pitch);
	s->y_dir.z = vec.y * sin(s->pitch) + vec.z * cos(s->pitch);
	vec = (t_vec3){0, 0, 1};
	vec.x = 0;
	vec.y = 0;
	vec.z = s->height_scale * s->mesh_scale;
	s->z_dir.x = vec.x;
	s->z_dir.y = vec.y * cos(s->pitch) + vec.z * -sin(s->pitch);
	s->z_dir.z = vec.y * sin(s->pitch) + vec.z * cos(s->pitch);
}

t_vec3	object_to_world(t_vec3 obj, t_FdF *s)
{
	t_vec3	world;

	world.x = obj.x * s->x_dir.x + obj.y * s->y_dir.x + obj.z * s->z_dir.x;
	world.y = obj.x * s->x_dir.y + obj.y * s->y_dir.y + obj.z * s->z_dir.y;
	world.z = obj.x * s->x_dir.z + obj.y * s->y_dir.z + obj.z * s->z_dir.z;
	world.x += round(s->mesh_pos.x);
	world.y += round(s->mesh_pos.y);
	return (world);
}

void	project_mesh(t_FdF *s)
{
	uint32_t	i;
	t_vec3		pos;

	i = 0;
	set_directions(s);
	while (i < s->vert_count)
	{
		pos = object_to_world(s->mesh[i].pos, s);
		s->mesh[i].pixel.vis = 1;
		s->mesh[i].pixel.depth = s->camera_height - pos.z;
		if (s->orthographic)
			s->mesh[i].pixel.pos = (t_ivec2){round(pos.x), round(pos.y)};
		else
		{
			if (s->mesh[i].pixel.depth <= 0.1)
				s->mesh[i].pixel.vis = 0;
			s->mesh[i].pixel.x = round(pos.x * s->foc / s->mesh[i].pixel.depth);
			s->mesh[i].pixel.y = round(pos.y * s->foc / s->mesh[i].pixel.depth);
		}
		s->mesh[i].pixel.x += s->canvas->width / 2;
		s->mesh[i].pixel.y += s->canvas->height / 2;
		i++;
	}
}
