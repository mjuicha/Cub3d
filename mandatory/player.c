/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: librahim <librahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:20:01 by mjuicha           #+#    #+#             */
/*   Updated: 2025/03/22 12:32:51 by librahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_waaal(t_game_data *game, int y, int x)
{
	if (x < 0 || y < 0 || y >= game->mapcounter \
		|| x >= (int)ft_strlen(game->map[y]))
		return (1);
	if (game->map[y][x] && game->map[y][x] == '1')
		return (1);
	return (0);
}

double	hoz(t_game_data *game, double angle)
{
	double	dy;
	double	dx;
	double	vet;

	game->hy = (floor(game->player->pos_y / game->height) * game->height)
		+ is_down(game);
	game->hx = game->player->pos_x + ((game->hy - game->player->pos_y)
			/ tan(angle));
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
		vet = floor((game->hy + is_up(game)) / game->height);
		if (check_waaal(game, vet, floor(game->hx / game->width)))
			break ;
		game->hx += dx;
		game->hy += dy;
	}
	return (phitagore(game, game->hx, game->hy));
}

double	ver(t_game_data *game, double angle)
{
	double	het;
	double	dy;
	double	dx;

	game->vx = (floor(game->player->pos_x / game->width) * game->width)
		+ is_right(game);
	game->vy = game->player->pos_y + ((game->vx - game->player->pos_x)
			* tan(angle));
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
		het = floor((game->vx + is_left(game)) / game->width);
		if (check_waaal(game, floor(game->vy / game->height), het))
			break ;
		game->vx += dx;
		game->vy += dy;
	}
	return (phitagore(game, game->vx, game->vy));
}

void	cast_one_ray(t_game_data *game, double angle, int ray)
{
	double	h_dis;
	double	v_dis;

	angle = normalize_angle(angle);
	get_ray_dir(game, angle);
	h_dis = hoz(game, angle);
	v_dis = ver(game, angle);
	game->dis[ray] = d_inf_equal(h_dis, v_dis, h_dis, v_dis);
	game->wallx[ray] = d_inf_equal(h_dis, v_dis, game->hx, game->vx);
	game->wally[ray] = d_inf_equal(h_dis, v_dis, game->hy, game->vy);
	game->t_angle[ray] = angle;
	game->is_hor[ray] = inf_equal(h_dis, v_dis);
	game->is_spec[ray] = equal(h_dis, v_dis);
}

void	cast_all_rays(t_game_data *game)
{
	float	dis_proj;
	float	angle_ofray;
	int		i;

	i = 0;
	dis_proj = (WIDTH / 2) / tan(game->player->fov / 2);
	while (i < WIDTH)
	{
		angle_ofray = game->player->angle + atan((i - WIDTH / 2) / dis_proj);
		cast_one_ray(game, angle_ofray, i);
		i++;
	}
}
