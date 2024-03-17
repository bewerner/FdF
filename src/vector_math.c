/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:58:59 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/12 23:12:56 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_length(t_ivec2 p1, t_ivec2 p2)
{
	t_vec2	distance;
	double	length;

	distance.x = abs(p2.x - p1.x);
	distance.y = abs(p2.y - p1.y);
	length = sqrt(distance.x * distance.x + distance.y * distance.y);
	return (length);
}

double	edge_function(t_ivec2 a, t_ivec2 b, t_ivec2 p)
{
	return ((b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x));
}
