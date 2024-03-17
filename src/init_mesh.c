/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mesh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:30:56 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/17 10:48:57 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_mesh(t_FdF *s)
{
	t_vec2	center;
	size_t	i;

	center.x = (double)(s->mesh_width - 1) / 2;
	center.y = (double)(s->mesh_height - 1) / 2;
	i = 0;
	while (i < s->vert_count)
	{
		s->mesh[i].x -= center.x;
		s->mesh[i].y -= center.y;
		i++;
	}
}

int8_t	is_fdf(char *filepath)
{
	if (ft_strrchr(filepath, '.'))
		if (!ft_strncmp(ft_strrchr(filepath, '.'), ".fdf\0", 5))
			return (1);
	return (0);
}

int8_t	is_png(char *filepath)
{
	if (ft_strrchr(filepath, '.'))
		if (!ft_strncmp(ft_strrchr(filepath, '.'), ".png\0", 5))
			return (1);
	return (0);
}

void	init_mesh(int argc, char **argv, t_FdF *s)
{
	if (argc == 2 && is_fdf(argv[1]))
	{
		init_fdf(argv[1], s);
		s->draw_edges = 1;
		s->anti_aliasing = 1;
		s->orthographic = 1;
	}
	else if (argc == 2 && is_png(argv[1]))
		init_png(argv[1], argv[2], s);
	else if (argc == 3 && is_png(argv[1]) && is_png(argv[2]))
		init_png(argv[1], argv[2], s);
	else
	{
		ft_putstr_fd("Wrong file format! Allowed formats:\n", 2);
		ft_putstr_fd("- One .fdf file  (heightmap)\n", 2);
		ft_putstr_fd("- One .png file  (heightmap)\n", 2);
		ft_putstr_fd("- Two .png files (heightmap and colormap)\n", 2);
		exit (1);
	}
	if (!s->draw_edges)
		s->draw_verts = 1;
	center_mesh(s);
}
