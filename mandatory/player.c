/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:20:01 by mjuicha           #+#    #+#             */
/*   Updated: 2025/04/09 14:51:18 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_waaal(t_game *game, int y, int x)
{
	if (x < 0 || y < 0 || y >= game->mapcounter \
		|| x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (game->map[y][x] && game->map[y][x] == '1')
		return (1);
	return (0);
}

double	hoz(t_game *game, double angle)
{
	double	dy;
	double	dx;
	double	vet;

	game->hor_y_intercept = (floor(game->player->pos_y / game->height)
			* game->height) + is_down(game);
	game->hor_x_intercept = game->player->pos_x + ((game->hor_y_intercept
				- game->player->pos_y) / tan(angle));
	dy = game->height;
	if (game->player->dir->up)
		dy *= -1;
	dx = game->height / tan(angle);
	if ((game->player->dir->left && dx > 0)
		|| (game->player->dir->right && dx < 0))
		dx *= -1;
	vet = 0;
	while (1)
	{
		vet = floor((game->hor_y_intercept + _up(game)) / game->height);
		if (check_waaal(game, vet, floor(game->hor_x_intercept / game->width)))
			break ;
		game->hor_x_intercept += dx;
		game->hor_y_intercept += dy;
	}
	return (phitagore(game, game->hor_x_intercept, game->hor_y_intercept));
}

double	ver(t_game *game, double angle)
{
	double	het;
	double	dy;
	double	dx;

	game->ver_x_intercept = (floor(game->player->pos_x / game->width)
			* game->width) + is_right(game);
	game->ver_y_intercept = game->player->pos_y + ((game->ver_x_intercept
				- game->player->pos_x) * tan(angle));
	dx = game->width;
	if (game->player->dir->left)
		dx *= -1;
	dy = game->width * tan(angle);
	if ((game->player->dir->up && dy > 0)
		|| (game->player->dir->down && dy < 0))
		dy *= -1;
	het = 0;
	while (1)
	{
		het = floor((game->ver_x_intercept + _left(game)) / game->width);
		if (check_waaal(game, floor(game->ver_y_intercept / game->height), het))
			break ;
		game->ver_x_intercept += dx;
		game->ver_y_intercept += dy;
	}
	return (phitagore(game, game->ver_x_intercept, game->ver_y_intercept));
}

void	cast_one_ray(t_game *game, double angle, int ray)
{
	double	h_dis;
	double	v_dis;

	angle = normalize_angle(angle);
	game->player->dir = get_dir(game, angle);
	h_dis = hoz(game, angle);
	v_dis = ver(game, angle);
	free(game->player->dir);
	game->dis[ray] = d_inf_equal(h_dis, v_dis, h_dis, v_dis);
	game->wallx[ray] = d_inf_equal(h_dis, v_dis, game->hor_x_intercept,
			game->ver_x_intercept);
	game->wally[ray] = d_inf_equal(h_dis, v_dis, game->hor_y_intercept,
			game->ver_y_intercept);
	game->t_angle[ray] = angle;
	game->is_hor[ray] = inf_equal(h_dis, v_dis);
	game->is_spec[ray] = equal(h_dis, v_dis);
}

void	cast_all_rays(t_game *game)
{
	double	angleofray;
	int		i;

	i = 0;
	angleofray = game->player->angle - (game->player->fov / 2);
	while (i < WIDTH)
	{
		cast_one_ray(game, angleofray, i);
		angleofray += game->player->fov / WIDTH;
		i++;
	}
}
