/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:45:44 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/15 17:18:02 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_big_pixel(mlx_image_t *img, t_pixel pixel, uint8_t size, t_FdF *s)
{
	t_ivec2	i;
	t_ivec2	center;
	double	radius;

	i = (t_ivec2){0, 0};
	center = pixel.pos;
	radius = (double)size / 2;
	pixel.x -= size / 2 + 1;
	pixel.y -= size / 2 + 1;
	while (i.y < size + 2)
	{
		if (get_length(pixel.pos, center) <= radius)
			put_pixel(img, pixel, 1, s);
		pixel.x++;
		i.x++;
		if (i.x == size + 2)
		{
			pixel.y++;
			i.y++;
			pixel.x -= size + 2;
			i.x = 0;
		}
	}
}

void	write_depth(t_pixel pixel, t_FdF *s)
{
	uint32_t	pos;
	float		depth;

	pos = pixel.x * 4 + pixel.y * s->depth_map->width * 4;
	depth = (float)pixel.depth;
	ft_memmove(&s->depth_map->pixels[pos], &depth, 4);
}

float	read_depth(t_pixel pixel, t_FdF *s)
{
	uint32_t	pos;
	float		depth;

	pos = pixel.x * 4 + pixel.y * s->depth_map->width * 4;
	ft_memmove(&depth, &s->depth_map->pixels[pos], 4);
	return (depth);
}

void	put_aa_pixel(mlx_image_t *img, t_pixel pixel, t_FdF *s)
{
	t_pixel	old;

	if (pixel.channel[A] && pixel.x >= 0 && pixel.x < (int)img->width
		&& pixel.y >= 0 && pixel.y < (int)img->height)
	{
		old.pos = pixel.pos;
		old.color = sample_image(s->canvas, pixel.x, pixel.y);
		old.depth = read_depth(pixel, s);
		if (pixel.depth > old.depth)
		{
			mlx_put_pixel(s->canvas, pixel.x, pixel.y, 0);
			mlx_put_pixel(s->depth_map, pixel.x, pixel.y, 0x7f96184b);
			put_aa_pixel(s->canvas, pixel, s);
			put_aa_pixel(s->canvas, old, s);
			return ;
		}
		if (old.channel[A])
			pixel.color = lerp_color(old.color, pixel.color,
					(double)pixel.channel[A] / old.channel[A] * 1.2);
		pixel.channel[A] = ft_imax(pixel.channel[A], old.channel[A]);
		mlx_put_pixel(s->canvas, pixel.x, pixel.y, pixel.color);
		write_depth(pixel, s);
	}
}

void	put_pixel(mlx_image_t *img, t_pixel pixel, uint8_t size, t_FdF *s)
{
	float	depth;

	if (!pixel.channel[A])
		return ;
	if (size > 1)
		put_big_pixel(img, pixel, size, s);
	else if (pixel.x >= 0 && pixel.x < (int)img->width
		&& pixel.y >= 0 && pixel.y < (int)img->height)
	{
		depth = read_depth(pixel, s);
		if (pixel.depth > depth)
			return ;
		mlx_put_pixel(img, pixel.x, pixel.y, pixel.color);
		write_depth(pixel, s);
	}
}
