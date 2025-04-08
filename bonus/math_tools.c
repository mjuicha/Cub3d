/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:54:26 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/08 15:59:07 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dir	*get_ray_direction(t_game *game, double angle)
{
	t_dir	*dir;

	dir = malloc(sizeof(t_dir));
	if (!dir)
		mlx_free(game, MALLOC_ERROR);
	dir->down = (angle >= 0.0 && angle <= M_PI);
	dir->up = !dir->down;
	dir->right = (angle <= M_PI / 2 || angle >= 3 * M_PI / 2);
	dir->left = !dir->right;
	return (dir);
}

double	phitagore(t_game *game, int x2, int y2)
{
	int	x1;
	int	y1;

	x1 = game->player->pos_x;
	y1 = game->player->pos_y;
	return (sqrtl(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
