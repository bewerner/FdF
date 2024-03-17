/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vert_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 23:53:11 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	height_to_color(int32_t height, t_FdF *s)
{
	t_color	color;
	double	factor;

	factor = 0;
	if (s->max_height - s->min_height)
	{
		factor = (height - s->min_height);
		factor /= (s->max_height - s->min_height);
	}
	color.color = lerp_color(0xFDD404FF, 0xF40AD8FF, factor);
	return (color.color);
}

void	set_min_max_height(t_FdF *s)
{
	uint32_t	i;

	s->min_height = s->mesh[0].z;
	s->max_height = s->mesh[0].z;
	i = 0;
	while (i < s->vert_count)
	{
		if (s->mesh[i].z > s->max_height)
			s->max_height = s->mesh[i].z;
		if (s->mesh[i].z < s->min_height)
			s->min_height = s->mesh[i].z;
		i++;
	}
}

void	set_vert_colors(t_FdF *s)
{
	size_t	i;

	set_min_max_height(s);
	i = 0;
	while (i < s->vert_count)
	{
		s->mesh[i].pixel.color = height_to_color(s->mesh[i].z, s);
		i++;
	}
}
