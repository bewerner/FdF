/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 01:35:59 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/15 15:59:13 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint8_t	line_is_visible(t_pixel a, t_pixel b, t_FdF *s)
{
	int32_t	width;
	int32_t	height;
	int32_t	max;

	width = s->canvas->width;
	height = s->canvas->height;
	if ((a.x > width && b.x > width) || (a.x < 0 && b.x < 0))
		return (0);
	if ((a.y > height && b.y > height) || (a.y < 0 && b.y < 0))
		return (0);
	max = 50000;
	if (s->orthographic)
		max = 500000;
	width += max;
	height += max;
	if (a.y > height || a.x > width || a.y < -max || a.x < -max)
		return (0);
	if (b.y > height || b.x > width || b.y < -max || b.x < -max)
		return (0);
	return (1);
}

void	put_aa_line_segment(t_vec2 pos, t_pixel pixel, t_FdF *s)
{
	t_vec2		offset;
	double		factor;
	uint8_t		alpha;

	alpha = pixel.channel[A];
	pixel.pos = (t_ivec2){round(pos.x), round(pos.y)};
	offset = (t_vec2){pos.x - pixel.x, pos.y - pixel.y};
	factor = 1 - fabs(offset.x) - fabs(offset.y);
	pixel.channel[A] = alpha * factor;
	put_aa_pixel(s->canvas, pixel, s);
	if (!offset.x && !offset.y)
		return ;
	if (offset.x)
		pixel.x += offset.x / fabs(offset.x);
	else if (offset.y)
		pixel.y += offset.y / fabs(offset.y);
	pixel.channel[A] = alpha - pixel.channel[A];
	put_aa_pixel(s->canvas, pixel, s);
}

void	put_aa_line(t_pixel a, t_pixel b, t_FdF *s)
{
	t_pixel		pixel;
	t_vec2		step;
	t_ivec2		distance;
	uint32_t	steps;
	uint32_t	i;

	i = 0;
	distance = (t_ivec2){b.x - a.x, b.y - a.y};
	steps = (ft_imax(abs(distance.x), abs(distance.y)));
	if (steps)
		step = (t_vec2){(double)distance.x / steps, (double)distance.y / steps};
	else
		put_pixel(s->canvas, a, 1, s);
	while (steps && i <= steps)
	{
		pixel.color = fade_color(a.color, b.color, steps, i);
		pixel.depth = a.depth + (b.depth - a.depth) * ((double)1 / steps) * i;
		put_aa_line_segment((t_vec2){a.x + step.x * i, a.y + step.y * i},
			pixel, s);
		i++;
	}
}

void	put_pixel_line(t_pixel a, t_pixel b, uint8_t thickness, t_FdF *s)
{
	t_pixel		pixel;
	t_vec2		step;
	t_ivec2		distance;
	uint32_t	steps;
	uint32_t	i;

	pixel = a;
	i = 0;
	distance = (t_ivec2){b.x - a.x, b.y - a.y};
	steps = (ft_imax(abs(distance.x), abs(distance.y)));
	if (steps)
		step = (t_vec2){(double)distance.x / steps, (double)distance.y / steps};
	else
		put_pixel(s->canvas, a, thickness, s);
	while (steps && i <= steps)
	{
		pixel.pos = (t_ivec2){round(a.x + step.x * i), round(a.y + step.y * i)};
		pixel.color = fade_color(a.color, b.color, steps, i);
		pixel.depth = a.depth + (b.depth - a.depth) * (1.f / steps) * i;
		put_pixel(s->canvas, pixel, thickness, s);
		i++;
	}
}

void	put_line(t_pixel a, t_pixel b, uint8_t thickness, t_FdF *s)
{
	if (!line_is_visible(a, b, s) || !a.vis || !b.vis)
		return ;
	if (!a.channel[A] && !b.channel[A])
		return ;
	if (s->anti_aliasing && s->draw_edges)
		put_aa_line(a, b, s);
	else
		put_pixel_line(a, b, thickness, s);
}
