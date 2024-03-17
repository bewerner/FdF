/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_dot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 23:39:37 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/15 15:13:47 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_ivec2	lerp_ivec2(t_ivec2 a, t_ivec2 b, double factor)
{
	t_ivec2	r;

	r.x = a.x + ((b.x - a.x) * factor);
	r.y = a.y + ((b.y - a.y) * factor);
	return (r);
}

void	put_dotted_line(t_vert a, t_vert b, uint16_t size, t_FdF *s)
{
	double		distance;
	double		factor;
	double		initial_factor;
	t_pixel		dot;
	uint32_t	segments;

	if (!a.pixel.vis || !b.pixel.vis || !line_is_visible(a.pixel, b.pixel, s))
		return ;
	put_dot(s->canvas, a.pixel, size, s);
	put_dot(s->canvas, b.pixel, size, s);
	if (!(b.z - a.z) && s->dot_density <= 1)
		return ;
	distance = fmax(fabs((b.z - a.z) * s->height_scale), 1);
	segments = round(distance) * s->dot_density;
	dot = a.pixel;
	initial_factor = (double)1 / segments;
	factor = initial_factor;
	while (factor < 1)
	{
		dot.pos = lerp_ivec2(a.pixel.pos, b.pixel.pos, factor);
		dot.color = lerp_color(a.pixel.color, b.pixel.color, factor);
		dot.depth = a.pixel.depth + ((b.pixel.depth - a.pixel.depth) * factor);
		put_dot(s->canvas, dot, size, s);
		factor += initial_factor;
	}
}

void	iterate_pixel_pos(t_ivec2 *pos, t_ivec2 *i, uint16_t size)
{
	(*pos).x++;
	(*i).x++;
	if ((*i).x == size)
	{
		(*pos).y++;
		(*i).y++;
		(*pos).x -= size;
		(*i).x = 0;
	}
}

void	put_dot(mlx_image_t *image, t_pixel pixel, uint16_t size, t_FdF *s)
{
	t_ivec2	i;
	t_ivec2	center;
	double	radius;
	double	length;
	t_color	color;

	if (!s->orthographic && size > 1)
		size = fmax(size * s->camera_height / pixel.depth, 1);
	i = (t_ivec2){0, 0};
	center = pixel.pos;
	radius = (double)size / 2;
	color.color = pixel.color;
	pixel.pos = (t_ivec2){pixel.x - size / 2, pixel.y - size / 2};
	while (i.y <= size)
	{
		length = get_length(pixel.pos, center);
		if (length <= radius)
		{
			pixel.channel[R] = (1 - length / radius / 2) * color.channel[R];
			pixel.channel[G] = (1 - length / radius / 2) * color.channel[G];
			pixel.channel[B] = (1 - length / radius / 2) * color.channel[B];
			put_pixel(image, pixel, 1, s);
		}
		iterate_pixel_pos(&pixel.pos, &i, size + 1);
	}
}
