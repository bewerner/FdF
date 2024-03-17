/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_png.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:41:51 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_mesh_vertically(t_FdF *s)
{
	u_int32_t	i;
	u_int32_t	offset;

	i = 0;
	set_min_max_height(s);
	offset = s->min_height + ((s->max_height - s->min_height) / 2);
	while (i < s->vert_count)
	{
		s->mesh[i].z -= offset;
		i++;
	}
}

void	read_png(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_FdF *s)
{
	u_int32_t		i;
	u_int32_t		x;
	u_int32_t		y;

	i = 0;
	x = 0;
	y = 0;
	while (i < s->vert_count)
	{
		s->mesh[i].x = x;
		s->mesh[i].y = y;
		s->mesh[i].z = heightmap->pixels[i * 4];
		if (colormap)
			s->mesh[i].pixel.color = sample_texture(colormap, x, y);
		i++;
		x++;
		if (x == heightmap->width)
		{
			x = 0;
			y++;
		}
	}
	if (!colormap)
		set_vert_colors(s);
	center_mesh_vertically(s);
}

void	set_dimensions(
	mlx_texture_t *heightmap, mlx_texture_t *colormap, t_FdF *s)
{
	if (colormap && (heightmap->width != colormap->width
			|| heightmap->height != colormap->height))
	{
		mlx_delete_texture(heightmap);
		mlx_delete_texture(colormap);
		clean_exit("Both images need to have the same resolution!", s);
	}
	s->mesh_width = heightmap->width;
	s->mesh_height = heightmap->height;
	s->vert_count = heightmap->width * heightmap->height;
}

void	malloc_mesh(mlx_texture_t *heightmap, mlx_texture_t *colormap, t_FdF *s)
{
	s->mesh = (t_vert *)malloc(s->vert_count * sizeof(t_vert));
	if (!s->mesh)
	{
		mlx_delete_texture(heightmap);
		if (colormap)
			mlx_delete_texture(colormap);
		clean_exit("Memory allocation failed", s);
	}
}

void	init_png(char *file1, char *file2, t_FdF *s)
{
	mlx_texture_t	*heightmap;
	mlx_texture_t	*colormap;

	colormap = NULL;
	heightmap = mlx_load_png(file1);
	if (!heightmap)
		clean_exit(file1, s);
	if (file2)
	{
		colormap = mlx_load_png(file2);
		if (!colormap)
		{
			mlx_delete_texture(heightmap);
			clean_exit(file2, s);
		}
	}
	set_dimensions(heightmap, colormap, s);
	malloc_mesh(heightmap, colormap, s);
	read_png(heightmap, colormap, s);
	mlx_delete_texture(heightmap);
	if (colormap)
		mlx_delete_texture(colormap);
	s->height_scale = 1;
	if (!ft_strncmp(file1, "assets/maps/materials/", 22))
		s->height_scale = 0.2;
}
