/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:51:18 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/13 02:29:17 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_settings(t_FdF *s)
{
	s->mesh_scale = ft_imin(s->mlx->width, s->mlx->height);
	s->mesh_scale /= ft_imax(s->mesh_width, s->mesh_height)
		+ ft_imax(s->max_height, -s->min_height);
	s->mesh_scale = fmax(s->mesh_scale * 0.6, 0.01);
	if (!s->orthographic)
		s->mesh_scale *= 3.3333;
	s->line_thickness = 1;
	s->vert_size = 1;
	s->dot_size = 1;
	s->dot_density = 1;
	s->draw_skybox = 1;
	s->camera_height = 2500;
	s->foc = 750;
	s->yaw = M_PI / 180 * 45;
	s->pitch = M_PI / 180 * (90 - 35.264);
	s->skybox_number = 1;
	s->height_scale
		*= fmax((double)ft_imax(s->mesh_width, s->mesh_height) / 1024, 1);
}

void	init_mlx(t_FdF *s)
{
	int32_t	width;
	int32_t	height;

	s->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FdF", 1);
	if (!s->mlx)
		clean_exit("mlx_init failed", s);
	mlx_get_monitor_size(0, &width, &height);
	if (width < WINDOW_WIDTH || height < WINDOW_HEIGHT)
	{
		mlx_terminate(s->mlx);
		width = ft_imin(width, height) * 0.7;
		height = width;
		s->mlx = mlx_init(width, height, "FdF", 1);
		if (!s->mlx)
			clean_exit("mlx_init failed", s);
	}
	s->depth_map = mlx_new_image(s->mlx, s->mlx->width, s->mlx->height);
	if (!s->depth_map)
		clean_exit("mlx_new_image failed", s);
	s->background = mlx_new_image(s->mlx, s->mlx->width, s->mlx->height);
	if (!s->background || mlx_image_to_window(s->mlx, s->background, 0, 0) < 0)
		clean_exit("mlx_new_image failed", s);
	s->canvas = mlx_new_image(s->mlx, s->mlx->width, s->mlx->height);
	if (!s->canvas || mlx_image_to_window(s->mlx, s->canvas, 0, 0) < 0)
		clean_exit("mlx_new_image failed", s);
}

int	main(int argc, char **argv)
{
	t_FdF	s;

	errno = 0;
	ft_bzero(&s, sizeof(t_FdF));
	if (argc != 2 && argc != 3)
		clean_exit("Wrong number of arguments! Allowed: 1 or 2", &s);
	init_mesh(argc, argv, &s);
	init_skybox(&s);
	init_mlx(&s);
	init_settings(&s);
	init_hooks(&s);
	delete_skybox_textures(&s);
	if (s.fps_image)
		mlx_delete_image(s.mlx, s.fps_image);
	mlx_terminate(s.mlx);
	free(s.mesh);
}
