/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_mesh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 01:32:21 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/13 01:34:47 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_mesh_dotted_edges(t_FdF *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = s->mesh_width;
	while (i < s->vert_count)
	{
		if (i % s->mesh_width)
			put_dotted_line(s->mesh[i], s->mesh[i - 1], s->dot_size, s);
		if (j < s->vert_count)
			put_dotted_line(s->mesh[i], s->mesh[j], s->dot_size, s);
		i++;
		j++;
	}
}

void	put_mesh_faces(t_FdF *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = s->mesh_width;
	while (j < s->vert_count)
	{
		if (i % s->mesh_width && s->mesh[i - 1].pixel.vis
			&& s->mesh[i].pixel.vis && s->mesh[j - 1].pixel.vis
			&& s->mesh[j].pixel.vis)
		{
			put_face((t_face){s->mesh[i - 1], s->mesh[i],
				s->mesh[j], s->mesh[j - 1]}, s);
		}
		i++;
		j++;
	}
}

void	put_mesh_edges(t_FdF *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = s->mesh_width;
	while (i < s->vert_count)
	{
		if (i % s->mesh_width)
			put_line(s->mesh[i].pixel, s->mesh[i - 1].pixel, s->line_thickness,
				s);
		if (j < s->vert_count)
			put_line(s->mesh[i].pixel, s->mesh[j].pixel, s->line_thickness, s);
		i++;
		j++;
	}
}

void	put_mesh_verts(t_FdF *s)
{
	size_t	i;

	i = 0;
	while (i < s->vert_count)
	{
		if (s->vert_size <= 1 && s->mesh[i].pixel.vis)
			put_pixel(s->canvas, s->mesh[i].pixel, 1, s);
		else if (s->mesh[i].pixel.vis
			&& s->mesh[i].pixel.x + s->vert_size + 2 >= 0
			&& s->mesh[i].pixel.y + s->vert_size + 2 >= 0
			&& s->mesh[i].pixel.x - s->vert_size - 2 <= (int)s->canvas->width
			&& s->mesh[i].pixel.y - s->vert_size - 2 <= (int)s->canvas->height)
			put_dot(s->canvas, s->mesh[i].pixel, s->vert_size, s);
		i++;
	}
}

void	put_mesh(t_FdF *s)
{
	ft_bzero(s->canvas->pixels, s->canvas->width * s->canvas->height * 4);
	if (s->draw_verts || s->draw_dotted_edges || s->draw_edges || s->draw_faces)
		project_mesh(s);
	if (s->draw_verts)
		put_mesh_verts(s);
	else if (s->draw_edges)
		put_mesh_edges(s);
	else if (s->draw_dotted_edges)
		put_mesh_dotted_edges(s);
	else if (s->draw_faces)
		put_mesh_faces(s);
}
