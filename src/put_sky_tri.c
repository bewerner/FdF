/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sky_tri.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:06:28 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_bounding_box(t_tri *tri, t_FdF *s)
{
	tri->bbox[0].x
		= ft_imin(ft_imax(ft_imin(ft_imin(tri->a.x, tri->b.x), tri->c.x), 0),
			s->background->width - 1);
	tri->bbox[0].y
		= ft_imin(ft_imax(ft_imin(ft_imin(tri->a.y, tri->b.y), tri->c.y), 0),
			s->background->height - 1);
	tri->bbox[1].x
		= ft_imax(ft_imin(ft_imax(ft_imax(tri->a.x, tri->b.x), tri->c.x),
				s->background->width - 1), 0);
	tri->bbox[1].y
		= ft_imax(ft_imin(ft_imax(ft_imax(tri->a.y, tri->b.y), tri->c.y),
				s->background->height - 1), 0);
}

void	put_sky_pixel(mlx_texture_t *tex, t_pixel pixel, t_tri tri, t_FdF *s)
{
	double	u;
	double	v;

	tri.weight_c /= tri.area;
	tri.weight_a /= tri.area;
	tri.weight_b /= tri.area;
	u = tri.a.u + (tri.b.u - tri.a.u) * tri.weight_b;
	v = tri.a.v + (tri.c.v - tri.a.v) * tri.weight_c;
	pixel.color = sample_texture(tex, (tex->width - 1) * u,
			(tex->height - 1) * v);
	mlx_put_pixel(s->background, pixel.x, pixel.y, pixel.color);
}

void	put_sky_tri(mlx_texture_t *texture, t_tri tri, t_FdF *s)
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
		if (tri.weight_c >= 0 && tri.weight_a >= 0)
			tri.weight_b = edge_function(tri.c.pos, tri.a.pos, p.pos);
		if (tri.weight_c >= 0 && tri.weight_a >= 0 && tri.weight_b >= 0)
			put_sky_pixel(texture, p, tri, s);
		p.x++;
		if (p.x > tri.bbox[1].x)
		{
			p.x = tri.bbox[0].x;
			p.y++;
		}
	}
}
