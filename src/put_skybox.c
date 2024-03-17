/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_skybox.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:19:33 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_skybox(t_vert *verts, t_FdF *s)
{
	size_t		i;
	t_vec3		tmp;

	i = 0;
	while (i < 121)
	{
		tmp.x = verts[i].x;
		tmp.y = verts[i].y;
		tmp.x = verts[i].x * cos(s->yaw) + verts[i].y * -sin(s->yaw);
		tmp.y = verts[i].x * sin(s->yaw) + verts[i].y * cos(s->yaw);
		tmp.z = tmp.y;
		tmp.y = tmp.y * cos(s->pitch) + verts[i].z * -sin(s->pitch);
		tmp.z = tmp.z * sin(s->pitch) + verts[i].z * cos(s->pitch);
		verts[i].pixel.vis = 1;
		if (tmp.z <= 0)
			verts[i].pixel.vis = 0;
		verts[i].pixel.x = round(tmp.x * s->foc / -tmp.z);
		verts[i].pixel.y = round(tmp.y * s->foc / -tmp.z);
		verts[i].pixel.depth = tmp.z;
		verts[i].pixel.x += s->canvas->width / 2;
		verts[i].pixel.y += s->canvas->height / 2;
		i++;
	}
}

void	subdivide_sky_face(mlx_texture_t *texture, t_vert *vert, t_FdF *s)
{
	size_t	i;
	t_tri	tri;

	i = 12;
	while (i < 121)
	{
		if (i % 11)
		{
			tri.a = vert[i - 12].pixel;
			tri.b = vert[i - 11].pixel;
			tri.c = vert[i - 1].pixel;
			if (tri.a.vis && tri.b.vis && tri.c.vis)
				put_sky_tri(texture, tri, s);
			tri.a = vert[i].pixel;
			tri.b = vert[i - 1].pixel;
			tri.c = vert[i - 11].pixel;
			if (tri.a.vis && tri.b.vis && tri.c.vis)
				put_sky_tri(texture, tri, s);
		}
		i++;
	}
}

void	put_skybox(t_FdF *s)
{
	project_skybox(s->skybox.bk, s);
	project_skybox(s->skybox.ft, s);
	project_skybox(s->skybox.lf, s);
	project_skybox(s->skybox.rt, s);
	project_skybox(s->skybox.up, s);
	project_skybox(s->skybox.dn, s);
	subdivide_sky_face(s->skybox.bk_tex, s->skybox.bk, s);
	subdivide_sky_face(s->skybox.ft_tex, s->skybox.ft, s);
	subdivide_sky_face(s->skybox.lf_tex, s->skybox.lf, s);
	subdivide_sky_face(s->skybox.rt_tex, s->skybox.rt, s);
	subdivide_sky_face(s->skybox.up_tex, s->skybox.up, s);
	subdivide_sky_face(s->skybox.dn_tex, s->skybox.dn, s);
}
