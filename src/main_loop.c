/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:55:17 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/13 01:33:50 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_depthmap(t_FdF *s)
{
	size_t	len;
	size_t	i;
	float	*ptr;

	len = s->depth_map->width * s->depth_map->height;
	i = 0;
	ptr = ((float *)s->depth_map->pixels);
	while (i < len)
	{
		ptr[i] = 9999999;
		i++;
	}
}

void	brighten_canvas(double factor, t_FdF *s)
{
	uint32_t	x;
	uint32_t	y;
	uint8_t		alpha;

	x = 0;
	y = 0;
	while (y < s->canvas->height)
	{
		alpha = s->canvas->pixels[x * 4 + y * s->canvas->width * 4 + 3];
		alpha = ft_imin(alpha * factor, 255);
		s->canvas->pixels[x * 4 + y * s->canvas->width * 4 + 3] = alpha;
		x++;
		if (x == s->canvas->width)
		{
			y++;
			x = 0;
		}
	}
}

void	put_background(t_FdF *s)
{
	uint32_t	x;
	uint32_t	y;
	t_color		color;

	color.color = 0x051525FF;
	x = 0;
	y = 0;
	while (y < s->background->height)
	{
		mlx_put_pixel(s->background, x, y, color.color);
		x++;
		if (x == s->background->width)
		{
			y++;
			color.channel[R] = y * 50 / s->background->height;
			x = 0;
		}
	}
}

void	put_fps(t_FdF *s)
{
	static uint32_t		frames;
	static double		time;
	char				*str;

	time += s->mlx->delta_time;
	frames++;
	if (!s->fps_image)
		s->fps_image = mlx_put_string(s->mlx, "--", 7, 2);
	if (time >= 1)
	{
		if (s->fps_image)
			mlx_delete_image(s->mlx, s->fps_image);
		str = ft_itoa((int)(frames / time));
		if (!str)
			clean_exit("Allocation in ft_itoa failed", s);
		s->fps_image = mlx_put_string(s->mlx, str, 7, 3);
		free(str);
		frames = 0;
		time = 0;
	}
}

void	main_loop(void *param)
{
	t_FdF	*s;

	s = param;
	s->clicked = fmax(s->clicked - s->mlx->delta_time, 0);
	if (s->draw_fps)
		put_fps(s);
	else if (s->fps_image)
	{
		mlx_delete_image(s->mlx, s->fps_image);
		s->fps_image = NULL;
	}
	if (s->draw_skybox)
		put_skybox(s);
	else
		put_background(s);
	reset_depthmap(s);
	put_mesh(s);
	if (s->anti_aliasing && s->draw_edges)
		brighten_canvas(1.2, s);
}
