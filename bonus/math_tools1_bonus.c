/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:15:18 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 16:52:29 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	inf_equal(double a, double b)
{
	if (a <= b)
		return (1);
	return (0);
}

int	equal(double a, double b)
{
	if (a == b)
		return (1);
	return (0);
}

double	shortest_dist(double a, double b, double r1, double r2)
{
	if (a <= b)
		return (r1);
	return (r2);
}

int	is_nord(double angle)
{
	if (angle >= M_PI && angle < 2 * M_PI)
		return (1);
	return (0);
}

int	is_east(double angle)
{
	if (angle >= M_PI_2 && angle < 3 * M_PI_2)
		return (1);
	return (0);
}
