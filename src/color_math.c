/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 02:02:06 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/15 17:23:22 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	sample_texture(mlx_texture_t *image, int32_t x, int32_t y)
{
	t_color		color;
	uint32_t	pos;

	color.color = 0;
	if (x >= 0 && x < (int32_t)image->width
		&& y >= 0 && y < (int32_t)image->height)
	{
		pos = (x * 4) + (y * image->width * 4);
		color.channel[R] = image->pixels[pos + 0];
		color.channel[G] = image->pixels[pos + 1];
		color.channel[B] = image->pixels[pos + 2];
		color.channel[A] = image->pixels[pos + 3];
	}
	return (color.color);
}

uint32_t	sample_image(mlx_image_t *image, int32_t x, int32_t y)
{
	t_color		color;
	uint32_t	pos;

	color.color = 0;
	if (x >= 0 && x < (int32_t)image->width
		&& y >= 0 && y < (int32_t)image->height)
	{
		pos = (x * 4) + (y * image->width * 4);
		color.channel[R] = image->pixels[pos + 0];
		color.channel[G] = image->pixels[pos + 1];
		color.channel[B] = image->pixels[pos + 2];
		color.channel[A] = image->pixels[pos + 3];
	}
	return (color.color);
}

uint32_t	fade_color(uint32_t col_a, uint32_t col_b, int32_t steps, int step)
{
	t_color	a;
	t_color	b;

	if (steps < 6)
		return (col_a);
	if (steps > 30)
		return (lerp_color(col_a, col_b, (double)step / steps));
	a.color = col_a;
	b.color = col_b;
	a.channel[R] += (b.channel[R] - a.channel[R]) / steps * step;
	a.channel[G] += (b.channel[G] - a.channel[G]) / steps * step;
	a.channel[B] += (b.channel[B] - a.channel[B]) / steps * step;
	a.channel[A] += (b.channel[A] - a.channel[A]) / steps * step;
	return (a.color);
}

uint8_t	lerp_color_channel(uint8_t a, uint8_t b, double factor)
{
	uint8_t	r;

	r = round(a * (1 - factor)) + (b * factor);
	return (r);
}

u_int32_t	lerp_color(u_int32_t color_a, u_int32_t color_b, double factor)
{
	t_color	a;
	t_color	b;
	t_color	r;

	factor = fmin(factor, 1);
	factor = fmax(factor, 0);
	a.color = color_a;
	b.color = color_b;
	r.channel[R] = lerp_color_channel(a.channel[R], b.channel[R], factor);
	r.channel[G] = lerp_color_channel(a.channel[G], b.channel[G], factor);
	r.channel[B] = lerp_color_channel(a.channel[B], b.channel[B], factor);
	r.channel[A] = lerp_color_channel(a.channel[A], b.channel[A], factor);
	return (r.color);
}
