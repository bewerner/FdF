/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skybox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 11:37:31 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return (r);
}

void	init_skybox_verts(t_vert *verts, t_vec3 start, t_vec3 stp1, t_vec3 stp2)
{
	t_vec3	pos;
	size_t	i;

	pos = start;
	verts[0].pos = pos;
	verts[0].pixel.u = 0;
	verts[0].pixel.v = 0;
	i = 1;
	while (i < 121)
	{
		pos = vec3_add(pos, stp1);
		verts[i].pixel.u = verts[i - 1].pixel.u + 0.1;
		verts[i].pixel.v = verts[i - 1].pixel.v;
		if (verts[i].pixel.u > 1)
		{
			pos = vec3_add(pos, stp2);
			verts[i].pixel.u = 0;
			verts[i].pixel.v = verts[i - 1].pixel.v + 0.1;
		}
		verts[i].pos = pos;
		i++;
	}
}

void	verify_allocation(mlx_texture_t *texture, char *path, t_FdF *s)
{
	if (!texture)
		clean_exit(path, s);
}

void	load_skybox_textures(uint8_t sky_number, t_FdF *s)
{
	char	path[28];

	delete_skybox_textures(s);
	ft_memmove(path, "assets/skyboxes/skyX_bk.png\0", 28);
	path[19] = sky_number + '0';
	s->skybox.bk_tex = mlx_load_png(path);
	verify_allocation(s->skybox.bk_tex, path, s);
	ft_memmove(path + 21, "dn", 2);
	s->skybox.dn_tex = mlx_load_png(path);
	verify_allocation(s->skybox.dn_tex, path, s);
	ft_memmove(path + 21, "ft", 2);
	s->skybox.ft_tex = mlx_load_png(path);
	verify_allocation(s->skybox.ft_tex, path, s);
	ft_memmove(path + 21, "lf", 2);
	s->skybox.lf_tex = mlx_load_png(path);
	verify_allocation(s->skybox.lf_tex, path, s);
	ft_memmove(path + 21, "rt", 2);
	s->skybox.rt_tex = mlx_load_png(path);
	verify_allocation(s->skybox.rt_tex, path, s);
	ft_memmove(path + 21, "up", 2);
	s->skybox.up_tex = mlx_load_png(path);
	verify_allocation(s->skybox.up_tex, path, s);
}

void	init_skybox(t_FdF *s)
{
	load_skybox_textures(1, s);
	init_skybox_verts(s->skybox.bk,
		(t_vec3){-1, -1, -1}, (t_vec3){0.2, 0, 0}, (t_vec3){-2.2, 0, 0.2});
	init_skybox_verts(s->skybox.ft,
		(t_vec3){1, 1, -1}, (t_vec3){-0.2, 0, 0}, (t_vec3){2.2, 0, 0.2});
	init_skybox_verts(s->skybox.lf,
		(t_vec3){-1, 1, -1}, (t_vec3){0, -0.2, 0}, (t_vec3){0, 2.2, 0.2});
	init_skybox_verts(s->skybox.rt,
		(t_vec3){1, -1, -1}, (t_vec3){0, 0.2, 0}, (t_vec3){0, -2.2, 0.2});
	init_skybox_verts(s->skybox.up,
		(t_vec3){-1, -1, -1}, (t_vec3){0, 0.2, 0}, (t_vec3){0.2, -2.2, 0});
	init_skybox_verts(s->skybox.dn,
		(t_vec3){1, -1, 1}, (t_vec3){0, 0.2, 0}, (t_vec3){-0.2, -2.2, 0});
}
