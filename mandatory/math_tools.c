/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:54:26 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 12:35:04 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray_dir(t_game_data *game, double angle)
{
	game->player->dir->down = (angle >= 0.0 && angle <= M_PI);
	game->player->dir->up = !game->player->dir->down;
	game->player->dir->right = (angle <= M_PI / 2 || angle >= 3 * M_PI / 2);
	game->player->dir->left = !game->player->dir->right;
}

double	phitagore(t_game_data *game, int x2, int y2)
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
