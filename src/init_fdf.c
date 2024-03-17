/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:41:54 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/15 15:46:07 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_dimensions(char *filepath, t_FdF *s)
{
	int16_t		fd;
	char		current;
	char		previous;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		clean_exit(filepath, s);
	previous = ' ';
	while (read(fd, &current, 1))
	{
		if (!ft_isspace(current) && ft_isspace(previous))
			s->vert_count++;
		if (current == '\n')
			s->mesh_height++;
		if (current == '\n' && !s->mesh_width)
			s->mesh_width = s->vert_count;
		previous = current;
	}
	if (current != '\n')
		s->mesh_height++;
	if (!s->mesh_width)
		s->mesh_width = s->vert_count;
	close(fd);
	if (!s->vert_count || s->mesh_width * s->mesh_height != s->vert_count)
		clean_exit("Map error", s);
}

static int32_t	get_next_value(int fd, t_FdF *s)
{
	int		bytes_read;
	int		i;
	char	value[64];

	bytes_read = 1;
	i = 0;
	while (bytes_read && i < 63)
	{
		bytes_read = read(fd, &value[i], 1);
		if (bytes_read == -1)
		{
			close(fd);
			clean_exit("Read failed", s);
		}
		if (i && ft_isspace(value[i]))
			break ;
		if (!ft_isspace(value[i]) && bytes_read)
			i++;
	}
	value[i] = '\0';
	validate_value(value, s);
	return (ft_atoi(value));
}

static void	read_fdf(char *filepath, t_FdF *s)
{
	int		fd;
	size_t	i;
	size_t	x;
	size_t	y;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		clean_exit(filepath, s);
	i = 0;
	x = 0;
	y = 0;
	while (i < s->vert_count)
	{
		s->mesh[i].x = x;
		s->mesh[i].y = y;
		s->mesh[i].z = get_next_value(fd, s);
		i++;
		x++;
		if (x == s->mesh_width)
		{
			y++;
			x = 0;
		}
	}
	close(fd);
}

void	init_fdf(char *filepath, t_FdF *s)
{
	set_dimensions(filepath, s);
	s->mesh = (t_vert *)malloc(s->vert_count * sizeof(t_vert));
	if (!s->mesh)
		clean_exit("Memory allocation failed", s);
	read_fdf(filepath, s);
	set_vert_colors(s);
	s->height_scale = 1;
}
