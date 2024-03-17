/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwerner <bwerner@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 23:48:03 by bwerner           #+#    #+#             */
/*   Updated: 2024/03/17 10:42:15 by bwerner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint8_t	is_in_range(char *nbstr, char *min, char *max)
{
	uint8_t		nbstrlen;
	uint8_t		i;

	nbstrlen = ft_strlen(nbstr);
	if ((nbstrlen > 6) || (nbstrlen > 5 && nbstr[0] != '-'))
		return (0);
	i = 0;
	while (nbstr[i] != '\0' && nbstrlen == 5 && nbstr[0] != '-')
	{
		if (nbstr[i] < max[i])
			return (1);
		if (nbstr[i] > max[i])
			return (0);
		i++;
	}
	i = 1;
	while (nbstr[i] != '\0' && nbstrlen == 6 && nbstr[0] == '-')
	{
		if (nbstr[i] < min[i])
			return (1);
		if (nbstr[i] > min[i])
			return (0);
		i++;
	}
	return (1);
}

uint8_t	is_numeric(char *str)
{
	uint8_t	i;

	i = 0;
	if (str[0] == '-')
		i = 1;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	validate_value(char *str, t_FdF *s)
{
	uint8_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			str[i] = '\0';
		else
			i++;
	}
	if (!is_numeric(str) || (str[0] == '0' && str[1] != '\0'))
	{
		ft_putstr_fd("Map Error: Value is invalid: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\nAllowed characters: digits and -\n", 2);
		clean_exit("Leading zeros are not allowed", s);
	}
	if (!is_in_range(str, "-20000", "20000"))
	{
		ft_putstr_fd("Map Error: Value out of range: ", 2);
		ft_putstr_fd(str, 2);
		clean_exit("\nAllowed range: -20000 to 20000", s);
	}
}
