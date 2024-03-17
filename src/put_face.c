/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_face.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 01:40:30 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_outlines(t_tri tri, t_FdF *s)
{
	if (!s->draw_faces_edges)
		return ;
	tri.a.color = 0x000000FF;
	tri.b.color = 0x000000FF;
	tri.c.color = 0x000000FF;
	tri.a.depth -= 3;
	tri.b.depth -= 3;
	tri.c.depth -= 3;
	put_line(tri.a, tri.b, 1, s);
	put_line(tri.b, tri.c, 1, s);
	put_line(tri.c, tri.a, 1, s);
}

void	set_bounding_box(t_tri *tri, t_FdF *s)
{
	tri->bbox[0].x
		= ft_imin(ft_imax(ft_imin(ft_imin(tri->a.x, tri->b.x), tri->c.x), 0),
			s->canvas->width - 1);
	tri->bbox[0].y
		= ft_imin(ft_imax(ft_imin(ft_imin(tri->a.y, tri->b.y), tri->c.y), 0),
			s->canvas->height - 1);
	tri->bbox[1].x
		= ft_imax(ft_imin(ft_imax(ft_imax(tri->a.x, tri->b.x), tri->c.x),
				s->canvas->width - 1), 0);
	tri->bbox[1].y
		= ft_imax(ft_imin(ft_imax(ft_imax(tri->a.y, tri->b.y), tri->c.y),
				s->canvas->height - 1), 0);
}

void	put_tri_pixel(t_pixel pixel, t_tri tri, t_FdF *s)
{
	tri.weight_c /= tri.area;
	tri.weight_a /= tri.area;
	tri.weight_b /= tri.area;
	pixel.channel[R] = tri.a.channel[R] * tri.weight_a
		+ tri.b.channel[R] * tri.weight_b + tri.c.channel[R] * tri.weight_c;
	pixel.channel[G] = tri.a.channel[G] * tri.weight_a
		+ tri.b.channel[G] * tri.weight_b + tri.c.channel[G] * tri.weight_c;
	pixel.channel[B] = tri.a.channel[B] * tri.weight_a
		+ tri.b.channel[B] * tri.weight_b + tri.c.channel[B] * tri.weight_c;
	pixel.channel[A] = tri.a.channel[A] * tri.weight_a
		+ tri.b.channel[A] * tri.weight_b + tri.c.channel[A] * tri.weight_c;
	pixel.depth = tri.a.depth * tri.weight_a
		+ tri.b.depth * tri.weight_b + tri.c.depth * tri.weight_c;
	put_pixel(s->canvas, pixel, 1, s);
}

void	put_tri(t_tri tri, t_FdF *s)
{
	t_pixel	p;

	tri.area = edge_function(tri.a.pos, tri.b.pos, tri.c.pos);
	if (tri.area <= 0)
		return ;
	set_bounding_box(&tri, s);
	p.pos = tri.bbox[0];
	while (p.y <= tri.bbox[1].y)
	{
		tri.weight_c = edge_function(tri.a.pos, tri.b.pos, p.pos);
		if (tri.weight_c >= 0)
			tri.weight_a = edge_function(tri.b.pos, tri.c.pos, p.pos);
		if (tri.weight_a >= 0 && tri.weight_c >= 0)
			tri.weight_b = edge_function(tri.c.pos, tri.a.pos, p.pos);
		if (tri.weight_c >= 0 && tri.weight_a >= 0 && tri.weight_b >= 0)
			put_tri_pixel(p, tri, s);
		p.x++;
		if (p.x > tri.bbox[1].x)
		{
			p.x = tri.bbox[0].x;
			p.y++;
		}
	}
	put_outlines(tri, s);
}

void	put_face(t_face face, t_FdF *s)
{
	t_tri	t1;
	t_tri	t2;

	if (fabs(face.c.z - face.a.z) >= fabs(face.d.z - face.b.z))
	{
		t1.a = face.a.pixel;
		t1.b = face.b.pixel;
		t1.c = face.c.pixel;
		t2.a = face.a.pixel;
		t2.b = face.c.pixel;
		t2.c = face.d.pixel;
	}
	else
	{
		t1.a = face.a.pixel;
		t1.b = face.b.pixel;
		t1.c = face.d.pixel;
		t2.a = face.b.pixel;
		t2.b = face.c.pixel;
		t2.c = face.d.pixel;
	}
	if (t1.a.vis && t1.b.vis && t1.c.vis)
		put_tri(t1, s);
	if (t2.a.vis && t2.b.vis && t2.c.vis)
		put_tri(t2, s);
}
